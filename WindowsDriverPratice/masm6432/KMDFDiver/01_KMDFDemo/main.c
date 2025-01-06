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
#include <wdmsec.h>

VOID EVT_WDF_Device_File_Create(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request, _In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Close(_In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Cleanup(_In_ WDFFILEOBJECT FileObject);

VOID DriverUnload(_In_ WDFDRIVER Driver)
{
    KdPrint(("驱动成功卸载\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWdfDriverConfig = { 0 };
    WDFDRIVER tWDFDriver = { 0 };
    PWDFDEVICE_INIT ptWDFDevInit = NULL;
    WDF_FILEOBJECT_CONFIG tWDFFileConfig = { 0 };
    UNICODE_STRING tDevName = RTL_CONSTANT_STRING(L"\\Device\\HelloWDF");
    UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloWDF");
    WDFDEVICE tWDFDev = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWdfDriverConfig, NULL);
    tWdfDriverConfig.DriverInitFlags = WdfDriverInitNonPnpDriver;
    tWdfDriverConfig.EvtDriverUnload = DriverUnload;

    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &tWdfDriverConfig, &tWDFDriver);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("驱动框架创建失败\n"));
        return lNTStatus;
    }
    else
    {
        KdPrint(("驱动框架创建成功\n"));
    }

    //创建驱动的一个设备对象
    ptWDFDevInit = WdfControlDeviceInitAllocate(tWDFDriver, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RWX_RES_RWX);
    if (!ptWDFDevInit)
    {
        KdPrint(("WdfControlDeviceInitAllocate is err.\n"));
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //申请设备名称
    lNTStatus = WdfDeviceInitAssignName(ptWDFDevInit, &tDevName);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备名分配失败\n"));
        return lNTStatus;
    }

    //设置文件属性
    WDF_FILEOBJECT_CONFIG_INIT(&tWDFFileConfig, EVT_WDF_Device_File_Create, EVT_WDF_File_Close, EVT_WDF_File_Cleanup);
    WdfDeviceInitSetFileObjectConfig(ptWDFDevInit, &tWDFFileConfig, WDF_NO_OBJECT_ATTRIBUTES);

    lNTStatus = WdfDeviceCreate(&ptWDFDevInit, WDF_NO_OBJECT_ATTRIBUTES, &tWDFDev);      //创建设备文件
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备创建失败\n"));
        return lNTStatus;
    }

    lNTStatus = WdfDeviceCreateSymbolicLink(tWDFDev, &tSysbolicLinkName);               //创建符号链接文件
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("符号链接创建失败\n"));
        return lNTStatus;
    }

    WdfControlFinishInitializing(tWDFDev);

    return lNTStatus;
}

VOID EVT_WDF_Device_File_Create(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request, _In_ WDFFILEOBJECT FileObject)
{
    KdPrint(("EVT_WDF_Device_File_Create is enter.\n"));
    WdfRequestComplete(Request, STATUS_SUCCESS);
}

VOID EVT_WDF_File_Close(_In_ WDFFILEOBJECT FileObject)
{
    KdPrint(("EVT_WDF_File_Close is enter.\n"));
}

VOID EVT_WDF_File_Cleanup(_In_ WDFFILEOBJECT FileObject)
{
    KdPrint(("EVT_WDF_File_Cleanup is enter.\n"));
}

