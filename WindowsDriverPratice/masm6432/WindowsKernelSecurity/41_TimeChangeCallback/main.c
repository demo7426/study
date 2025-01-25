/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.25
��  ��: ʱ�����ص�
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.25
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdm.h>

VOID TimeChangeCallBack_Func(
	_In_opt_ PVOID CallbackContext,
	_In_opt_ PVOID Argument1,
	_In_opt_ PVOID Argument2
)
{
	KdPrint(("ʱ�䱻�޸�.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;
	UNICODE_STRING tTimeChangeCbName = RTL_CONSTANT_STRING(L"\\Callback\\SetSystemTime");
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	PCALLBACK_OBJECT ptCbObj = NULL;

	DriverObject->DriverUnload = DriverUnload;

	InitializeObjectAttributes(&tObjAttr, &tTimeChangeCbName, OBJ_CASE_INSENSITIVE, NULL, NULL);
	lStatus = ExCreateCallback(&ptCbObj, &tObjAttr, TRUE, FALSE);
	if (!NT_SUCCESS(lStatus))
	{
		KdPrint(("ExCreateCallback is err.\n"));
		return lStatus;
	}

	ExRegisterCallback(ptCbObj, TimeChangeCallBack_Func, NULL);

	ObDereferenceObject(ptCbObj);
	ptCbObj = NULL;

	KdPrint(("�������سɹ�\n"));

	return lStatus;
}

