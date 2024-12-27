/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2024.12.27
描  述: 编写一个wdm示例驱动
备  注:
修改记录:

  1.  日期: 2024.12.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <ntddk.h>

typedef struct _DEVICE_EXTENSION_INFO
{
    PDEVICE_OBJECT pFDO;                            //上层业务驱动
    PDEVICE_OBJECT pPDO;                            //物理总线驱动
}DEVICE_EXTENSION_INFO, *PDEVICE_EXTENSION_INFO;

NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    KdPrint(("Driver_Dispatch is enter.\n"));

    Irp->IoStatus.Information = 0;
    Irp->IoStatus.Status = lNTStatus;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);
    
    return lNTStatus;
}

NTSTATUS Driver_PNP_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION ptIOStack = IoGetCurrentIrpStackLocation(Irp);

    KdPrint(("Driver_PNP_Dispatch is enter.\n"));

    if (ptIOStack->MinorFunction == IRP_MN_REMOVE_DEVICE)
    {
        UNICODE_STRING tSysbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloWDM");

        IoSkipCurrentIrpStackLocation(Irp);
        lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);
        IoDetachDevice(ptDevExtenInfo->pPDO);

        IoDeleteDevice(ptDevExtenInfo->pFDO);
        IoDeleteSymbolicLink(&tSysbolicName);
    }
    else
    {
        IoSkipCurrentIrpStackLocation(Irp);
        lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);
    }

    return lNTStatus;
}

NTSTATUS Driver_AddDevice(_In_ struct _DRIVER_OBJECT* DriverObject, _In_ struct _DEVICE_OBJECT* PhysicalDeviceObject)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    UNICODE_STRING tDevName = RTL_CONSTANT_STRING(L"\\Device\\HelloWDM");
    UNICODE_STRING tSysbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloWDM");
    PDEVICE_OBJECT ptDevObj = NULL;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = NULL;

    lNTStatus = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION_INFO), &tDevName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDevObj);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("创建设备文件失败\n"));
        return lNTStatus;
    }

    lNTStatus = IoCreateSymbolicLink(&tSysbolicName, &tDevName);
    if (!NT_SUCCESS(lNTStatus))
    {
        IoDeleteDevice(ptDevObj);
        KdPrint(("创建符号链接文件失败\n"));
        return lNTStatus;
    }

    ptDevExtenInfo = ptDevObj->DeviceExtension;
    ptDevExtenInfo->pFDO = ptDevObj;
    ptDevExtenInfo->pPDO = IoAttachDeviceToDeviceStack(ptDevObj, PhysicalDeviceObject);
    if (ptDevExtenInfo->pPDO == NULL)
    {
        IoDeleteDevice(ptDevObj);
        IoDeleteSymbolicLink(&tSysbolicName);
        return STATUS_UNSUCCESSFUL;
    }

    ptDevObj->Flags |= DO_BUFFERED_IO | DO_POWER_PAGABLE;
    ptDevObj->Flags &= ~DO_DEVICE_INITIALIZING;

    return lNTStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;
    
    for (size_t i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
    {
        DriverObject->MajorFunction[i] = Driver_Dispatch;
    }
    
    DriverObject->MajorFunction[IRP_MJ_PNP] = Driver_PNP_Dispatch;
    DriverObject->DriverExtension->AddDevice = Driver_AddDevice;

    KdPrint(("驱动加载成功\n"));

    return lNTStatus;
}




