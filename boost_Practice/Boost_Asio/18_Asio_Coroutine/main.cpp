/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.14
描  述: 使用boost asio 协程库编写一个tcp异步的回声服务端
备  注:
修改记录:

  1.  日期: 2025.05.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/write.hpp>

#include <iostream>

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;

namespace this_coro = boost::asio::this_coro;

awaitable<void> Echo(tcp::socket _Socket)
{
	try
	{
		constexpr size_t unRecvBufSize = 4096;
		char chRecvBuf[unRecvBufSize] = { 0 };
		size_t unRecvBufValidLen = 0;

		while (1)
		{
			unRecvBufValidLen = co_await _Socket.async_read_some(boost::asio::buffer(chRecvBuf, unRecvBufSize), use_awaitable);
			co_await _Socket.async_send(boost::asio::buffer(chRecvBuf, unRecvBufValidLen), use_awaitable);
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Echo exceptio is" << e.what() << std::endl;
	}
}

awaitable<void> Listener()
{
	auto cExecutor = co_await this_coro::executor;					//获取当前线程的执行器
	tcp::acceptor cAcceptor(cExecutor, { tcp::v4(), 32888 });

	for (;;)
	{
		tcp::socket cSocket = co_await cAcceptor.async_accept(use_awaitable);
		co_spawn(cExecutor, Echo(std::move(cSocket)), detached);	//启动监听协程 Listener，后台运行（detached）
	}
}

int main()
{
	try
	{
		boost::asio::io_context cIO_Context(1);						//1--io_context使用的线程数量
		boost::asio::signal_set cSignal_Set(cIO_Context, SIGINT, SIGTERM);
		cSignal_Set.async_wait([&](auto, auto) {
			cIO_Context.stop();
			});

		co_spawn(cIO_Context, Listener(), detached);
		cIO_Context.run();											//cIO_Context运行起来后，才有执行器
	}
	catch (const std::exception& e)
	{
		std::cout << "Exceptio is" << e.what() << std::endl;
	}

	return EXIT_SUCCESS;
}


