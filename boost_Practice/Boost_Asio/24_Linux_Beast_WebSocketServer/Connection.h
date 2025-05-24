/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Connection.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.22
描  述: 处理WebSocket连接
备  注: 
修改记录:

  1.  日期: 2025.05.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#pragma once

#include <queue>
#include <mutex>
#include <memory>

#include "boost/beast.hpp"
#include "boost/asio.hpp"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "boost/uuid/uuid_io.hpp"

class CConnection : public std::enable_shared_from_this<CConnection>
{
public:
	CConnection(boost::asio::io_context& _IO_Context);
	
	std::string GetUuid();

	boost::asio::ip::tcp::socket& GetSocket();

	void AsyncAccept();

private:
	std::unique_ptr<boost::beast::websocket::stream<boost::beast::tcp_stream>> m_pWebSocket;
	std::string m_strUuid = "";

	boost::asio::io_context& m_cIO_Context;

	boost::beast::flat_buffer m_cRecvFlatBuf;		//接收缓冲

	std::queue<std::string> m_queSend;				//发送队列
	std::mutex m_mutSend;							//发送队列互斥量

	std::size_t m_unRecvCounter = 0;				//接收到数据的次数

	void Start();

	void AsyncSend(std::string _Msg);
};
