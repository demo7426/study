/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: 使用信号量、互斥锁进行线程同步
备  注:	CreateSemaphore--创建信号量
		ReleaseSemaphore--释放信号量
		CreateMutex--创建互斥锁
		ReleaseMutex--释放互斥锁
修改记录:

  1.  日期: 2024.12.06
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

DWORD WINAPI ThreadSemaphore(LPVOID lpThreadParameter)
{
	std::cout << "进入线程\n";

	if (!lpThreadParameter)
		return EXIT_FAILURE;

	PHANDLE phandSemaphore = (PHANDLE)lpThreadParameter;

	ReleaseSemaphore(*phandSemaphore, 1, NULL);

	std::cout << "退出线程\n";

	return EXIT_SUCCESS;
}

/// <summary>
/// 信号量线程同步测试
/// </summary>
/// <param name=""></param>
INT32 Semaphore_Test01(VOID)
{
	HANDLE handSemaphore = CreateSemaphore(NULL, 2, 2, NULL);
	if (!handSemaphore)
	{
		std::cerr << "创建信号量失败" << std::endl;
		return EXIT_FAILURE;
	}

	WaitForSingleObject(handSemaphore, INFINITE);
	WaitForSingleObject(handSemaphore, INFINITE);

	CreateThread(NULL, 0, ThreadSemaphore, &handSemaphore, 0, NULL);

	WaitForSingleObject(handSemaphore, INFINITE);

	std::cout << "结束主线程" << std::endl;
}

DWORD WINAPI ThreadMutex(LPVOID lpThreadParameter)
{
	if (!lpThreadParameter)
		return EXIT_FAILURE;

	PHANDLE phandMutex = (PHANDLE)lpThreadParameter;

	WaitForSingleObject(*phandMutex, INFINITE);

	std::cout << "进入线程\n";

	ReleaseMutex(*phandMutex);

	std::cout << "退出线程\n";

	return EXIT_SUCCESS;
}

/// <summary>
/// 互斥锁线程同步测试
/// </summary>
/// <param name=""></param>
INT32 Mutex_Test02(VOID)
{
	HANDLE handThread[2] = { NULL };

	HANDLE handMutex = CreateMutex(NULL, FALSE, NULL);
	if (!handMutex)
	{
		std::cerr << "创建互斥锁失败" << std::endl;
		return EXIT_FAILURE;
	}

	handThread[0] = CreateThread(NULL, 0, ThreadMutex, &handMutex, 0, NULL);
	handThread[1] = CreateThread(NULL, 0, ThreadMutex, &handMutex, 0, NULL);

	WaitForMultipleObjects(2, handThread, TRUE, INFINITE);

	std::cout << "结束主线程" << std::endl;
}

int main()
{
	//Semaphore_Test01();
	Mutex_Test02();

	return EXIT_SUCCESS;
}
