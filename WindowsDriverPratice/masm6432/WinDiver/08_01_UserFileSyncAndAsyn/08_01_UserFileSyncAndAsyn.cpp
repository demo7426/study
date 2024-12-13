/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.13
描  述: 用户态读写文件同步、异步操作
备  注: WriteFile--支持同步或异步写入数据
		ReadFileEx--异步读取数据
		SleepEx--挂起当前线程，直到满足指定的条件。 发生以下情况之一时，将继续执行：
								调用 I / O 完成回调函数。
								异步过程调用(APC) 排队到线程。
								超时间隔已过。
		
修改记录:

  1.  日期: 2024.12.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

using namespace std;

VOID WINAPI ReadFile_Overlapped(_In_    DWORD dwErrorCode,
	_In_    DWORD dwNumberOfBytesTransfered,
	_Inout_ LPOVERLAPPED lpOverlapped)
{
	cout << "ReadFile_Overlapped 函数被调用\n";
}

/// <summary>
/// 同步测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
INT32 Sync_Test01(VOID)
{
	DWORD dwRet = 0;

	HANDLE hOpenFile = CreateFile(L"test.txt",
		GENERIC_ALL,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		cerr << "打开文件失败" << endl;
		return EXIT_FAILURE;
	}

	WriteFile(hOpenFile, "文本数据", strlen("文本数据"), &dwRet, NULL);

	CloseHandle(hOpenFile);
	hOpenFile = NULL;

	return EXIT_SUCCESS;
}

/// <summary>
/// 异步测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
INT32 Asyn_Test02(VOID)
{
	OVERLAPPED tOverLapped = { NULL };
	DWORD dwRet = 0;
	CHAR chReadBuf[1024] = { 0 };

	HANDLE hOpenFile = CreateFile(L"test.txt",
		GENERIC_ALL,
		FILE_SHARE_WRITE | FILE_SHARE_READ,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,//必须新增 FILE_FLAG_OVERLAPPED 标志打开或创建文件，显示指出打开的文件支持异步读写其内部数据，具体说明查看msdn
		NULL
	);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		cerr << "打开文件失败" << endl;
		cerr << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	tOverLapped.hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	//异步写入数据，成功写入数据后，tOverLapped.hEvent会被写为
	WriteFile(hOpenFile, "异步写入的文本数据", strlen("异步写入的文本数据"), &dwRet, &tOverLapped);

	WaitForSingleObject(tOverLapped.hEvent, INFINITE);

	ReadFileEx(hOpenFile, chReadBuf, sizeof chReadBuf, &tOverLapped, ReadFile_Overlapped);
	SleepEx(INFINITE, TRUE);	/*挂起当前线程，直到满足指定的条件。 发生以下情况之一时，将继续执行：
								调用 I / O 完成回调函数。
								异步过程调用(APC) 排队到线程。
								超时间隔已过。*/

	cout << chReadBuf << endl;

	CloseHandle(hOpenFile);
	hOpenFile = NULL;

	return EXIT_SUCCESS;
}

int main()
{
#if 0
	Sync_Test01();
#else
	Asyn_Test02();
#endif // 1


	return EXIT_SUCCESS;
}

