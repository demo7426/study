/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	WebSocketServer.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.22
描  述: 实现一个WebSocket服务端
备  注:
修改记录:

  1.  日期: 2025.05.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "WebSocketServer.h"

CWebSocketServer::CWebSocketServer(boost::asio::io_context& _IO_Context, unsigned short _Port) : m_cIO_Context(_IO_Context),
	m_cAcceptor(_IO_Context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _Port))
{
	std::cout << "WebSocketServer start on port: " << _Port << std::endl;
}

void CWebSocketServer::StartAccept()
{
	auto pcConnection = std::make_shared<CConnection>(m_cIO_Context);

	//直接由tcp socket提升为web socket
	m_cAcceptor.async_accept(pcConnection->GetSocket(), [this, pcConnection](boost::system::error_code _Err) {
		try
		{
			if (_Err)
				std::cout << "async_accept acceptor failed, error is " << _Err.what() << std::endl;
			else
				pcConnection->AsyncAccept();

			this->StartAccept();
		}
		catch (const std::exception& e)
		{
			std::cout << "async_accept exception error is " << e.what() << std::endl;
		}

		});
}
