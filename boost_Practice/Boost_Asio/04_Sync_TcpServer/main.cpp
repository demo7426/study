/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.20
描  述: 使用boost库编写一个tcp同步的回声服务端
备  注:
修改记录:

  1.  日期: 2025.04.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <boost/asio.hpp>
#include <memory>
#include <set>

std::set<std::shared_ptr<std::thread>> g_setThread;

void Session(std::shared_ptr<boost::asio::ip::tcp::socket> _pSocket)
{
	constexpr size_t unBufSize = 1024;
	char chRecvBuf[unBufSize] = { 0 };		//接收数据缓冲区
		
	size_t unRecvValidLen = 0;				//接收数据的有效长度
	boost::system::error_code cErrCode = boost::asio::error::host_not_found;

	while (true)
	{
		unRecvValidLen = _pSocket->read_some(boost::asio::buffer(chRecvBuf, sizeof chRecvBuf - 1), cErrCode);
		if (cErrCode == boost::asio::error::eof)
		{
			std::cout << "Connection closed by peer" << std::endl;
			break;
		}

		if (unRecvValidLen == 0)
			continue;

		std::cout << "receive from " << _pSocket->remote_endpoint().address().to_string() << ", " << chRecvBuf << std::endl;
		_pSocket->send(boost::asio::buffer(chRecvBuf, strlen(chRecvBuf)));
		memset(chRecvBuf, 0, sizeof chRecvBuf);
	}
}

void Server_Run(boost::asio::io_context& _IOContext, unsigned short _Port)
{
	boost::asio::ip::tcp::acceptor cAcceptor(_IOContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), _Port));

	for (;;)
	{
		std::shared_ptr<boost::asio::ip::tcp::socket> pSocket(new boost::asio::ip::tcp::socket(_IOContext));

		cAcceptor.accept(*pSocket);

		auto t = std::make_shared<std::thread>(Session, pSocket);

		g_setThread.emplace(t);					//增加t的引用计数，防止其被析构
	}
}

int main()
{
	try
	{
		boost::asio::io_context cIOContext;		//上下文服务
		Server_Run(cIOContext, 32888);

		for(auto& it : g_setThread)
		{
			it->join();
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

