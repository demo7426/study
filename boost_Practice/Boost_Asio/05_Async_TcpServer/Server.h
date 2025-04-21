/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Server.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.21
描  述: 回声服务端
备  注:
修改记录:

  1.  日期: 2025.04.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#pragma once

#include "Session.h"

class CServer
{
public:
	CServer(boost::asio::io_context& _IO_Context, unsigned short _PortNo);

	~CServer() = default;

private:
	void StartAccept(void);

	void HandleAccept_CallBack(CSession* _pSession, const boost::system::error_code& _ErrCode);

	boost::asio::io_context& m_cIO_Context;
	boost::asio::ip::tcp::acceptor m_cAcceptor;
};



