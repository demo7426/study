/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.16
描  述: 结构化异常处理
备  注: 1、捕获异常:
			__try{
			}
			__except (EXCEPTION_EXECUTE_HANDLER){
			}
		2、支持执行指定最终作用域
			__try{
			}
			__finally{
			}
		3、检测、抛出异常
			ProbeForRead(pchBuf, 1, 4);						//检测对应内存区域是否可读，不可读则抛出异常
			ProbeForWrite(pchBuf, 1, 4);					//检测对应内存区域是否可写，不可写则抛出异常
			ExRaiseStatus(STATUS_ACCESS_VIOLATION);			//抛出指定异常
			ExRaiseAccessViolation();						//抛出内存错误操作的异常
			ExRaiseDatatypeMisalignment();					//抛出字节未对齐的异常
修改记录:

  1.  日期: 2024.11.16
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 捕获抛出的异常
/// </summary>
/// <param name=""></param>
VOID TryExcept(VOID)
{
	PCHAR pchBuf = 0x80000000;
	__try
	{
		//*pchBuf = 1;
		//ProbeForRead(pchBuf, 1, 4);					//检测对应内存区域是否可读，不可读则抛出异常
		//ProbeForWrite(pchBuf, 1, 4);					//检测对应内存区域是否可写，不可写则抛出异常
		//ExRaiseStatus(STATUS_ACCESS_VIOLATION);		//抛出指定异常
		//ExRaiseAccessViolation();						//抛出内存错误操作的异常
		ExRaiseDatatypeMisalignment();					//抛出字节未对齐的异常
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("%d\n", GetExceptionCode()));
	}
}

/// <summary>
/// 支持执行指定最终作用域
/// </summary>
/// <param name=""></param>
VOID TryFinnal(VOID)
{
	PCHAR pchBuf = NULL;
	__try
	{
		KdPrint(("__try\n"));
		__leave;
	}
	__finally
	{
		KdPrint(("__finally\n"));
		return;
	}

	KdPrint(("TryFinnal is end\n"));
}

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DiverUnload;

	TryExcept();

	KdPrint(("\n"));
	TryFinnal();

	KdPrint(("驱动加载成功\n"));
	return STATUS_SUCCESS;
}

