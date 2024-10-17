/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.17
描  述:	实现一个最简易的 版本windows10 版本号22H2 驱动程序
备  注:
修改记录:

  1.  日期: 2024.10.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 驱动卸载回调函数
/// </summary>
/// <param name="driver">内核分发器分配的对象</param>
/// <returns></returns>
NTSTATUS DriverUnload(PDRIVER_OBJECT driver)
{
    UNREFERENCED_PARAMETER(driver);

    DbgPrint("%s is entry.\n", __FUNCDNAME__);
    return STATUS_SUCCESS;
}

/// <summary>
/// 驱动入口函数
/// </summary>
/// <param name="driver">内核分发器分配的对象</param>
/// <param name="res_path">字符串信息</param>
/// <returns></returns>
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING res_path)
{
    UNREFERENCED_PARAMETER(res_path);

    driver->DriverUnload = DriverUnload;

    DbgPrint("%s is entry.\n", __FUNCDNAME__);

    return STATUS_SUCCESS;
}


