/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.12
描  述: 使用事件实现用户和内核同步
备  注:
修改记录:

  1.  日期: 2024.12.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>
#include <winioctl.h>

using namespace std;

//Function 需要从 0x800 开始，前面的被内核系统占用
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//读数据
#define IO_WRITE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)			//写数据
#define IO_QUERY_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)			//查询信息
#define IO_EVENT_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)			//事件同步

DWORD WINAPI ThreadEvent(LPVOID lpThreadParameter)
{
	HANDLE handEvent = *(PHANDLE)lpThreadParameter;

	cout << "进入 ThreadEvent" << endl;

	WaitForSingleObject(handEvent, INFINITE);

	cout << "退出 ThreadEvent" << endl;

	return 0;
}


int main()
{
	DWORD dwRet;
	HANDLE handThread;
	HANDLE handEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (!handEvent)
	{
		std::cerr << "创建事件失败" << std::endl;
		return EXIT_FAILURE;
	}

	HANDLE hDevice = CreateFile(TEXT("\\\\.\\HelloDDK"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		cout << "设备打开失败, err:" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	handThread = CreateThread(NULL, 0, ThreadEvent, &handEvent, 0, NULL);
	if (handThread == NULL)
	{
		cout << "CreateThread, err:" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	DeviceIoControl(hDevice, IO_EVENT_CODE, &handEvent, sizeof handEvent, NULL, 0, &dwRet, NULL);

	Sleep(2000);

	WaitForSingleObject(handThread, INFINITE);

	CloseHandle(handEvent);
	CloseHandle(hDevice);														//如果 hDevice 未正在被占用，则会先清理 hDevice，再关闭 hDevice

	cout << "退出主程序" << endl;

	return EXIT_SUCCESS;
}

