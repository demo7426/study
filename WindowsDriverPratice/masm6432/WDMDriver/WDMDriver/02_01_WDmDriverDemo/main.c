/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2024.12.27
��  ��: ��дһ��wdmʾ������
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.27
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>

typedef struct _DEVICE_EXTENSION_INFO
{
    PDEVICE_OBJECT pFDO;                            //�ϲ�ҵ������
    PDEVICE_OBJECT pPDO;                            //������������
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
        KdPrint(("�����豸�ļ�ʧ��\n"));
        return lNTStatus;
    }

    lNTStatus = IoCreateSymbolicLink(&tSysbolicName, &tDevName);
    if (!NT_SUCCESS(lNTStatus))
    {
        IoDeleteDevice(ptDevObj);
        KdPrint(("�������������ļ�ʧ��\n"));
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
    KdPrint(("����ж�سɹ�\n"));
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

    KdPrint(("�������سɹ�\n"));

    return lNTStatus;
}




