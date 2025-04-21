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

void CServer::Erase_Uuid(std::string _Uuid)
{
	m_mapSession.erase(_Uuid);
}

void CServer::StartAccept(void)
{
	std::shared_ptr<CSession> pcSession = std::make_shared<CSession>(m_cIO_Context, this);
	
	m_cAcceptor.async_accept(pcSession->R_Socket(), 
		std::bind(&CServer::HandleAccept_CallBack, this, pcSession, std::placeholders::_1));
}

void CServer::HandleAccept_CallBack(std::shared_ptr<CSession> _pSession, const boost::system::error_code& _ErrCode)
{
	if (!_ErrCode)			//连接成功
	{
		m_mapSession.insert(std::make_pair(_pSession->Get_Uuid(), _pSession));

		_pSession->Start();
	}
	
	this->StartAccept();
}
