/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Connection.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.22
��  ��: ����WebSocket����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#include <iostream>

#include "Connection.h"
#include "ConnectionMgr.h"

CConnection::CConnection(boost::asio::io_context& _IO_Context) : m_cIO_Context(_IO_Context),
	m_pWebSocket(std::make_unique<boost::beast::websocket::stream<boost::beast::tcp_stream>>(boost::asio::make_strand(_IO_Context)))
{
	//����Ψһuuid
	boost::uuids::random_generator cRandom_Generator;
	boost::uuids::uuid tUuid = cRandom_Generator();
	m_strUuid = boost::uuids::to_string(tUuid);
}

std::string CConnection::GetUuid()
{
	return m_strUuid;
}

boost::asio::ip::tcp::socket& CConnection::GetSocket()
{
	return boost::beast::get_lowest_layer(*m_pWebSocket).socket();		//����websocket�ײ��tcp socket����
}

void CConnection::AsyncAccept()
{
	auto self = shared_from_this();
	m_pWebSocket->async_accept([self](boost::system::error_code _Err) {
		try
		{
			if (!_Err)
			{
				CConnectionMgr::GetInstance().Add_Connection(self);		//��ֹ��ǰ����ָ�뱻����ϵͳ�ͷ�
				self->Start();
			}
			else
				std::cout << "websocket accept failed, err is " << _Err.message() << std::endl;
		}
		catch (const std::exception& e)
		{
			std::cout << "websocket async accept exception is " << e.what() << std::endl;
		}

		});
}

void CConnection::Start()
{
	auto self = shared_from_this();
	m_pWebSocket->async_read(m_cRecvFlatBuf, [self](boost::system::error_code _Err, std::size_t _BufBytes) {
		try
		{
			if (_Err)
			{
				std::cout << "websocket accept failed, err is " << _Err.message() << std::endl;
				CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//��ֹ��ǰ����ָ�뱻����ϵͳ�ͷ�
				return;
			}	

			std::string strRecvData;

			//���õ�ǰ��Ϣ�ķ���ģʽ��text �� binary��
			//got_text()�����ص�ǰ�յ�����Ϣ�Ƿ����ı����ͣ�true ��ʾ���ı���false ��ʾ�Ƕ����ƣ�
			//text(bool)�����÷�����Ϣʱʹ���ı���true��������ƣ�false��ģʽ
			self->m_pWebSocket->text(self->m_pWebSocket->got_text());				

			strRecvData = boost::beast::buffers_to_string(self->m_cRecvFlatBuf.data());	//���յ�����ת��Ϊstring

			self->m_cRecvFlatBuf.consume(self->m_cRecvFlatBuf.size());					//���websocket�Ľ��ջ�����

			std::cout << "websocket recv msg: " << "[" << ++self->m_unRecvCounter << "] " << strRecvData << std::endl;

			self->AsyncSend(std::move(strRecvData));
			self->Start();
		}
		catch (const std::exception& e)
		{
			std::cout << "websocket async accept exception is " << e.what() << std::endl;
			CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//��ֹ��ǰ����ָ�뱻����ϵͳ�ͷ�
		}
		});
}

void CConnection::AsyncSend(std::string _Msg)
{
	bool bPending = false;								//��ʾ���Ͷ��е������Ƿ����ڷ���;false--δ����;true--���ڷ���;
	std::lock_guard<std::mutex> cLockGuard(m_mutSend);

	if (m_queSend.size() > 0)							//��������ݣ����ʾ�첽�����Ѿ���������
		bPending = true;

	m_queSend.push(_Msg);

	if (bPending)										//��ֹ�������boost asio���첽��������
		return;

	auto self = shared_from_this();

	//���asio���첽���ݷ���û�����������ڴ˴������첽����
	m_pWebSocket->async_write(boost::asio::buffer(_Msg.data(), _Msg.size()), [self](boost::system::error_code _Err, std::size_t _BufBytes) {
		try
		{
			if (_Err)
			{
				std::cout << "websocket async_write failed, err is " << _Err.message() << std::endl;
				CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//��ֹ��ǰ����ָ�뱻����ϵͳ�ͷ�
				return;
			}

			std::string strSendMsg;
			{
				std::lock_guard<std::mutex> cLockGuard(self->m_mutSend);

				self->m_queSend.pop();
				if (self->m_queSend.empty())
					return;

				strSendMsg = self->m_queSend.front();
			}

			self->AsyncSend(std::move(strSendMsg));
		}
		catch (const std::exception& e)
		{
			std::cout << "websocket async_write exception is " << e.what() << std::endl;
			CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);			//��ֹ��ǰ����ָ�뱻����ϵͳ�ͷ�
		}
		});
}




