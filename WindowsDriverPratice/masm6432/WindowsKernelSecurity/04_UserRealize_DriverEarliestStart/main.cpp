/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.14
描  述: 通过用户态程序修改注册表的方式，实现驱动的最早启动
备  注: 
修改记录:

  1.  日期: 2025.01.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <iostream>
#include <Windows.h>
#include <Shlwapi.h>

using namespace std;

#pragma comment(lib, "Shlwapi.lib")

/// <summary>
/// 通过修改服务控制管理器的方式，实现驱动的最早启动
/// </summary>
/// <param name=""></param>
VOID Realize_DriverEarliestStart01(VOID)
{
    DWORD dwRet = 0;

    SC_HANDLE tSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (!tSCManager)
    {
        cout << "OpenSCManager is err" << endl;
        return;
    }

    SC_HANDLE tService = CreateService(tSCManager,
        TEXT("03_ModifyRegistry_DriverEarliestStart"),
        TEXT("03_ModifyRegistry_DriverEarliestStart"),
        SERVICE_ALL_ACCESS,
        SERVICE_KERNEL_DRIVER,
        SERVICE_SYSTEM_START,
        SERVICE_ERROR_IGNORE,
        TEXT("System32\\Drivers\\03_ModifyRegistry_DriverEarliestStart.sys"),
        TEXT("System Reserved"),
        &dwRet, NULL, NULL, NULL);
    if(!tService)
    {
        cout << "创建服务失败或服务已经存在，需手动cmd执行命令 sc delete 03_ModifyRegistry_DriverEarliestStart 来删除该服务" << endl;
        return;
    }

    StartService(tService, NULL, NULL);

    CloseServiceHandle(tService);
    CloseServiceHandle(tSCManager);
}

/// <summary>
/// 通过修改注册表的方式，实现驱动的最早启动
/// 此方法没有创建服务，只是单纯的修改了注册表而已，经过测试无法正常自动的加载对应驱动
/// </summary>
/// <param name=""></param>
VOID Realize_DriverEarliestStart02(VOID)
{
    DWORD dwStart = SERVICE_SYSTEM_START;
    DWORD dwType = SERVICE_KERNEL_DRIVER;

    SHSetValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\03_ModifyRegistry_DriverEarliestStart"), TEXT("ImagePath"),
        REG_EXPAND_SZ, TEXT("System\\Driver\\03_ModifyRegistry_DriverEarliestStart.sys"), (lstrlen(L"System\\Driver\\03_ModifyRegistry_DriverEarliestStart.sys") + 1) * sizeof(TCHAR));

    SHSetValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\03_ModifyRegistry_DriverEarliestStart"), TEXT("Group"),
        REG_SZ, TEXT("System Reserved"), (lstrlen(L"System Reserved") + 1) * sizeof(TCHAR));

    SHSetValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\03_ModifyRegistry_DriverEarliestStart"), TEXT("Start"),
        REG_DWORD, &dwStart, sizeof dwStart);

    SHSetValue(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\03_ModifyRegistry_DriverEarliestStart"), TEXT("Type"),
        REG_DWORD, &dwType, sizeof dwType);
}

int main()
{
    Realize_DriverEarliestStart01();

    return EXIT_SUCCESS;
}




