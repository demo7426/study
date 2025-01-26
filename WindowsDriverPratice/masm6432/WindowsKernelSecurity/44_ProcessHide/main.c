/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.26
描  述: win7 32位操作系统的进程隐藏
备  注: 需要使用windbg x nt!MiProcessLoaderEntry 获取MiProcessLoaderEntry的虚拟地址
修改记录:

  1.  日期: 2025.01.26
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

UINT32 GetProcessOffset(VOID)
{
	if (SharedUserData->NtMajorVersion == 5) //win xp操作系统
	{
		return 0x88;
	}
	else if (SharedUserData->NtMajorVersion == 6 && SharedUserData->NtMinorVersion == 1)
	{
		if (sizeof(PVOID) == 4)			//win7 32位操作系统
		{
			return 0xB8;
		}
		else							//win7 64位操作系统
		{
			return 0x188;
		}
	}
	
	return 0;
}

//进程隐藏
VOID ProcessHide(HANDLE ProcessId)
{
	PEPROCESS ptPeProcess = NULL;
	PFNMIPROCESSLOADERENTRY MinProcessLoaderEntry = NULL;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	lNTStatus = PsLookupProcessByProcessId(ProcessId, &ptPeProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsLookupProcessByProcessId is err\n"));
		return;
	}

#ifdef _X86_
	MinProcessLoaderEntry = (PFNMIPROCESSLOADERENTRY)0x83eb8b37;
#endif // _x86

	if (!MinProcessLoaderEntry)
	{
		KdPrint(("MinProcessLoaderEntry is empty\n"));
		return;
	}

	MinProcessLoaderEntry((PCHAR)ptPeProcess + GetProcessOffset(), FALSE);
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

	ProcessHide((HANDLE)2164);

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}



