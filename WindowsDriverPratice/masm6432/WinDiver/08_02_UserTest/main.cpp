/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.15
描  述: 多次出发异步irq，在最后再响应irq中断
备  注: 
修改记录:

  1.  日期: 2024.12.15
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

using namespace std;

/// <summary>
/// 异步读取文件数据测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
INT32 Test01(VOID)
{
	OVERLAPPED tOverLapped = { NULL };
	DWORD dwRet = 0;

	HANDLE hOpenFile = CreateFile(L"\\\\.\\HelloDDK",
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

	for (size_t i = 0; i < 100; i++)
	{
		ReadFile(hOpenFile, NULL, 0, &dwRet, &tOverLapped);		//如果使用 FILE_FLAG_OVERLAPPED打开 hFile 参数，则需要指向 OVERLAPPED 结构的指针
	}

	CloseHandle(hOpenFile);
	hOpenFile = NULL;

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}

