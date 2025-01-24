/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.24
��  ��: ע���ص��뱣��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.24
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>

LARGE_INTEGER g_tCookie;
WCHAR g_wchKeyPath[1024] = { 0 };			//��ǰע����·��
WCHAR g_wchKeyName[260] = { 0 };			//��ǰ������������


//ע�������ص�����
NTSTATUS Register_CallBack(_In_ PVOID CallbackContext, _In_opt_ PVOID Argument1, _In_opt_ PVOID Argument2)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	switch ((REG_NOTIFY_CLASS)Argument1)
	{
	case RegNtPreOpenKey:
	case RegNtPreOpenKeyEx:
	case RegNtPreCreateKey:
	case RegNtPreCreateKeyEx:
	{
		PREG_CREATE_KEY_INFORMATION ptReg_KeyInfo = (PREG_CREATE_KEY_INFORMATION)Argument2;
		if (!ptReg_KeyInfo)
		{
			lStatus = STATUS_INVALID_PARAMETER;
			return lStatus;
		}

		RtlCopyMemory(g_wchKeyPath, ptReg_KeyInfo->CompleteName->Buffer, ptReg_KeyInfo->CompleteName->Length);
		if (wcsstr(_wcslwr(g_wchKeyPath), _wcslwr(g_wchKeyName)) != NULL)
		{
			lStatus = STATUS_STACK_OVERFLOW;
		}
	}
	default:
		break;
	}

	return lStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	CmUnRegisterCallback(g_tCookie);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	RtlCopyMemory(g_wchKeyName, DriverObject->DriverExtension->ServiceKeyName.Buffer, DriverObject->DriverExtension->ServiceKeyName.Length);

	CmRegisterCallback(Register_CallBack, NULL, &g_tCookie);

	KdPrint(("�������سɹ�\n"));

	return lStatus;
}

