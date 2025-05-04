/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Session.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.04.21
��  ��: ��������˻Ự�ӿ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.04.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#include <iostream>

#include "Server.h"
#include "Session.h"

CSession::CSession(boost::asio::io_context& _IO_Context, CServer* _pServer): m_cSocket(_IO_Context), m_pcServer(_pServer)
{
	boost::uuids::uuid tUuid = boost::uuids::random_generator()();
	m_strUuid = boost::uuids::to_string(tUuid);
}

void CSession::Start(void)
{
	memset(m_chRecvBuf, 0, m_unMaxRecvLen);
	m_cSocket.async_read_some(boost::asio::buffer(m_chRecvBuf, m_unMaxRecvLen),
		std::bind(&CSession::Handle_Read_CallBack, this, std::placeholders::_1, std::placeholders::_2, this->shared_from_this()));
}

void CSession::Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred, std::shared_ptr<CSession> _pSelf_Session)
{
	if (_ErrCode) 
	{
		std::cout << "Handle_Read_CallBack is err, " << _ErrCode.message() << std::endl;

		this->m_cSocket.close();

		m_pcServer->Erase_Uuid(m_strUuid);
		return;
	}

	unsigned char uchTLVHead_OccupyBytes = m_uchTLVLen_OccupyBytes + m_uchTLVType_OccupyBytes;

	//this->Send(m_chRecvBuf, _Byte_Transferred);

	if (_Byte_Transferred > 0)
	{
		unsigned short ushTLV_Type = 0;									//TLV��ʽ����
		unsigned short ushShouldRecvLen = 0;							//Ӧ�����յ����ݳ���

		m_unRecvValidLen += _Byte_Transferred;

		while (m_unRecvValidLen >= uchTLVHead_OccupyBytes)				//�Ѿ����յ������ݵĳ�����Ϣ
		{
			ushShouldRecvLen = *(unsigned short*)(m_chRecvBuf + m_uchTLVType_OccupyBytes);

			if (m_unRecvValidLen - uchTLVHead_OccupyBytes >= ushShouldRecvLen)		//���������Ѿ���������
			{
				ushTLV_Type = *(unsigned short*)(m_chRecvBuf);

				m_queRecv.push(std::make_shared<CRecvMsg_Node>(ushTLV_Type, m_chRecvBuf + uchTLVHead_OccupyBytes, ushShouldRecvLen));

				//������һ�ε�����
				memmove(m_chRecvBuf, m_chRecvBuf + ushShouldRecvLen + uchTLVHead_OccupyBytes,
					m_unRecvValidLen - ushShouldRecvLen - uchTLVHead_OccupyBytes);

				m_unRecvValidLen -= (ushShouldRecvLen + uchTLVHead_OccupyBytes);

				this->Send(m_queRecv.front()->m_pchDataStartAddr, m_queRecv.front()->m_nMaxLen);
				m_queRecv.pop();
			}
			else																		//���ݲ������������첽��������
				break;
		}
	}

	m_cSocket.async_read_some(boost::asio::buffer(m_chRecvBuf + m_unRecvValidLen, m_unMaxRecvLen - m_unRecvValidLen),
		std::bind(&CSession::Handle_Read_CallBack, this, std::placeholders::_1, std::placeholders::_2, _pSelf_Session));
}

void CSession::Handle_Write_CallBack(const boost::system::error_code& _ErrCode, std::shared_ptr<CSession> _pSelf_Session)
{
	if (_ErrCode)
	{
		std::cout << "Handle_Write_CallBack is err, " << _ErrCode.message() << std::endl;

		this->m_cSocket.close();

		m_pcServer->Erase_Uuid(m_strUuid);
		return;
	}

	std::lock_guard<std::mutex> cLockGuard(m_SendLock);

	m_queSend.pop();

	if (!m_queSend.empty())
	{
		auto pcMsgNode = m_queSend.front();
		m_cSocket.async_send(boost::asio::buffer(pcMsgNode->m_pchDataStartAddr, pcMsgNode->m_nMaxLen),
			std::bind(&CSession::Handle_Write_CallBack, this, std::placeholders::_1, this->shared_from_this()));
	}
}

void CSession::Send(char* _pMsg, int _MsgLen)
{
	bool bPending = false;								//��ʾ���Ͷ��е������Ƿ����ڷ���;false--δ����;true--���ڷ���;
	std::lock_guard<std::mutex> cLockGuard(m_SendLock);

	if (m_queSend.size() > 0)							//��������ݣ����ʾ�첽�����Ѿ���������
		bPending = true;

	m_queSend.push(std::make_shared<CSendMsg_Node>(_pMsg, _MsgLen));
	
	if (bPending)										//��ֹ�������boost asio���첽��������
		return;

	//���asio���첽���ݷ���û�����������ڴ˴������첽����
	m_cSocket.async_send(boost::asio::buffer(_pMsg, _MsgLen),
		std::bind(&CSession::Handle_Write_CallBack, this, std::placeholders::_1, this->shared_from_this()));
}
