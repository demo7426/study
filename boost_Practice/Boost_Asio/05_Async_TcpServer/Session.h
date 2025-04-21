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
	/// 读数据回调
	/// </summary>
	/// <param name="_ErrCode"></param>
	/// <param name="_Byte_Transferred"></param>
	void Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred, std::shared_ptr<CSession> _pSelf_Session);

	/// <summary>
	/// 写数据回调
	/// </summary>
	/// <param name="_ErrCode"></param>
	void Handle_Write_CallBack(const boost::system::error_code& _ErrCode, std::shared_ptr<CSession> _pSelf_Session);

private:
	boost::asio::ip::tcp::socket m_cSocket;
	
	constexpr static size_t m_unMaxRecvLen = 1024;				//接收数据缓冲最大长度
	char m_chRecvBuf[m_unMaxRecvLen] = { 0 };					//接收数据缓冲

	std::string m_strUuid;

	CServer* m_pcServer = nullptr;
};

