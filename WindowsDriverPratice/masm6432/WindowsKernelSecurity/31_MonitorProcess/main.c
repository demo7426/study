/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.22
��  ��: ���̼��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID Process_Notify_Rountine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId, _In_ BOOLEAN Create)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS ptCurProcess = NULL;

	lNTStatus = PsLookupProcessByProcessId(ProcessId, &ptCurProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsLookupProcessByProcessId is err.\n"));
		return;
	}

	if (Create)
	{
		KdPrint(("�򿪳���,��ǰ����ID: %d, ����: %s\n", (INT32)ParentId, PsGetProcessImageFileName(ptCurProcess)));
	}
	else
	{
		KdPrint(("�رճ���,��ǰ����ID: %d, ����: %s\n", (INT32)ParentId, PsGetProcessImageFileName(ptCurProcess)));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsSetCreateProcessNotifyRoutine(Process_Notify_Rountine, TRUE);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	PsSetCreateProcessNotifyRoutine(Process_Notify_Rountine, FALSE);

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


