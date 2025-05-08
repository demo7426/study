/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.4     新建日期: 2025.04.21
描  述: 使用boost库编写一个tcp异步的回声服务端
备  注: 
修改记录:

  1.  日期: 2025.04.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

  2.  日期: 2025.04.22
	  作者: 钱锐
	  内容:
		  1) 采用智能指针实现一个伪闭包，解决上一个版本当客户端突然关闭时CSession有可能多次delete this;导致内存异常bug；
	  版本:V0.1.1

  3.  日期: 2025.04.23
	  作者: 钱锐
	  内容:
		  1) 增加发送队列实现全双工通信；
	  版本:V0.1.2

  4.  日期: 2025.05.06
	  作者: 钱锐
	  内容:
		  1) 扩展逻辑系统单独处理接收到数据节点的功能；
	  版本:V0.1.3

  5.  日期: 2025.05.08
	  作者: 钱锐
	  内容:
		  1) 扩展支持两种方式实现服务器的优雅退出功能；
	  版本:V0.1.4

*************************************************/

#include <iostream>

#include "Server.h"			

#if 1														//使用C标准实现服务器的优雅退出

static bool g_bQuit = false;								//是否退出程序;false--不退出程序;true--退出程序;
static std::mutex g_cMutQuit;								//用于控制程序是否退出的互斥锁	
static std::condition_variable g_cConditionVar_Quit;		//用于控制程序是否退出的条件变量	

/// <summary>
/// 异常信号回调函数
/// </summary>
/// <param name="_Signal"></param>
static void Sig_Handler(int _Signal)
{
	if (_Signal == SIGINT || _Signal == SIGTERM)
	{
		std::unique_lock<std::mutex> cUniqueLock(g_cMutQuit);
		g_bQuit = true;
		g_cConditionVar_Quit.notify_one();
	}
}

int main()
{
	try
	{
		boost::asio::io_context cIO_Context;
		
		std::thread cNetWorkThread([&cIO_Context] {
			unsigned short ushPortNo = 32888;

			CServer cServer(cIO_Context, ushPortNo);
			cIO_Context.run();
			});

		//注册异常信号及其回调函数
		signal(SIGINT, Sig_Handler);					
		signal(SIGTERM, Sig_Handler);

		while (!g_bQuit)									//使用while循环检测，防止g_cConditionVar_Quit被唤醒后可能出现的程序虚假结束
		{
			std::unique_lock<std::mutex> cUniqueLock(g_cMutQuit); 
			g_cConditionVar_Quit.wait(cUniqueLock);
		}

		cIO_Context.stop();
		cNetWorkThread.join();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

#else															//使用BOOST库实现服务器的优雅退出		

int main()
{
	try
	{
		boost::asio::io_context cIO_Context;
		boost::asio::signal_set cSignalSet(cIO_Context, SIGINT, SIGTERM);

		cSignalSet.async_wait([&cIO_Context](auto, auto) {		//异步等待异常信号的出发
			cIO_Context.stop();
			});

		unsigned short ushPortNo = 32888;

		CServer cServer(cIO_Context, ushPortNo);
		cIO_Context.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

#endif

