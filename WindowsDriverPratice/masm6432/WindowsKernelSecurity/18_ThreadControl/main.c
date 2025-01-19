/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.2     �½�����: 2025.01.18
��  ��: ö���߳�
��  ע: ���Ҫ��ֹ�̣߳���Ҫ�ȴ��̣߳�Ȼ��ͨ��windbgӲ�����ȡ�� PFNZWTERMINATETHREAD �����ĵ�ַ���ر��߳�
�޸ļ�¼:

  1.  ����: 2025.01.18
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

  2.  ����: 2025.01.19
	  ����: Ǯ��
	  ����:
		  1) ��չ����ֹ�̵߳�˵����
	  �汾:V0.0.2

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

#define MAX_PROCESSID 100000			//�������ID
#define MAX_THREADID 100000				//�߳����ID

//ö���߳�
static VOID EnumThread(PEPROCESS Process);

//ö�ٽ���
VOID EnumProcess(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	for (size_t i = 1; i < MAX_PROCESSID; i++)
	{
		lNTStatus = PsLookupProcessByProcessId((HANDLE)i, &tPEProcess);
		if (!NT_SUCCESS(lNTStatus))
			continue;

		KdPrint(("ProcessID:��ǰ����: %06d, ������:%06d, ����:%s\n", i, (INT32)PsGetProcessInheritedFromUniqueProcessId(tPEProcess), PsGetProcessImageFileName(tPEProcess)));
		EnumThread(tPEProcess);
	}
}

VOID SuspendProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	lNTStatus = PsLookupProcessByProcessId((HANDLE)ProcesssID, &tPEProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	PsSuspendProcess(tPEProcess);
}

VOID ResumeProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	lNTStatus = PsLookupProcessByProcessId((HANDLE)ProcesssID, &tPEProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	PsResumeProcess(tPEProcess);
}

//��ֹ����
VOID TerminateProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hProcess;
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	CLIENT_ID tClient_ID = { 0 };

	tClient_ID.UniqueProcess = ProcesssID;
	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	
	lNTStatus = ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &tObjAttr, &tClient_ID);		//�򿪽��̶���ľ���������öԴ˶���ķ���Ȩ��
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	lNTStatus = ZwTerminateProcess(hProcess, STATUS_SUCCESS);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}
}

static VOID EnumThread(PEPROCESS Process)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread;
	PETHREAD tPEThread = { 0 };

	for (size_t i = 1; i < MAX_THREADID; i++)
	{
		lNTStatus = PsLookupThreadByThreadId((HANDLE)i, &tPEThread);
		if (!NT_SUCCESS(lNTStatus))
		{
			continue;
		}

		if (IoThreadToProcess(tPEThread) == Process)
		{
			KdPrint(("\t��������:%s, ����ID:%06d, �߳�ID:%06d\n", PsGetProcessImageFileName(Process), (INT32)PsGetProcessId(Process),  i));
		}
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("�����ɹ�ж��"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�����ɹ�����"));

	EnumProcess();

	return lNTStatus;
}




