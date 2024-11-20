/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.20
描  述: 缓冲区读写数据，查询文件大小测试
备  注:
修改记录:

  1.  日期: 2024.11.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/
#include <iostream>
#include <Windows.h>
#include <winioctl.h>

using namespace std;

#define IOTEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)

int main()
{
	DWORD dwRet;
	CHAR chBuf[1024] = { 0 };

	HANDLE hDevice = CreateFile(TEXT("\\\\.\\HelloDDK"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		cout << "设备打开失败, err:" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	if (!ReadFile(hDevice, chBuf, sizeof chBuf, &dwRet, NULL))
	{
		cout << "ReadFile is err:" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	cout << chBuf << endl;
	cout << "成功读取长度为: " << dwRet << endl;

	memset(chBuf, 0, sizeof chBuf);
	memcpy(chBuf, "这是一段来自于用户层的字符串", strlen("这是一段来自于用户层的字符串"));

	WriteFile(hDevice, chBuf, strlen("这是一段来自于用户层的字符串"), &dwRet, NULL);
	cout << "成功写入长度为: " << dwRet << endl;

	cout << "文件大小为: " << GetFileSize(hDevice, NULL) << endl;
	
	//DeviceIoControl(hDevice, IOTEST, NULL, 0, NULL, 0, &dwRet, NULL);
	CloseHandle(hDevice);														//如果 hDevice 未正在被占用，则会先清理 hDevice，再关闭 hDevice

	return EXIT_SUCCESS;
}

