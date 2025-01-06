/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.06
��  ��: ʵ��WDF��IO����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.06
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>
#include <wdmsec.h>

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//������

VOID EVT_WDF_Device_File_Create(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request, _In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Close(_In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Cleanup(_In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode);

VOID DriverUnload(_In_ WDFDRIVER Driver)
{
    KdPrint(("�����ɹ�ж��\n"));
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

    WDF_IO_QUEUE_CONFIG tWDFIOQueueConfig = { 0 };
    WDFQUEUE tWDFQueue = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWdfDriverConfig, NULL);
    tWdfDriverConfig.DriverInitFlags = WdfDriverInitNonPnpDriver;
    tWdfDriverConfig.EvtDriverUnload = DriverUnload;

    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &tWdfDriverConfig, &tWDFDriver);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("������ܴ���ʧ��\n"));
        return lNTStatus;
    }
    else
    {
        KdPrint(("������ܴ����ɹ�\n"));
    }

    //����������һ���豸����
    ptWDFDevInit = WdfControlDeviceInitAllocate(tWDFDriver, &SDDL_DEVOBJ_SYS_ALL_ADM_RWX_WORLD_RWX_RES_RWX);
    if (!ptWDFDevInit)
    {
        KdPrint(("WdfControlDeviceInitAllocate is err.\n"));
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    //�����豸����
    lNTStatus = WdfDeviceInitAssignName(ptWDFDevInit, &tDevName);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�豸������ʧ��\n"));
        return lNTStatus;
    }

    //�����ļ�����
    WDF_FILEOBJECT_CONFIG_INIT(&tWDFFileConfig, EVT_WDF_Device_File_Create, EVT_WDF_File_Close, EVT_WDF_File_Cleanup);
    WdfDeviceInitSetFileObjectConfig(ptWDFDevInit, &tWDFFileConfig, WDF_NO_OBJECT_ATTRIBUTES);

    lNTStatus = WdfDeviceCreate(&ptWDFDevInit, WDF_NO_OBJECT_ATTRIBUTES, &tWDFDev);      //�����豸�ļ�
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�豸����ʧ��\n"));
        return lNTStatus;
    }

    //��ʼ��IO����
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&tWDFIOQueueConfig, WdfIoQueueDispatchSequential);
    tWDFIOQueueConfig.EvtIoDeviceControl = EVT_WDF_IO_Queue_IO_Device_Control;

    lNTStatus = WdfIoQueueCreate(tWDFDev, &tWDFIOQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &tWDFQueue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("���д���ʧ��\n"));
        return lNTStatus;
    }

    lNTStatus = WdfDeviceCreateSymbolicLink(tWDFDev, &tSysbolicLinkName);               //�������������ļ�
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�������Ӵ���ʧ��\n"));
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

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    KdPrint(("EVT_WDF_IO_Queue_IO_Device_Control is enter.\n"));

    WdfRequestComplete(Request, STATUS_SUCCESS);
}

