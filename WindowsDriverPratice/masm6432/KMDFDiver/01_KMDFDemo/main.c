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

VOID DriverUnload(_In_ WDFDRIVER Driver)
{
    KdPrint(("�����ɹ�ж��\n"));
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
        KdPrint(("������ܴ���ʧ��\n"));
        return lNTStatus;
    }
    else
    {
        KdPrint(("������ܴ����ɹ�\n"));
    }

    return lNTStatus;
}



