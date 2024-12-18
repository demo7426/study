/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.18
��  ��: �ں�ģʽ�µĵȴ�����
��  ע:	
�޸ļ�¼:

  1.  ����: 2024.12.18
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// �¼��ȴ�����
/// </summary>
/// <param name="_WaitUs">�ȴ�ʱ��;��λΪus</param>
VOID WaitTest01(ULONG _WaitUs)
{
	KEVENT tKEvent;
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * _WaitUs);

	KeInitializeEvent(&tKEvent, SynchronizationEvent, FALSE);
	KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, &tTimeout);

	KdPrint(("WaitTest01 is end.\n"));
}

/// <summary>
/// Timer�ȴ�����
/// </summary>
/// <param name="_WaitUs">�ȴ�ʱ��;��λΪus</param>
VOID WaitTest02(ULONG _WaitUs)
{
	KTIMER tKTimer;
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * _WaitUs);

	KeInitializeTimer(&tKTimer);
	KeSetTimer(&tKTimer, tTimeout, NULL);
	
	KeWaitForSingleObject(&tKTimer, Executive, KernelMode, FALSE, &tTimeout);

	KdPrint(("WaitTest02 is end.\n"));
}

/// <summary>
/// �߳���ʱ�ȴ�����
/// </summary>
/// <param name="_WaitUs">�ȴ�ʱ��;��λΪus</param>
VOID WaitTest03(ULONG _WaitUs)
{
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * _WaitUs);
	
	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);

	KdPrint(("WaitTest03 is end.\n"));
}

/// <summary>
/// ��ʱ��ռ��cpu�ȴ�����
/// </summary>
/// <param name="_WaitUs">�ȴ�ʱ��;��λΪus</param>
VOID WaitTest04(ULONG _WaitUs)
{
	KeStallExecutionProcessor(_WaitUs);			//��ʱ��ռ��cpu

	KdPrint(("WaitTest04 is end.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	KdPrint(("�������سɹ�\n"));

	DriverObject->DriverUnload = DriverUnload;

	WaitTest01(2000 * 1000);
	WaitTest02(2000 * 1000);
	WaitTest03(2000 * 1000);
	WaitTest04(2000 * 1000);

	return lNTStatus;
}



