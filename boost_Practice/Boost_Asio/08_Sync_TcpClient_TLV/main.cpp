/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.25
描  述: 使用boost库编写一个tcp同步的tlv格式客户端
备  注: 
修改记录:

  1.  日期: 2025.04.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <boost/asio.hpp>

int main()
{
	try
	{
		constexpr size_t unBufSize = 65537;
		char chSendBuf[unBufSize] = { 0 };
		size_t unSendBufLen = 0;
		constexpr static unsigned char uchTLVLen_OccupyBytes = 2;			//TLV格式，长度所占用的总字节数
		const char* chData = "Hello world";

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
			memset(chSendBuf, 0, sizeof(chSendBuf));
			std::cin.getline(chSendBuf + uchTLVLen_OccupyBytes, unBufSize - uchTLVLen_OccupyBytes);

			unSendBufLen = strlen(chSendBuf + uchTLVLen_OccupyBytes);
			*(unsigned short*)chSendBuf = unSendBufLen;

			for (size_t i = 0; i < 100000; i++)		//测试数据量较大时，服务器是否处理了TCP数据粘包
			{
				cSocket.send(boost::asio::buffer(chSendBuf, unSendBufLen + uchTLVLen_OccupyBytes));		//发数据
			}

			for (size_t i = 0; i < 100000; i++)
			{
				std::cout << "Receive: " << i << " ";
				memset(chSendBuf, 0, sizeof(chSendBuf));
				cSocket.receive(boost::asio::buffer(chSendBuf, unSendBufLen));
				std::cout << chSendBuf << std::endl;
			}
		}

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}

