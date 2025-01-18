/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.18
描  述: 枚举、暂停、恢复、结束进程
备  注:
修改记录:

  1.  日期: 2025.01.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#define MAX_PROCESSID 100000			//进程最大ID

//根据进程信息,获取进程名称
PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);

//挂起进程
NTSTATUS PsSuspendProcess(IN PEPROCESS Process);

//恢复进程
NTSTATUS PsResumeProcess(IN PEPROCESS Process);

//获取父进程
HANDLE PsGetProcessInheritedFromUniqueProcessId(IN PEPROCESS Process);

//终止进程
//NTSTATUS ZwTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus);

//枚举进程
VOID EnumProcess(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	for (size_t i = 1; i < MAX_PROCESSID; i++)
	{
		lNTStatus = PsLookupProcessByProcessId((HANDLE)i, &tPEProcess);
		if (!NT_SUCCESS(lNTStatus))
			continue;

		KdPrint(("ProcessID:当前进程: %06d, 父进程:%06d, 名称:%s\n", i, (INT32)PsGetProcessInheritedFromUniqueProcessId(tPEProcess), PsGetProcessImageFileName(tPEProcess)));
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

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 5000 * 1000);

	ResumeProcess((HANDLE)3664);		//恢复计算器的进程

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);

	TerminateProcess((HANDLE)3664);		//终止计算器的进程
	
	KdPrint(("驱动成功卸载"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动成功加载"));

	EnumProcess();

	SuspendProcess((HANDLE)3664);		//挂起计算器的进程

	return lNTStatus;
}




