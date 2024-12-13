/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.13
��  ��: ʹ�ÿ��ٻ�������ں�ͬ����ʹ��ԭ���ԡ�������������
��  ע: ExInitializeFastMutex--��ʼ�����ٻ������
		ExAcquireFastMutex--��ȡ���ٻ��⣬�����Ҫ��ȴ�
		ExAcquireFastMutexUnsafe--��ȡ���ٻ��⣬�����Ҫ��ȴ��������߱�����ֹͣ����APC
		ExReleaseFastMutex--�ͷſ��ٻ���
		ExReleaseFastMutex--�ͷſ��ٻ��⣬�����APC�ύ��ֹ
		ExTryToAcquireFastMutex--��ȡ���ٻ��⣬�������������ȡ���ȴ�

		InterlockedCompareExchange--���ݱȽ�;�ȼ���:lValue == 10? lValue = 20: 0;
		InterlockedDecrement--��1
		InterlockedExchange--����ֵ
		InterlockedExchangeAdd--��
		InterlockedIncrement--��1

		//ʹ����ѡ��
		ExInterlockedAddLargeInteger--64λ�ӷ�
		ExInterlockedAddLargeStatisticr--64λ�ӷ�
		ExInterlockedAddUlong--32λ�ӷ�
		ExInterlockedCompareExchange64--���ݱȽ�;֧�ֵ���LARGE_INTEGER��������;�ȼ���:lValue == 10? lValue = 20: 0;
�޸ļ�¼:

  1.  ����: 2024.12.13
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

VOID ThreadProc(_In_ PVOID StartContext)
{
	PFAST_MUTEX ptFastMutex = (PFAST_MUTEX)StartContext;
	LARGE_INTEGER tLarge_Integer = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);

	ExAcquireFastMutex(ptFastMutex);

	KdPrint(("ThreadProc enter.\n"));

	KeDelayExecutionThread(KernelMode, FALSE, &tLarge_Integer);

	KdPrint(("ThreadProc quit.\n"));

	ExReleaseFastMutex(ptFastMutex);

	PsTerminateSystemThread(0);
}

/// <summary>
/// ���ٻ����ʹ��
/// </summary>
/// <param name=""></param>
VOID FastMutex_Test01(VOID)
{
	FAST_MUTEX tFastMutex;
	HANDLE hThread[2] = { NULL };
	PETHREAD ptThread[2] = { NULL };

	ExInitializeFastMutex(&tFastMutex);

	PsCreateSystemThread(hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, &tFastMutex);
	PsCreateSystemThread(hThread + 1, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, &tFastMutex);

	ObReferenceObjectByHandle(hThread[0], THREAD_ALL_ACCESS, *PsThreadType, KernelMode, &(ptThread[0]), NULL);
	ObReferenceObjectByHandle(hThread[1], THREAD_ALL_ACCESS, *PsThreadType, KernelMode, &(ptThread[1]), NULL);

	KeWaitForMultipleObjects(2, ptThread, WaitAll, Executive, KernelMode, FALSE, NULL, NULL);

	ObDereferenceObject(ptThread[0]);
	ObDereferenceObject(ptThread[1]);
}

/// <summary>
/// ���ݵ�ԭ���ԡ�������������������
/// </summary>
/// <param name=""></param>
VOID InterLocked_Test02(VOID)
{
	LONG lValue = 10;
	LARGE_INTEGER tLarge_Integer01 = RtlConvertUlongToLargeInteger(10);
	LARGE_INTEGER tLarge_Integer02 = RtlConvertUlongToLargeInteger(90);
	LARGE_INTEGER tLarge_Integer03 = RtlConvertUlongToLargeInteger(90);
	KSPIN_LOCK tKSpinLock;

	InterlockedCompareExchange(&lValue, 20, 10);			//���ݱȽ�;�ȼ���:lValue == 10? lValue = 20: 0;
	KdPrint(("lValue: %d", lValue));

	InterlockedDecrement(&lValue);							//��1
	KdPrint(("lValue: %d", lValue));

	InterlockedExchange(&lValue, 100);						//����ֵ
	KdPrint(("lValue: %d", lValue));

	InterlockedExchangeAdd(&lValue, 2);						//�ӷ�
	KdPrint(("lValue: %d", lValue));

	InterlockedIncrement(&lValue);							//��1
	KdPrint(("lValue: %d", lValue));

	//ʹ����ѡ��
	KeInitializeSpinLock(&tKSpinLock);

	ExInterlockedAddLargeInteger(&tLarge_Integer01, tLarge_Integer02, &tKSpinLock);
	KdPrint(("tLarge_Integer01.LowPart: %u", tLarge_Integer01.LowPart));

	ExInterlockedAddLargeStatistic(&tLarge_Integer01, 10);
	KdPrint(("tLarge_Integer01.LowPart: %u", tLarge_Integer01.LowPart));

	ExInterlockedAddUlong(&(tLarge_Integer01.LowPart), 20, &tKSpinLock);
	KdPrint(("tLarge_Integer01.LowPart: %u", tLarge_Integer01.LowPart));

	tLarge_Integer01 = RtlConvertUlongToLargeInteger(10);
	tLarge_Integer02 = RtlConvertUlongToLargeInteger(10);

	ExInterlockedCompareExchange64(&tLarge_Integer01, &tLarge_Integer03, &tLarge_Integer02, &tKSpinLock);
	KdPrint(("tLarge_Integer01.LowPart: %u", tLarge_Integer01.LowPart));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	FastMutex_Test01();
	InterLocked_Test02();

	return STATUS_SUCCESS;
}



