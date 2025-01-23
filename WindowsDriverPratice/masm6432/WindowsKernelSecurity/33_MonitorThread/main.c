/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.23
描  述: 线程监控
备  注: 
修改记录:

  1.  日期: 2025.01.23
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

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
		KdPrint(("创建:当前进程ID: %d, 线程ID: %d, 进程名称: %wZ\n", (INT32)ProcessId, (INT32)ThreadId, PsGetProcessImageFileName(ptPEProcess)));
	}
	else
	{
		KdPrint(("销毁:当前进程ID: %d, 线程ID: %d, 进程名称: %wZ\n", (INT32)ProcessId, (INT32)ThreadId, PsGetProcessImageFileName(ptPEProcess)));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsRemoveCreateThreadNotifyRoutine(Create_Thread_Notify_Routine);

	KdPrint(("驱动卸载成功\n"));
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

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


