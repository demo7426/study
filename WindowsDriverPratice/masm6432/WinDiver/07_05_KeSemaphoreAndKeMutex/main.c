/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.12
描  述: 内核使用信号量、互斥锁进行线程同步
备  注:	KeInitializeSemaphore--初始化信号量
		KeReadStateSemaphore--读取信号量当前可用数量
		PsTerminateSystemThread--释放信号量

		KeInitializeMutex--初始化互斥锁
		ObReferenceObjectByHandle--根据句柄引用其对象
		ObDereferenceObject--释放对象其引用
		KeReleaseMutex--释放互斥锁

		KeDelayExecutionThread--线程延时函数
修改记录:

  1.  日期: 2024.12.12
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

VOID Thread_Semaphore(_In_ PVOID StartContext)
{
	PRKSEMAPHORE ptKSemaphore = (PRKSEMAPHORE)StartContext;
	LARGE_INTEGER uTimerOut = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//负号代表相对时间;延时时间的单位为100ns

	KdPrint(("Thread_Semaphore enter\n"));

	KeDelayExecutionThread(KernelMode, FALSE, &uTimerOut);							//线程延时函数

	KdPrint(("Thread_Semaphore end\n"));

	KeReleaseSemaphore(ptKSemaphore, IO_NO_INCREMENT, 1, FALSE);

	PsTerminateSystemThread(0);		//必须告知内核线程从这里开始结束了
}

VOID Thread_Mutex(_In_ PVOID StartContext)
{
	PKMUTANT ptKMutex = (PKMUTANT)StartContext;
	LARGE_INTEGER uTimerOut = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//负号代表相对时间;延时时间的单位为100ns

	KeWaitForSingleObject(ptKMutex, Executive, KernelMode, FALSE, NULL);

	KdPrint(("Thread_Mutex enter\n"));

	KeDelayExecutionThread(KernelMode, FALSE, &uTimerOut);							//线程延时函数

	KdPrint(("Thread_Mutex end\n"));

	KeReleaseMutex(ptKMutex, FALSE);

	PsTerminateSystemThread(0);		//必须告知内核线程从这里开始结束了
}

/// <summary>
/// 内核模式信号量测试
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
/// 内核模式互斥锁测试
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	//KeSemaphore_Test01();
	KeMutex_Test02();

	return STATUS_SUCCESS;
}



