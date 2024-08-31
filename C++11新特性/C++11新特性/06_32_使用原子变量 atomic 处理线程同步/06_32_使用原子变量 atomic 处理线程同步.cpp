/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_32_使用原子变量 atomic 处理线程同步.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.07
描  述: 使用原子操作保护线程临界资源
备  注:
修改记录:

  1.  日期: 2024.07.07
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <atomic>
#include <thread>

int Test01(void)
{
	volatile std::atomic<int> nValue = 0;
	constexpr unsigned short usFreq = 10000;

	std::thread cTh01([&](const unsigned int _Freq) {
		for (size_t i = 0; i < _Freq; i++)
		{
			++nValue;
			std::cout << "++nValue: " << nValue << '\n';
		}
		}, usFreq);

	std::thread cTh02([&](const unsigned int _Freq) {
		for (size_t i = 0; i < _Freq; i++)
		{
			--nValue;
			std::cout << "--nValue: " << nValue << '\n';
		}
		}, usFreq);

	cTh01.join();
	cTh02.join();

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}
