/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.05.22
描  述: 使用beast库编写一个websocket服务器
备  注: 直接从tcp socket升级到websocket,后续可以结合http服务器，从http的post升级指令把socket升级到websocket
修改记录:

  1.  日期: 2025.05.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include "WebSocketServer.h"

int main()
{
	boost::asio::io_context cIO_Context;
	CWebSocketServer cWebSocketServer(cIO_Context, 32888);

	cWebSocketServer.StartAccept();
	cIO_Context.run();

	return EXIT_SUCCESS;
}
