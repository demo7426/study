/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.19
描  述: 串口过滤驱动测试
备  注:
修改记录:

  1.  日期: 2024.02.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/
#include <iostream>
#include <Windows.h>
#include <winioctl.h>

using namespace std;

int main()
{
	DWORD dwRet;
	CHAR chBuf[] = { 'a', 'b', 'c' };

	HANDLE hDevice = CreateFile(TEXT("\\\\.\\COM1"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		cout << "设备打开失败, err:" << GetLastError() << endl;
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < sizeof(chBuf) / sizeof(chBuf[0]); i++)
	{
		WriteFile(hDevice, chBuf + i, 1, &dwRet, NULL);
		if (dwRet == 0)
		{
			printf("WriteFile is err,  i = %d\n", i);
		}
	}
	
	CloseHandle(hDevice);														//如果 hDevice 未正在被占用，则会先清理 hDevice，再关闭 hDevice

	return EXIT_SUCCESS;
}

