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

#pragma once

#include <map>

#include "Session.h"

class CServer
{
public:
	CServer(boost::asio::io_context& _IO_Context, unsigned short _PortNo);

	~CServer();

	void Erase_Uuid(std::string _Uuid);

private:
	void StartAccept(void);

	void HandleAccept_CallBack(std::shared_ptr<CSession> _pSession, const boost::system::error_code& _ErrCode);

private:

	boost::asio::io_context& m_cIO_Context;

	boost::asio::ip::tcp::acceptor m_cAcceptor;

	std::map<std::string, std::shared_ptr<CSession>> m_mapSession;
};



