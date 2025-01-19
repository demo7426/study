/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.19
描  述: 自动结束线程
备  注: 
修改记录:

  1.  日期: 2025.01.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>

static KEVENT g_tThreadCtlKEvent = { 0 };		//线程控制事件
static PETHREAD g_tPEThread = NULL;

VOID ThreadProc(PVOID _pContent)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	LARGE_INTEGER tWaitForSingleTimeout = RtlConvertLongToLargeInteger(-10 * 1000 * 1000);					//等待事件的延时时间

	g_tPEThread = PsGetCurrentThread();

	KdPrint(("ThreadProc is enter.\n"));

	while (TRUE)
	{
		KdPrint(("ThreadProc is running.\n"));

		lNTStatus = KeWaitForSingleObject(&g_tThreadCtlKEvent, Executive, KernelMode, FALSE, &tWaitForSingleTimeout);
		if (lNTStatus == STATUS_TIMEOUT)
			continue;
		else
			break;
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	KeSetEvent(&g_tThreadCtlKEvent, IO_NO_INCREMENT, FALSE);

	lNTStatus = KeWaitForSingleObject(g_tPEThread, Executive, KernelMode, FALSE, NULL);
	if (NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ThreadProc is end.\n"));
	}

	KdPrint(("驱动卸载成功"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;
	OBJECT_ATTRIBUTES tObjAttr = { 0 };

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功"));
	
	KeInitializeEvent(&g_tThreadCtlKEvent, SynchronizationEvent, FALSE);						//设置为无信号状态

	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_CASE_INSENSITIVE, NULL, NULL);
	PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, &tObjAttr, NULL, NULL, ThreadProc, NULL);

	return lNTStatus;
}
