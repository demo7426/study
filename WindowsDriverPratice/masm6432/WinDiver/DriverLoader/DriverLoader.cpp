/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	DriverLoader.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.12
描  述: 实现一个windows 驱动的自动加载器
备  注:
修改记录:

  1.  日期: 2024.11.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	SC_HANDLE hScManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);		//创建一个SC管理对象
	if (hScManager == NULL)
	{
		cout << "创建管理对象失败" << endl;
		return EXIT_FAILURE;
	}

	SC_HANDLE hService = CreateService(hScManager, TEXT("mydriver"), TEXT("mydriver"),
		SERVER_ALL_ACCESS, SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
		TEXT("./02_02_FirstDiverDemo.sys"), NULL, NULL, NULL, NULL, NULL);	//创建一个服务
	if (hService == NULL)
	{
		if (GetLastError() == ERROR_SERVICE_EXISTS)
		{
			hService = OpenService(hScManager, TEXT("mydriver"), SERVER_ALL_ACCESS);
			if (hService == NULL)
			{
				cout << "打开服务失败" << endl;
				CloseServiceHandle(hScManager);
				return EXIT_FAILURE;
			}
		}
		else
		{
			cout << "创建服务失败" << endl;
			CloseServiceHandle(hScManager);
			return EXIT_FAILURE;
		}
	}

	if (!StartService(hService, NULL, NULL))										//启动服务
	{
		cout << "启动服务失败: err = " << GetLastError() <<  endl;
		CloseServiceHandle(hService);
		CloseServiceHandle(hScManager);
		return EXIT_FAILURE;
	}

	getchar();

	SERVICE_STATUS tStatus;

	ControlService(hService, SERVICE_CONTROL_STOP, &tStatus);				//停止服务
	DeleteService(hService);												//删除服务

	CloseServiceHandle(hService);
	CloseServiceHandle(hScManager);

	return EXIT_SUCCESS;
}

