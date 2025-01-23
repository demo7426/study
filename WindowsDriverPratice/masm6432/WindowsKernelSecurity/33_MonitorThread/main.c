/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.23
��  ��: �̼߳��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.23
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID Create_Thread_Notify_Routine(_In_ HANDLE ProcessId, _In_ HANDLE ThreadId, _In_ BOOLEAN Create)
{
	PEPROCESS ptPEProcess = NULL;

	PsLookupProcessByProcessId(ProcessId, &ptPEProcess);

	if (Create)
	{
		KdPrint(("����:��ǰ����ID: %d, �߳�ID: %d, ��������: %wZ\n", (INT32)ProcessId, (INT32)ThreadId, PsGetProcessImageFileName(ptPEProcess)));
	}
	else
	{
		KdPrint(("����:��ǰ����ID: %d, �߳�ID: %d, ��������: %wZ\n", (INT32)ProcessId, (INT32)ThreadId, PsGetProcessImageFileName(ptPEProcess)));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsRemoveCreateThreadNotifyRoutine(Create_Thread_Notify_Routine);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	lNTStatus = PsSetCreateThreadNotifyRoutine(Create_Thread_Notify_Routine);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsSetCreateThreadNotifyRoutine is err. 0x%x\n", lNTStatus));
		return lNTStatus;
	}

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


