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

class CSession
{
public:
	CSession() = delete;
	CSession(boost::asio::io_context& _IO_Context) : m_cSocket(_IO_Context)
	{};

	~CSession() = default;

	void Start(void);

	inline boost::asio::ip::tcp::socket& R_Socket(void)
	{
		return m_cSocket;
	}

private:
	/// <summary>
	/// �����ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	/// <param name="_Byte_Transferred"></param>
	void Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred);

	/// <summary>
	/// д���ݻص�
	/// </summary>
	/// <param name="_ErrCode"></param>
	void Handle_Write_CallBack(const boost::system::error_code& _ErrCode);

private:
	boost::asio::ip::tcp::socket m_cSocket;
	
	constexpr static size_t m_unMaxRecvLen = 1024;				//�������ݻ�����󳤶�
	char m_chRecvBuf[m_unMaxRecvLen] = { 0 };					//�������ݻ���
};

