/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.05
��  ��: wdf����ʾ��
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.05
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>
#include <wdmsec.h>

VOID EVT_WDF_Device_File_Create(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request, _In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Close(_In_ WDFFILEOBJECT FileObject);

VOID EVT_WDF_File_Cleanup(_In_ WDFFILEOBJECT FileObject);

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

