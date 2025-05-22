/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	WebSocketServer.h
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


