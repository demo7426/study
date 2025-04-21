/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Session.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.21
描  述: 回声服务端会话接口
备  注:
修改记录:

  1.  日期: 2025.04.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

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
	/// 读数据回调
	/// </summary>
	/// <param name="_ErrCode"></param>
	/// <param name="_Byte_Transferred"></param>
	void Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred);

	/// <summary>
	/// 写数据回调
	/// </summary>
	/// <param name="_ErrCode"></param>
	void Handle_Write_CallBack(const boost::system::error_code& _ErrCode);

private:
	boost::asio::ip::tcp::socket m_cSocket;
	
	constexpr static size_t m_unMaxRecvLen = 1024;				//接收数据缓冲最大长度
	char m_chRecvBuf[m_unMaxRecvLen] = { 0 };					//接收数据缓冲
};

