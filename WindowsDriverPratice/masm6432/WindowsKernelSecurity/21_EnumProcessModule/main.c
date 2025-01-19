/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.19
描  述: 枚举进程模块
备  注: TODO:
		win7 32位操作系统下，加载该.sys会导致系统崩溃
			//获取链表头指针
			ptList_Header = &ptPeb->Ldr->InMemoryOrderModuleList; 
		待解决
修改记录:

  1.  日期: 2025.01.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

#define MAX_PROCESSID 100000			//进程最大ID
#define MAX_THREADID 100000				//线程最大ID

//枚举线程
static VOID EnumThread(PEPROCESS Process);

//枚举进程模块
static VOID EnumProcessModule(PEPROCESS Process);

//枚举进程
VOID EnumProcess(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	for (size_t i = 0; i < MAX_PROCESSID; i+=4)
	{
		lNTStatus = PsLookupProcessByProcessId((HANDLE)i, &tPEProcess);
		if (!NT_SUCCESS(lNTStatus))
			continue;

		KdPrint(("ProcessID:当前进程: %06d, 父进程:%06d, 名称:%s\n", i, (INT32)PsGetProcessInheritedFromUniqueProcessId(tPEProcess), PsGetProcessImageFileName(tPEProcess)));
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

//终止进程
VOID TerminateProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hProcess;
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	CLIENT_ID tClient_ID = { 0 };

	tClient_ID.UniqueProcess = ProcesssID;
	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);
	
	lNTStatus = ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &tObjAttr, &tClient_ID);		//打开进程对象的句柄，并设置对此对象的访问权限
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
			KdPrint(("\t进程名称:%s, 进程ID:%06d, 线程ID:%06d\n", PsGetProcessImageFileName(Process), (INT32)PsGetProcessId(Process),  i));
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

	// 由于进程隔离，所以我们要把当前线程附着到目标进程上
	// 在目标的进程地址空间操作
	KeStackAttachProcess(Process, &tKAPC_State);

	//获取链表头指针
	ptList_Header = &ptPeb->Ldr->InMemoryOrderModuleList;

	//获取第一个节点
	ptCurList_Entry = ptList_Header->Flink;

	while (ptCurList_Entry && ptCurList_Entry->Flink != ptList_Header)
	{
		// 获取对应节点的LDR_DATA_TABLE_ENTRY结构首地址
		ptLdrDataTableEntry = CONTAINING_RECORD(ptCurList_Entry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		// 打印
		KdPrint(("\t模块基址: %p\t模块名: %wZ\r\n", ptLdrDataTableEntry->DllBase, &ptLdrDataTableEntry->FullDllName));

		// 下一个节点
		ptCurList_Entry = ptCurList_Entry->Flink;
	}

	KeUnstackDetachProcess(&tKAPC_State);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动成功卸载"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动成功加载"));

	EnumProcess();

	return lNTStatus;
}




