/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.23
描  述: Dll模块监控
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

VOID Load_Image_Notify_Routine(_In_opt_ PUNICODE_STRING FullImageName, _In_ HANDLE ProcessId,                // pid into which image is being mapped
	_In_ PIMAGE_INFO ImageInfo)
{
	if (ProcessId == 0)
	{
		KdPrint(("%wZ\n", FullImageName));
	}
	else
	{
		PEPROCESS ptPEProcess = NULL;

		PsLookupProcessByProcessId(ProcessId, &ptPEProcess);
		KdPrint(("%s, %wZ\n", PsGetProcessImageFileName(ptPEProcess), FullImageName));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsRemoveLoadImageNotifyRoutine(Load_Image_Notify_Routine);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	lNTStatus = PsSetLoadImageNotifyRoutine(Load_Image_Notify_Routine);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsSetLoadImageNotifyRoutine is err. 0x%x\n", lNTStatus));
		return lNTStatus;
	}

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


