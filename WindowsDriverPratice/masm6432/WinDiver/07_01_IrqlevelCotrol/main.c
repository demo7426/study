/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.05
描  述: 优先级获取及设置，自旋锁也会改变当前进程优先级
备  注:	1、	中断请求优先级包含有32个等级:
				HIGH_LEVEL--一般为电源模块使用的优先级
				......
				DISPATCH_LEVEL--用户高优先级
				APC_LEVEL--用户中优先级
				PASSIVE_LEVEL--用户最低优先级（用户层的程序一般都处于该层级）
			KeGetCurrentIrql--获取当前进程的优先级
			KeRaiseIrql--提升当前进程的优先级到指定的优先级
			KeLowerIrql--降低当前进程的优先级

		2、	KeInitializeSpinLock--初始化自旋锁
			KeAcquireSpinLock--获取自旋锁
			KeAcquireSpinLock--释放自旋锁
修改记录:

  1.  日期: 2024.12.05
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 打印当前进程的优先级
/// </summary>
/// <param name=""></param>
VOID PrintCurIrlLevel(VOID)
{
	switch (KeGetCurrentIrql())
	{
	case DISPATCH_LEVEL:
		KdPrint(("DISPATCH_LEVEL\n"));
		break;
	case APC_LEVEL:
		KdPrint(("APC_LEVEL\n"));
		break;
	case PASSIVE_LEVEL:
		KdPrint(("PASSIVE_LEVEL\n"));
		break;
	default:
		break;
	}
}

/// <summary>
/// 自旋锁测试
/// </summary>
/// <param name=""></param>
VOID SpinLockTest01(VOID)
{
	KIRQL uchIrql;
	KSPIN_LOCK ulSpinLock;

	KdPrint(("自旋锁测试:\n"));

	KeInitializeSpinLock(&ulSpinLock);
	PrintCurIrlLevel();

	KeAcquireSpinLock(&ulSpinLock, &uchIrql);			//获取到自旋锁后，会提升之后的优先级直到释放自旋锁，可以防止函数在同一时刻被多次重入
	PrintCurIrlLevel();

	KeReleaseSpinLock(&ulSpinLock, uchIrql);
	PrintCurIrlLevel();
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	KIRQL uchIrql;

	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("驱动加载成功\n"));

	PrintCurIrlLevel();

	KeRaiseIrql(DISPATCH_LEVEL, &uchIrql);
	PrintCurIrlLevel();

	KeLowerIrql(uchIrql);
	PrintCurIrlLevel();

	SpinLockTest01();

	return STATUS_SUCCESS;
}