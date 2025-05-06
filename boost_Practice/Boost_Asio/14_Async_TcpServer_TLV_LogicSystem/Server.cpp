/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Server.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.04.21
��  ��: ���������
��  ע:
�޸ļ�¼:

  1.  ����: 2025.04.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

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
	if (!_ErrCode)			//���ӳɹ�
	{
		m_mapSession.insert(std::make_pair(_pSession->Get_Uuid(), _pSession));

		_pSession->Start();
	}
	
	this->StartAccept();
}
