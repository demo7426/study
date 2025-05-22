/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	WebSocketServer.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.05.22
��  ��: ʵ��һ��WebSocket�����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.05.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

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

	//ֱ����tcp socket����Ϊweb socket
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
