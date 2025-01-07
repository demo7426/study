/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.07
��  ��: ʵ��WDF��PNP(���弴��)
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>

#include "Device.h"

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWDFDriverConfig = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWDFDriverConfig, EVT_WDF_Driver_Device_Add);

    //������������������
    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &tWDFDriverConfig, WDF_NO_HANDLE);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("������������������ʧ��\n"));
        return lNTStatus;
    }

    KdPrint(("�������سɹ�\n"));

    return lNTStatus;
}



