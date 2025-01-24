/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.24
��  ��: ʵ�ֽ��̱���
��  ע: ������ֻ����win7 64λ����������
�޸ļ�¼:

  1.  ����: 2025.01.24
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdm.h>

#include "ExportAPI.h"

#define PROCESS_TERMINATE 0x0001

HANDLE g_hOb = NULL;

//ͨ������ǩ�����
NTSTATUS BypassDriverCheck(PDRIVER_OBJECT DriverObject)
{
	if (DriverObject == NULL)
	{
		return STATUS_INVALID_PARAMETER;
	}

	PLDR_DATA_TABLE_ENTRY ptLdrData = (PLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection;
	
	ptLdrData->Flags |= 0x20;		//�ں˻����Ƿ��������ǩ�����������Flags�Ƿ�Ϊ0x20��
	
	return STATUS_SUCCESS;
}

//���̲����ص�����
OB_PREOP_CALLBACK_STATUS Ob_Pre_Operation_CallBack(_In_ PVOID RegistrationContext,	_Inout_ POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	PEPROCESS ptPEProcess = NULL;

	if (OperationInformation->ObjectType != *PsProcessType)
	{
		return OB_PREOP_SUCCESS;
	}

	ptPEProcess = OperationInformation->Object;
	if (_stricmp(PsGetProcessImageFileName(ptPEProcess), "calc.exe") != 0)
		return OB_PREOP_SUCCESS;

	if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE || OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
	{
		if (OperationInformation->Parameters->CreateHandleInformation.DesiredAccess & PROCESS_TERMINATE)
			OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
	}

	return OB_PREOP_SUCCESS;
}

//�Ƿ�ʹ�ܽ��̱���
NTSTATUS EnableProtectProcess(BOOLEAN _IsEnable)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	if (_IsEnable)
	{
		OB_CALLBACK_REGISTRATION tOb_Cb = { 0 };
		OB_OPERATION_REGISTRATION tOb_Op = { 0 };

		tOb_Cb.Version = OB_FLT_REGISTRATION_VERSION;
		tOb_Cb.RegistrationContext = NULL;
		tOb_Cb.OperationRegistrationCount = 1;
		tOb_Cb.OperationRegistration = &tOb_Op;
		RtlInitUnicodeString(&tOb_Cb.Altitude, L"123456");

		tOb_Op.ObjectType = PsProcessType;
		tOb_Op.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
		tOb_Op.PreOperation = Ob_Pre_Operation_CallBack;
	
		lStatus = ObRegisterCallbacks(&tOb_Cb, &g_hOb);
		if (!NT_SUCCESS(lStatus))
		{
			KdPrint(("ע��ʧ��\n"));
			return lStatus;
		}
	}
	else
	{
		if (g_hOb)
		{
			ObUnRegisterCallbacks(g_hOb);
			g_hOb = NULL;
		}
	}

	return lStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	EnableProtectProcess(FALSE);
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	BypassDriverCheck(DriverObject);
	EnableProtectProcess(TRUE);

	KdPrint(("�������سɹ�\n"));

	return lStatus;
}

