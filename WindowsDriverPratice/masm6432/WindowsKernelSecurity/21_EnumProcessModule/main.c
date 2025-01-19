/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.19
��  ��: ö�ٽ���ģ��
��  ע: TODO:
		win7 32λ����ϵͳ�£����ظ�.sys�ᵼ��ϵͳ����
			//��ȡ����ͷָ��
			ptList_Header = &ptPeb->Ldr->InMemoryOrderModuleList; 
		�����
�޸ļ�¼:

  1.  ����: 2025.01.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

#define MAX_PROCESSID 100000			//�������ID
#define MAX_THREADID 100000				//�߳����ID

//ö���߳�
static VOID EnumThread(PEPROCESS Process);

//ö�ٽ���ģ��
static VOID EnumProcessModule(PEPROCESS Process);

//ö�ٽ���
VOID EnumProcess(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	for (size_t i = 0; i < MAX_PROCESSID; i+=4)
	{
		lNTStatus = PsLookupProcessByProcessId((HANDLE)i, &tPEProcess);
		if (!NT_SUCCESS(lNTStatus))
			continue;

		KdPrint(("ProcessID:��ǰ����: %06d, ������:%06d, ����:%s\n", i, (INT32)PsGetProcessInheritedFromUniqueProcessId(tPEProcess), PsGetProcessImageFileName(tPEProcess)));
		//EnumThread(tPEProcess);
		EnumProcessModule(tPEProcess);
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

static VOID EnumProcessModule(PEPROCESS Process)
{
	PPEB ptPeb = NULL;
	KAPC_STATE tKAPC_State = { 0 };
	PLIST_ENTRY ptList_Header = { 0 };
	PLIST_ENTRY ptCurList_Entry = { 0 };
	PLDR_DATA_TABLE_ENTRY ptLdrDataTableEntry = NULL;

	ptPeb = PsGetProcessPeb(Process);
	if (!ptPeb || !ptPeb->Ldr)
		return;

	// ���ڽ��̸��룬��������Ҫ�ѵ�ǰ�̸߳��ŵ�Ŀ�������
	// ��Ŀ��Ľ��̵�ַ�ռ����
	KeStackAttachProcess(Process, &tKAPC_State);

	//��ȡ����ͷָ��
	ptList_Header = &ptPeb->Ldr->InMemoryOrderModuleList;

	//��ȡ��һ���ڵ�
	ptCurList_Entry = ptList_Header->Flink;

	while (ptCurList_Entry && ptCurList_Entry->Flink != ptList_Header)
	{
		// ��ȡ��Ӧ�ڵ��LDR_DATA_TABLE_ENTRY�ṹ�׵�ַ
		ptLdrDataTableEntry = CONTAINING_RECORD(ptCurList_Entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		// ��ӡ
		KdPrint(("\tģ���ַ: %p\tģ����: %wZ\r\n", ptLdrDataTableEntry->DllBase, &ptLdrDataTableEntry->FullDllName));

		// ��һ���ڵ�
		ptCurList_Entry = ptCurList_Entry->Flink;
	}

	KeUnstackDetachProcess(&tKAPC_State);
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




