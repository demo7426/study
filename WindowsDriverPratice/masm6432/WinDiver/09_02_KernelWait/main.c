/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.18
描  述: 内核模式下的等待操作
备  注:	
修改记录:

  1.  日期: 2024.12.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 事件等待测试
/// </summary>
/// <param name="_WaitUs">等待时间;单位为us</param>
VOID WaitTest01(ULONG _WaitUs)
{
	KEVENT tKEvent;
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * _WaitUs);

	KeInitializeEvent(&tKEvent, SynchronizationEvent, FALSE);
	KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, &tTimeout);

	KdPrint(("WaitTest01 is end.\n"));
}

/// <summary>
/// Timer等待测试
/// </summary>
/// <param name="_WaitUs">等待时间;单位为us</param>
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
/// 线程延时等待测试
/// </summary>
/// <param name="_WaitUs">等待时间;单位为us</param>
VOID WaitTest03(ULONG _WaitUs)
{
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * _WaitUs);
	
	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);

	KdPrint(("WaitTest03 is end.\n"));
}

/// <summary>
/// 延时且占用cpu等待测试
/// </summary>
/// <param name="_WaitUs">等待时间;单位为us</param>
VOID WaitTest04(ULONG _WaitUs)
{
	KeStallExecutionProcessor(_WaitUs);			//延时且占用cpu

	KdPrint(("WaitTest04 is end.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	KdPrint(("驱动加载成功\n"));

	DriverObject->DriverUnload = DriverUnload;

	WaitTest01(2000 * 1000);
	WaitTest02(2000 * 1000);
	WaitTest03(2000 * 1000);
	WaitTest04(2000 * 1000);

	return lNTStatus;
}



