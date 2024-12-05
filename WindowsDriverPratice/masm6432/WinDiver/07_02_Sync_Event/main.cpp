/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.05
描  述: 使用时间进行线程同步
备  注:	CreateEvent--创建事件
		SetEvent--释放事件
		WaitForSingleObject--等待事件
		WaitForMultipleObjects--等待多个事件
修改记录:

  1.  日期: 2024.12.05
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadProc(LPVOID lpThreadParameter)
{
	std::cout << "进入线程\n";

	if (!lpThreadParameter)
		return EXIT_FAILURE;

	PHANDLE phandEvent = (PHANDLE)lpThreadParameter;

	SetEvent(*phandEvent);			//释放事件

	std::cout << "退出线程\n";

	return EXIT_SUCCESS;
}

int main()
{
	HANDLE handEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (!handEvent)
	{
		std::cerr << "创建事件失败" << std::endl;
		return EXIT_FAILURE;
	}

	CreateThread(NULL, 0, ThreadProc, &handEvent, 0, NULL);

	WaitForSingleObject(handEvent, INFINITE);

	std::cout << "结束主线程" << std::endl;

	return EXIT_SUCCESS;
}
