/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.12
��  ��: ����PNP����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.12
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>

#include "Driver.h"
#include "Device.h"

/// <summary>
/// ��ӡinf�ļ���ע�����ӵĲ���
/// </summary>
/// <param name="_Driver">��������</param>
/// <returns></returns>
static NTSTATUS PrintRegeditParameter(IN WDFDRIVER _Driver);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_DRIVER_CONFIG tWDFDriverConfig = { 0 };
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    WDFDRIVER tWDFDriver = { 0 };

    WDF_DRIVER_CONFIG_INIT(&tWDFDriverConfig, EVT_WDF_Driver_Device_Add);

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DRIVER_CONTEXT);  //���������Ķ���Ĵ�������

    //������������������
    lNTStatus = WdfDriverCreate(DriverObject, RegistryPath, &tWDFObjAttr, &tWDFDriverConfig, &tWDFDriver);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("������������������ʧ��\n"));
        return lNTStatus;
    }

    PrintRegeditParameter(tWDFDriver);

    KdPrint(("�������سɹ�\n"));

    return lNTStatus;
}

static NTSTATUS PrintRegeditParameter(IN WDFDRIVER _Driver)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDRIVER_CONTEXT ptDriverContext = GetDriverContext(_Driver);
    WDFKEY tWDFKey = { 0 };
    UNICODE_STRING tUnicKeyName;

    //����������� Parameters ע������������ʾ�ü��Ŀ��ע��������ľ����
    lNTStatus = WdfDriverOpenParametersRegistryKey(_Driver, KEY_READ | KEY_WRITE, WDF_NO_OBJECT_ATTRIBUTES, &tWDFKey);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfDriverOpenParametersRegistryKey is err.\n"));
        return lNTStatus;
    }

    RtlInitUnicodeString(&tUnicKeyName, L"����");
    lNTStatus = WdfRegistryQueryULong(tWDFKey, &tUnicKeyName, &ptDriverContext->Num);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    RtlInitUnicodeString(&tUnicKeyName, L"����");
    lNTStatus = WdfRegistryQueryULong(tWDFKey, &tUnicKeyName, &ptDriverContext->Boole);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    UNICODE_STRING tUnicValue;
    USHORT ushValueLen = 0;

    tUnicValue.Buffer = ptDriverContext->StrContent;
    tUnicValue.Length = 0;
    tUnicValue.MaximumLength = sizeof ptDriverContext->StrContent;

    RtlInitUnicodeString(&tUnicKeyName, L"�ַ���");
    lNTStatus = WdfRegistryQueryUnicodeString(tWDFKey, &tUnicKeyName, &ushValueLen, &tUnicValue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("WdfRegistryQueryULong is err.\n"));
        return lNTStatus;
    }

    KdPrint(("����:%d\n", ptDriverContext->Num));
    KdPrint(("����:%d\n", ptDriverContext->Boole));
    KdPrint(("�ַ���:%wZ\n", &tUnicValue));

    return lNTStatus;
}

