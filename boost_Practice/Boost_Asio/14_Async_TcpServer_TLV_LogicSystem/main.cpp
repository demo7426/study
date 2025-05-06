/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.3     新建日期: 2025.04.21
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

*************************************************/

#include <iostream>

#include "Server.h"

int main()
{
	try
	{
		boost::asio::io_context cIO_Context;
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


