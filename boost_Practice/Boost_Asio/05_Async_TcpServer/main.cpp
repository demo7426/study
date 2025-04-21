/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.21
描  述: 使用boost库编写一个tcp异步的回声服务端
备  注:
修改记录:

  1.  日期: 2025.04.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

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


