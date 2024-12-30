/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2024.12.30
��  ��: PNP�����Ľ�WDM����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.30
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <initguid.h>
#include <stdlib.h>

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

typedef struct _DEVICE_EXTENSION_INFO
{
    PDEVICE_OBJECT pFDO;                            //�ϲ�ҵ������
    PDEVICE_OBJECT pPDO;                            //������������
    UNICODE_STRING SysbolicName;
}DEVICE_EXTENSION_INFO, * PDEVICE_EXTENSION_INFO;

NTSTATUS PNP_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;

    IoSkipCurrentIrpStackLocation(Irp);
    lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);

    return lNTStatus;
}

NTSTATUS PNP_RemoveDevice(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;

    IoSkipCurrentIrpStackLocation(Irp);
    lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);
    IoDetachDevice(ptDevExtenInfo->pPDO);

    IoDeleteDevice(ptDevExtenInfo->pFDO);
    IoSetDeviceInterfaceState(&ptDevExtenInfo->SysbolicName, FALSE);

    return lNTStatus;
}

NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

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

    //PNP��������
    static char* pchMinorFuncName[] = {
        "IRP_MN_START_DEVICE                     ",
        "IRP_MN_QUERY_REMOVE_DEVICE              ",
        "IRP_MN_REMOVE_DEVICE                    ",
        "IRP_MN_CANCEL_REMOVE_DEVICE             ",
        "IRP_MN_STOP_DEVICE                      ",
        "IRP_MN_QUERY_STOP_DEVICE                ",
        "IRP_MN_CANCEL_STOP_DEVICE               ",
        "IRP_MN_QUERY_DEVICE_RELATIONS           ",
        "IRP_MN_QUERY_INTERFACE                  ",
        "IRP_MN_QUERY_CAPABILITIES               ",
        "IRP_MN_QUERY_RESOURCES                  ",
        "IRP_MN_QUERY_RESOURCE_REQUIREMENTS      ",
        "IRP_MN_QUERY_DEVICE_TEXT                ",
        "IRP_MN_FILTER_RESOURCE_REQUIREMENTS     ",
        "",
        "IRP_MN_READ_CONFIG                      ",
        "IRP_MN_WRITE_CONFIG                     ",
        "IRP_MN_EJECT                            ",
        "IRP_MN_SET_LOCK                         ",
        "IRP_MN_QUERY_ID                         ",
        "IRP_MN_QUERY_PNP_DEVICE_STATE           ",
        "IRP_MN_QUERY_BUS_INFORMATION            ",
        "IRP_MN_DEVICE_USAGE_NOTIFICATION        ",
        "IRP_MN_SURPRISE_REMOVAL                 "
    };

    static NTSTATUS(*PNP_Handle[])(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp) = {
        PNP_Default,
        PNP_Default,
        PNP_RemoveDevice,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default,
        PNP_Default
    };

    if (ptIOStack->MinorFunction >= _countof(pchMinorFuncName))
        lNTStatus = PNP_Default(DeviceObject, Irp);                                 //����������������ķ���ֵ������ᵼ��ϵͳ����
    else
    {
        KdPrint(("%s\n", pchMinorFuncName[ptIOStack->MinorFunction]));
        lNTStatus = PNP_Handle[ptIOStack->MinorFunction](DeviceObject, Irp);        //����������������ķ���ֵ������ᵼ��ϵͳ����
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

    lNTStatus = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION_INFO), NULL, FILE_DEVICE_UNKNOWN, FILE_AUTOGENERATED_DEVICE_NAME, FALSE, &ptDevObj);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�����豸�ļ�ʧ��\n"));
        return lNTStatus;
    }

    ptDevExtenInfo = ptDevObj->DeviceExtension;
    ptDevExtenInfo->pFDO = ptDevObj;
    ptDevExtenInfo->pPDO = IoAttachDeviceToDeviceStack(ptDevObj, PhysicalDeviceObject);
    if (ptDevExtenInfo->pPDO == NULL)
    {
        IoDeleteDevice(ptDevObj);
        return STATUS_UNSUCCESSFUL;
    }

    //�����豸�ӿڣ��������ӣ�
    IoRegisterDeviceInterface(ptDevExtenInfo->pPDO, &INTERFACEGUID, NULL, &ptDevExtenInfo->SysbolicName);
    KdPrint(("%wZ\n", &ptDevExtenInfo->SysbolicName));
    IoSetDeviceInterfaceState(&ptDevExtenInfo->SysbolicName, TRUE);

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




