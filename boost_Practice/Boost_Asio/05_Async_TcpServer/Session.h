/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Session.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.04.21
��  ��: ��������˻Ự�ӿ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.04.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.1.0

*************************************************/

#pragma once

#include <boost/asio.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <memory>
#include <iostream>

class CServer;

class CSession : public std::enable_shared_from_this<CSession>
{
public:
	CSession(boost::asio::io_context& _IO_Context, CServer* _pServer);
	
	~CSession()
	{
		std::cout << "~CSession" << std::endl;
	}

	void Start(void);

	inline boost::asio::ip::tcp::socket& R_Socket(void)
	{
		return m_cSocket;
	}

	inline std::string& Get_Uuid(void)
	{
		return m_strUuid;
	}

private:
	/// <summary>
	/// �����ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	/// <param name="_Byte_Transferred"></param>
	void Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred, std::shared_ptr<CSession> _pSelf_Session);

	/// <summary>
	/// д���ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	void Handle_Write_CallBack(const boost::system::error_code& _ErrCode, std::shared_ptr<CSession> _pSelf_Session);

private:
	boost::asio::ip::tcp::socket m_cSocket;
	
	constexpr static size_t m_unMaxRecvLen = 1024;				//�������ݻ�����󳤶�
	char m_chRecvBuf[m_unMaxRecvLen] = { 0 };					//�������ݻ���

	std::string m_strUuid;

	CServer* m_pcServer = nullptr;
};

