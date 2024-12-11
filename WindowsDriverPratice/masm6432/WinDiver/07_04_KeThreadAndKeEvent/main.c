/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.11
描  述: 内核在指定的程序下创建线程，使用事件进行线程同步
备  注:	PsCreateSystemThread--创建线程
		ZwOpenProcess--打开进程对象的句柄，并设置对此对象的访问权限
		PsGetProcessImageFileName--获取对应的线程名称

		KeInitializeEvent--初始化事件
		KeWaitForSingleObject--等待事件
		KeSetEvent--当事件对象设置为有信号状态
修改记录:

  1.  日期: 2024.12.11
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);			//TODO:函数定义在何处？

VOID ThreadProc(_In_ PVOID StartContext)
{
	KdPrint(("该线程父进程名称: %s\n", PsGetProcessImageFileName(PsGetCurrentProcess())));		

	PsTerminateSystemThread(0);		//必须告知内核线程从这里开始结束了
}

VOID ThreadEvent(_In_ PVOID StartContext)
{
	PRKEVENT phandEvent = (PRKEVENT)StartContext;

	KdPrint(("ThreadEvent enter.\n"));

	KeSetEvent(phandEvent, IO_NO_INCREMENT, FALSE);

	KdPrint(("ThreadEvent quit.\n"));

	PsTerminateSystemThread(0);		//必须告知内核线程从这里开始结束了
}

/// <summary>
/// 内核线程创建测试
/// </summary>
/// <param name=""></param>
VOID KeThread_Test01(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE handThread;
	HANDLE handProcess;
	OBJECT_ATTRIBUTES tObjAttr;
	CLIENT_ID tClient_ID;

	PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, NULL);

	//必须对 CLIENT_ID 全部的数据进行初始化操作
	tClient_ID.UniqueProcess = (HANDLE)284;			//父进程PID，从自己的操作系统任务管理器中选择一个存在的进程
	tClient_ID.UniqueThread = (HANDLE)0;				
	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwOpenProcess(&handProcess, PROCESS_ALL_ACCESS, &tObjAttr, &tClient_ID);					//打开进程对象的句柄，并设置对此对象的访问权限
	if (NT_SUCCESS(lNTStatus))
	{
		PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, handProcess, NULL, ThreadProc, NULL);
	}
	else
	{
		KdPrint(("ZwOpenProcess is err. 0x%x\n", lNTStatus));
	}
	KdPrint(("KeThread_Test01 is end.\n"));
}

/// <summary>
/// 使用事件对线程进行数据同步
/// </summary>
/// <param name=""></param>
VOID KeEvent_Test02(VOID)
{
	KEVENT tKEvent;
	HANDLE handThread;

	KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);

	PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadEvent, &tKEvent);

	KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);

	KdPrint(("KeEvent_Test02 quit.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	KeThread_Test01();
	KeEvent_Test02();

	return STATUS_SUCCESS;
}



