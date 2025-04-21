/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Session.cpp
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

#include <iostream>

#include "Session.h"

void CSession::Start(void)
{
	memset(m_chRecvBuf, 0, sizeof m_chRecvBuf);
	m_cSocket.async_read_some(boost::asio::buffer(m_chRecvBuf, sizeof m_chRecvBuf), 
		std::bind(&CSession::Handle_Read_CallBack, this, std::placeholders::_1, std::placeholders::_2));
}

void CSession::Handle_Read_CallBack(const boost::system::error_code& _ErrCode, size_t _Byte_Transferred)
{
	if (_ErrCode) 
	{
		std::cout << "Handle_Read_CallBack is err, " << _ErrCode.message() << std::endl;
		delete this;
		return;
	}

	if (_Byte_Transferred == 0)
	{
		memset(m_chRecvBuf, 0, sizeof m_chRecvBuf);
		m_cSocket.async_read_some(boost::asio::buffer(m_chRecvBuf, sizeof m_chRecvBuf),
			std::bind(&CSession::Handle_Read_CallBack, this, std::placeholders::_1, std::placeholders::_2));
	}
	else
	{
		m_cSocket.async_send(boost::asio::buffer(m_chRecvBuf, _Byte_Transferred),
			std::bind(&CSession::Handle_Write_CallBack, this, std::placeholders::_1));
	}
}

void CSession::Handle_Write_CallBack(const boost::system::error_code& _ErrCode)
{
	if (_ErrCode)
	{
		std::cout << "Handle_Write_CallBack is err, " << _ErrCode.message() << std::endl;
		delete this;
		return;
	}

	memset(m_chRecvBuf, 0, sizeof m_chRecvBuf);
	m_cSocket.async_read_some(boost::asio::buffer(m_chRecvBuf, sizeof m_chRecvBuf),
		std::bind(&CSession::Handle_Read_CallBack, this, std::placeholders::_1, std::placeholders::_2));
}
