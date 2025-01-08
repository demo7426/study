/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.08
描  述: 实现一个支持数字转换KMDf的PNP驱动
备  注:
修改记录:

  1.  日期: 2025.01.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>

#include "Device.h"

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWDFDriverConfig = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWDFDriverConfig, EVT_WDF_Driver_Device_Add);

    //创建框架驱动程序对象
    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &tWDFDriverConfig, WDF_NO_HANDLE);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("创建框架驱动程序对象失败\n"));
        return lNTStatus;
    }

    KdPrint(("驱动加载成功\n"));

    return lNTStatus;
}



