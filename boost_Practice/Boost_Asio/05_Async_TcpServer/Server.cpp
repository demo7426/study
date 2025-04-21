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

#include "Server.h"

CServer::CServer(boost::asio::io_context& _IO_Context, unsigned short _PortNo): m_cIO_Context(_IO_Context),
	m_cAcceptor(_IO_Context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _PortNo))
{
	this->StartAccept();
}

void CServer::StartAccept(void)
{
	CSession* pcSession = new CSession(m_cIO_Context);
	
	m_cAcceptor.async_accept(pcSession->R_Socket(), 
		std::bind(&CServer::HandleAccept_CallBack, this, pcSession, std::placeholders::_1));
}

void CServer::HandleAccept_CallBack(CSession* _pSession, const boost::system::error_code& _ErrCode)
{
	if (_ErrCode)			//连接错误
		delete _pSession;
	else					//连接成功
		_pSession->Start();
	
	this->StartAccept();
}
