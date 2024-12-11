/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.12
��  ��: �ں�ʹ���ź����������������߳�ͬ��
��  ע:	KeInitializeSemaphore--��ʼ���ź���
		KeReadStateSemaphore--��ȡ�ź�����ǰ��������
		PsTerminateSystemThread--�ͷ��ź���

		KeInitializeMutex--��ʼ��������
		ObReferenceObjectByHandle--���ݾ�����������
		ObDereferenceObject--�ͷŶ���������
		KeReleaseMutex--�ͷŻ�����

		KeDelayExecutionThread--�߳���ʱ����
�޸ļ�¼:

  1.  ����: 2024.12.12
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

VOID Thread_Semaphore(_In_ PVOID StartContext)
{
	PRKSEMAPHORE ptKSemaphore = (PRKSEMAPHORE)StartContext;
	LARGE_INTEGER uTimerOut = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//���Ŵ������ʱ��;��ʱʱ��ĵ�λΪ100ns

	KdPrint(("Thread_Semaphore enter\n"));

	KeDelayExecutionThread(KernelMode, FALSE, &uTimerOut);							//�߳���ʱ����

	KdPrint(("Thread_Semaphore end\n"));

	KeReleaseSemaphore(ptKSemaphore, IO_NO_INCREMENT, 1, FALSE);

	PsTerminateSystemThread(0);		//�����֪�ں��̴߳����￪ʼ������
}

VOID Thread_Mutex(_In_ PVOID StartContext)
{
	PKMUTANT ptKMutex = (PKMUTANT)StartContext;
	LARGE_INTEGER uTimerOut = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//���Ŵ������ʱ��;��ʱʱ��ĵ�λΪ100ns

	KeWaitForSingleObject(ptKMutex, Executive, KernelMode, FALSE, NULL);

	KdPrint(("Thread_Mutex enter\n"));

	KeDelayExecutionThread(KernelMode, FALSE, &uTimerOut);							//�߳���ʱ����

	KdPrint(("Thread_Mutex end\n"));

	KeReleaseMutex(ptKMutex, FALSE);

	PsTerminateSystemThread(0);		//�����֪�ں��̴߳����￪ʼ������
}

/// <summary>
/// �ں�ģʽ�ź�������
/// </summary>
/// <param name=""></param>
VOID KeSemaphore_Test01(VOID)
{
	KSEMAPHORE tKSemaphore;
	LONG lSemaphoreCount = 0;
	HANDLE handThread;

	KeInitializeSemaphore(&tKSemaphore, 2, 2);

	lSemaphoreCount = KeReadStateSemaphore(&tKSemaphore);
	KdPrint(("Semaphore count is %d\n", lSemaphoreCount));

	KeWaitForSingleObject(&tKSemaphore, Executive, KernelMode, FALSE, NULL);
	lSemaphoreCount = KeReadStateSemaphore(&tKSemaphore);
	KdPrint(("Semaphore count is %d\n", lSemaphoreCount));

	KeWaitForSingleObject(&tKSemaphore, Executive, KernelMode, FALSE, NULL);
	lSemaphoreCount = KeReadStateSemaphore(&tKSemaphore);
	KdPrint(("Semaphore count is %d\n", lSemaphoreCount));

	PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, Thread_Semaphore, &tKSemaphore);

	KeWaitForSingleObject(&tKSemaphore, Executive, KernelMode, FALSE, NULL);
	KdPrint(("KeSemaphore_Test01 is end\n"));
}

/// <summary>
/// �ں�ģʽ����������
/// </summary>
/// <param name=""></param>
VOID KeMutex_Test02(VOID)
{
	KMUTANT tKMutex;
	LONG lSemaphoreCount = 0;
	HANDLE handThread[2] = { NULL };
	PETHREAD ptThread[2] = { NULL };

	KeInitializeMutex(&tKMutex, 0);

	PsCreateSystemThread(&(handThread[0]), THREAD_ALL_ACCESS, NULL, NULL, NULL, Thread_Mutex, &tKMutex);
	PsCreateSystemThread(&(handThread[1]), THREAD_ALL_ACCESS, NULL, NULL, NULL, Thread_Mutex, &tKMutex);

	ObReferenceObjectByHandle(handThread[0], THREAD_ALL_ACCESS, *PsThreadType, KernelMode, &(ptThread[0]), NULL);
	ObReferenceObjectByHandle(handThread[1], THREAD_ALL_ACCESS, *PsThreadType, KernelMode, &(ptThread[1]), NULL);

	KeWaitForMultipleObjects(2, ptThread, WaitAll, Executive, KernelMode, FALSE, NULL, NULL);

	ObDereferenceObject(ptThread[0]);
	ObDereferenceObject(ptThread[1]);

	KdPrint(("KeMutex_Test02 is end\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	//KeSemaphore_Test01();
	KeMutex_Test02();

	return STATUS_SUCCESS;
}



