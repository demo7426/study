/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.13
描  述: 使用快速互斥进行内核同步，使用原子性、自旋锁操作数
备  注: ExInitializeFastMutex--初始化快速互斥对象
		ExAcquireFastMutex--获取快速互斥，如果必要则等待
		ExAcquireFastMutexUnsafe--获取快速互斥，如果必要则等待，调用者必须先停止接收APC
		ExReleaseFastMutex--释放快速互斥
		ExReleaseFastMutex--释放快速互斥，不解除APC提交禁止
		ExTryToAcquireFastMutex--获取快速互斥，如果可能立即获取不等待

		InterlockedCompareExchange--数据比较;等价于:lValue == 10? lValue = 20: 0;
		InterlockedDecrement--减1
		InterlockedExchange--交换值
		InterlockedExchangeAdd--加
		InterlockedIncrement--加1

		//使用自选锁
		ExInterlockedAddLargeInteger--64位加法
		ExInterlockedAddLargeStatisticr--64位加法
		ExInterlockedAddUlong--32位加法
		ExInterlockedCompareExchange64--数据比较;支持的是LARGE_INTEGER类型数据;等价于:lValue == 10? lValue = 20: 0;
修改记录:

  1.  日期: 2024.12.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

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
/// 快速互斥的使用
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
/// 数据的原子性、互斥锁保护操作测试
/// </summary>
/// <param name=""></param>
VOID InterLocked_Test02(VOID)
{
	LONG lValue = 10;
	LARGE_INTEGER tLarge_Integer01 = RtlConvertUlongToLargeInteger(10);
	LARGE_INTEGER tLarge_Integer02 = RtlConvertUlongToLargeInteger(90);
	LARGE_INTEGER tLarge_Integer03 = RtlConvertUlongToLargeInteger(90);
	KSPIN_LOCK tKSpinLock;

	InterlockedCompareExchange(&lValue, 20, 10);			//数据比较;等价于:lValue == 10? lValue = 20: 0;
	KdPrint(("lValue: %d", lValue));

	InterlockedDecrement(&lValue);							//减1
	KdPrint(("lValue: %d", lValue));

	InterlockedExchange(&lValue, 100);						//交换值
	KdPrint(("lValue: %d", lValue));

	InterlockedExchangeAdd(&lValue, 2);						//加法
	KdPrint(("lValue: %d", lValue));

	InterlockedIncrement(&lValue);							//加1
	KdPrint(("lValue: %d", lValue));

	//使用自选锁
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	FastMutex_Test01();
	InterLocked_Test02();

	return STATUS_SUCCESS;
}



