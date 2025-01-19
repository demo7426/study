/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.19
��  ��: �Զ������߳�
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>

static KEVENT g_tThreadCtlKEvent = { 0 };		//�߳̿����¼�
static PETHREAD g_tPEThread = NULL;

VOID ThreadProc(PVOID _pContent)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	LARGE_INTEGER tWaitForSingleTimeout = RtlConvertLongToLargeInteger(-10 * 1000 * 1000);					//�ȴ��¼�����ʱʱ��

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

	KdPrint(("����ж�سɹ�"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;
	OBJECT_ATTRIBUTES tObjAttr = { 0 };

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�"));
	
	KeInitializeEvent(&g_tThreadCtlKEvent, SynchronizationEvent, FALSE);						//����Ϊ���ź�״̬

	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_CASE_INSENSITIVE, NULL, NULL);
	PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, &tObjAttr, NULL, NULL, ThreadProc, NULL);

	return lNTStatus;
}
