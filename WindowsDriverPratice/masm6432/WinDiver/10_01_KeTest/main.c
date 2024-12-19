/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.19
描  述: 通过设备句柄调用驱动程序
备  注:
修改记录:

  1.  日期: 2024.12.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

VOID APC_Routine(_In_ PVOID ApcContext, _In_ PIO_STATUS_BLOCK IoStatusBlock, _In_ ULONG Reserved)
{
	PKEVENT ptKEvent = (PKEVENT)ApcContext;
	if (!ptKEvent)
		return;

	KeSetEvent(ptKEvent, IO_NO_INCREMENT, FALSE);
}

/// <summary>
/// 通过设备句柄，同步调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Sync_Test01(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);

	InitializeObjectAttributes(&tObjAttr, &tDeviceName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL, 
		&tObjAttr, 
		&tIO_Status, 
		NULL, 
		FILE_ATTRIBUTE_NORMAL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		FILE_OPEN, 
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL, 
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("打开文件失败: 0x%x\n", lNTStatus));
		return;
	}

	ZwReadFile(handFile, NULL, NULL, NULL, &tIO_Status, NULL, 0, &tOffset, NULL);

	ZwClose(handFile);
}

/// <summary>
/// 通过设备句柄，异步调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test02(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;

	InitializeObjectAttributes(&tObjAttr, &tSysbolicLinkName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIO_Status,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("打开文件失败: 0x%x\n", lNTStatus));
		return;
	}

	KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);
	lNTStatus = ZwReadFile(handFile, NULL, APC_Routine, &tKEvent, &tIO_Status, NULL, 0, &tOffset, NULL);

	//lNTStatus 返回值为 STATUS_CANCELLED
	//TODO:下面的代码没有生效
	if (NT_SUCCESS(lNTStatus))
	{
		if (lNTStatus == STATUS_PENDING)
		{
			KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
		}
		
	}
	KdPrint(("ZwReadFile: 0x%x\n", lNTStatus));

	ZwClose(handFile);
}


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptDeviceObj = NULL;

	KdPrint(("驱动加载成功\n"));

	DriverObject->DriverUnload = DriverUnload;

	//CallDiver_Sync_Test01();
	CallDiver_Async_Test02();

	return lNTStatus;
}


