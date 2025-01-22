/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.22
描  述: 进程监控
备  注: 
修改记录:

  1.  日期: 2025.01.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

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
		KdPrint(("打开程序,当前进程ID: %d, 名称: %s\n", (INT32)ParentId, PsGetProcessImageFileName(ptCurProcess)));
	}
	else
	{
		KdPrint(("关闭程序,当前进程ID: %d, 名称: %s\n", (INT32)ParentId, PsGetProcessImageFileName(ptCurProcess)));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsSetCreateProcessNotifyRoutine(Process_Notify_Rountine, TRUE);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	PsSetCreateProcessNotifyRoutine(Process_Notify_Rountine, FALSE);

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


