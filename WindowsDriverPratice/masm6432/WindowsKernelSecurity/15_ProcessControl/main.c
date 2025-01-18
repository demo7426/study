/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.18
��  ��: ö�١���ͣ���ָ�����������
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.18
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#define MAX_PROCESSID 100000			//�������ID

//���ݽ�����Ϣ,��ȡ��������
PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);

//�������
NTSTATUS PsSuspendProcess(IN PEPROCESS Process);

//�ָ�����
NTSTATUS PsResumeProcess(IN PEPROCESS Process);

//��ȡ������
HANDLE PsGetProcessInheritedFromUniqueProcessId(IN PEPROCESS Process);

//��ֹ����
//NTSTATUS ZwTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus);

//ö�ٽ���
VOID EnumProcess(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	for (size_t i = 1; i < MAX_PROCESSID; i++)
	{
		lNTStatus = PsLookupProcessByProcessId((HANDLE)i, &tPEProcess);
		if (!NT_SUCCESS(lNTStatus))
			continue;

		KdPrint(("ProcessID:��ǰ����: %06d, ������:%06d, ����:%s\n", i, (INT32)PsGetProcessInheritedFromUniqueProcessId(tPEProcess), PsGetProcessImageFileName(tPEProcess)));
	}
}

VOID SuspendProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	lNTStatus = PsLookupProcessByProcessId((HANDLE)ProcesssID, &tPEProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	PsSuspendProcess(tPEProcess);
}

VOID ResumeProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS tPEProcess = { 0 };

	lNTStatus = PsLookupProcessByProcessId((HANDLE)ProcesssID, &tPEProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	PsResumeProcess(tPEProcess);
}

//��ֹ����
VOID TerminateProcess(HANDLE ProcesssID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hProcess;
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	CLIENT_ID tClient_ID = { 0 };

	tClient_ID.UniqueProcess = ProcesssID;
	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwOpenProcess(&hProcess, PROCESS_ALL_ACCESS, &tObjAttr, &tClient_ID);		//�򿪽��̶���ľ���������öԴ˶���ķ���Ȩ��
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}

	lNTStatus = ZwTerminateProcess(hProcess, STATUS_SUCCESS);
	if (!NT_SUCCESS(lNTStatus))
	{
		return;
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 5000 * 1000);

	ResumeProcess((HANDLE)3664);		//�ָ��������Ľ���

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);

	TerminateProcess((HANDLE)3664);		//��ֹ�������Ľ���
	
	KdPrint(("�����ɹ�ж��"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�����ɹ�����"));

	EnumProcess();

	SuspendProcess((HANDLE)3664);		//����������Ľ���

	return lNTStatus;
}




