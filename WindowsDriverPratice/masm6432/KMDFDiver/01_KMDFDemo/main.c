/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.05
描  述: wdf驱动示例
备  注:
修改记录:

  1.  日期: 2025.01.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>

VOID DriverUnload(_In_ WDFDRIVER Driver)
{
    KdPrint(("驱动成功卸载\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWdfDriverConfig = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWdfDriverConfig, NULL);
    tWdfDriverConfig.DriverInitFlags = WdfDriverInitNonPnpDriver;
    tWdfDriverConfig.EvtDriverUnload = DriverUnload;

    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &tWdfDriverConfig, WDF_NO_HANDLE);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("驱动框架创建失败\n"));
        return lNTStatus;
    }
    else
    {
        KdPrint(("驱动框架创建成功\n"));
    }

    return lNTStatus;
}



