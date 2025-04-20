/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.20
描  述: 使用boost库编写一个tcp同步的客户端
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

int main()
{
	try
	{
		constexpr size_t unBufSize = 1024;
		char chSendBuf[unBufSize] = { 0 };
		size_t unSendBufLen = 0;

		boost::asio::io_context cIOContext;		//上下文服务

		boost::asio::ip::tcp::endpoint cTcpEndPoint(boost::asio::ip::make_address("127.0.0.1"), 32888);
		boost::asio::ip::tcp::socket cSocket(cIOContext);

		boost::system::error_code cErrCode;

		cSocket.connect(cTcpEndPoint, cErrCode);
		if (cErrCode)
		{
			std::cout << "connect failed, code is " << cErrCode.value() << " err msg is " << cErrCode.message() << std::endl;
			return 0;
		}

		std::cout << "Enter message:\n";

		while (true)
		{
			std::cout << "Send: ";
			std::cin.getline(chSendBuf, sizeof chSendBuf - 1);
			unSendBufLen = strlen(chSendBuf);

			cSocket.send(boost::asio::buffer(chSendBuf, unSendBufLen));		//发数据

			std::cout << "Receive: ";
			cSocket.receive(boost::asio::buffer(chSendBuf, unSendBufLen));

			std::cout << chSendBuf << std::endl;
		}
		
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

    return 0;
}

