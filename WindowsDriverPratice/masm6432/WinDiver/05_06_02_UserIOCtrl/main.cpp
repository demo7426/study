/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.22
描  述: 其它IO控制
备  注:
修改记录:

  1.  日期: 2024.11.22
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
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)			//读数据
#define IO_WRITE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)			//写数据
#define IO_QUERY_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)			//查询信息

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


	DeviceIoControl(hDevice, IO_READ_CODE, chBuf, sizeof chBuf, chBuf, sizeof chBuf, &dwRet, NULL);
	cout << "成功读取的数据长度: " << dwRet << " " << chBuf << endl;

	memset(chBuf, 0, sizeof chBuf);
	memcpy(chBuf, "这是一段来自于用户层的字符串", strlen("这是一段来自于用户层的字符串"));
	DeviceIoControl(hDevice, IO_WRITE_CODE, chBuf, strlen(chBuf), chBuf, sizeof chBuf, &dwRet, NULL);
	cout << "成功写入的数据长度: " << dwRet << endl;

	memset(chBuf, 0, sizeof chBuf);
	DeviceIoControl(hDevice, IO_QUERY_CODE, NULL, 0, NULL, 0, &dwRet, NULL);
	cout << "文件大小:" << dwRet << endl;

	CloseHandle(hDevice);														//如果 hDevice 未正在被占用，则会先清理 hDevice，再关闭 hDevice

	return EXIT_SUCCESS;
}

