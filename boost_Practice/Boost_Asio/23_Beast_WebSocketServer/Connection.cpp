/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Connection.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.22
描  述: 处理WebSocket连接
备  注:
修改记录:

  1.  日期: 2025.05.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "Connection.h"
#include "ConnectionMgr.h"

CConnection::CConnection(boost::asio::io_context& _IO_Context) : m_cIO_Context(_IO_Context),
	m_pWebSocket(std::make_unique<boost::beast::websocket::stream<boost::beast::tcp_stream>>(boost::asio::make_strand(_IO_Context)))
{
	//生成唯一uuid
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
	return boost::beast::get_lowest_layer(*m_pWebSocket).socket();		//返回websocket底层的tcp socket对象
}

void CConnection::AsyncAccept()
{
	auto self = shared_from_this();
	m_pWebSocket->async_accept([self](boost::system::error_code _Err) {
		try
		{
			if (!_Err)
			{
				CConnectionMgr::GetInstance().Add_Connection(self);		//防止当前智能指针被操作系统释放
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
				CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//防止当前智能指针被操作系统释放
				return;
			}	

			std::string strRecvData;

			//设置当前消息的发送模式（text 或 binary）
			//got_text()：返回当前收到的消息是否是文本类型（true 表示是文本，false 表示是二进制）
			//text(bool)：设置发送消息时使用文本（true）或二进制（false）模式
			self->m_pWebSocket->text(self->m_pWebSocket->got_text());				

			strRecvData = boost::beast::buffers_to_string(self->m_cRecvFlatBuf.data());	//接收的数据转换为string

			self->m_cRecvFlatBuf.consume(self->m_cRecvFlatBuf.size());					//清空websocket的接收缓冲区

			std::cout << "websocket recv msg: " << "[" << ++self->m_unRecvCounter << "] " << strRecvData << std::endl;

			self->AsyncSend(std::move(strRecvData));
			self->Start();
		}
		catch (const std::exception& e)
		{
			std::cout << "websocket async accept exception is " << e.what() << std::endl;
			CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//防止当前智能指针被操作系统释放
		}
		});
}

void CConnection::AsyncSend(std::string _Msg)
{
	bool bPending = false;								//表示发送队列的数据是否正在发送;false--未发送;true--正在发送;
	std::lock_guard<std::mutex> cLockGuard(m_mutSend);

	if (m_queSend.size() > 0)							//如果有数据，则表示异步发送已经被启动了
		bPending = true;

	m_queSend.push(_Msg);

	if (bPending)										//防止多次启动boost asio的异步发送数据
		return;

	auto self = shared_from_this();

	//如果asio的异步数据发送没有启动，则在此处启动异步发送
	m_pWebSocket->async_write(boost::asio::buffer(_Msg.data(), _Msg.size()), [self](boost::system::error_code _Err, std::size_t _BufBytes) {
		try
		{
			if (_Err)
			{
				std::cout << "websocket async_write failed, err is " << _Err.message() << std::endl;
				CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);		//防止当前智能指针被操作系统释放
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
			CConnectionMgr::GetInstance().Remove_Connection(self->m_strUuid);			//防止当前智能指针被操作系统释放
		}
		});
}




