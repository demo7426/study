/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_37_promise 类的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.07
描  述: 使用promise对象在线程内部设置值，使用future对象接收返回值 
备  注:	每一个promise对象内部都维护者一个future对象
修改记录:

  1.  日期: 2024.07.07
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <thread>
#include <future>
#include <chrono>

void CalledFunc(std::promise<std::string>& _Promise)
{
	std::this_thread::sleep_for(std::chrono::seconds(3));
	_Promise.set_value("Cristiano is fottball player.");
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int Test01(void)
{
	std::promise<std::string> cPromise;
	std::future<std::string> cFuture = cPromise.get_future();
	
	std::thread cTh01(CalledFunc, std::ref(cPromise));
	 
	std::cout << "线程返回值为: " << cFuture.get() << std::endl;

	cTh01.join();
		
	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}

