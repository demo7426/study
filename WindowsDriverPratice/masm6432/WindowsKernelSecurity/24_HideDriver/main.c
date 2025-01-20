/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.20
��  ��: ����������ʹ������arp�����޷�ʶ�𵽸�����
��  ע: ��Ҫʹ��windbg ʹ��x nt!MiProcessLoaderEntry ץȡ����ַ�󣬲ſ�������ʹ�ø�����
		�����������޷�����ж�ظ�����
�޸ļ�¼:

  1.  ����: 2025.01.20
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

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

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);		//��֤�����Ѿ����سɹ����ٽ�����ں�����������ɾ��

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
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;

	DriverObject->DriverUnload = DriverUnload;

	PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, DriverObject);

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}



