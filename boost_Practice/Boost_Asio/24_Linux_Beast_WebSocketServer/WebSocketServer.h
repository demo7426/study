/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	WebSocketServer.h
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

#pragma once

#include "ConnectionMgr.h"

class CWebSocketServer
{
public:
	CWebSocketServer(const CWebSocketServer&) = delete;
	CWebSocketServer& operator=(const CWebSocketServer&) = delete;
	CWebSocketServer(boost::asio::io_context& _IO_Context, unsigned short _Port);

	void StartAccept();
private:
	boost::asio::ip::tcp::acceptor m_cAcceptor;
	boost::asio::io_context& m_cIO_Context;
};


