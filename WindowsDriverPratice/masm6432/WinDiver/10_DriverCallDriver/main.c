/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.19
描  述: 通过设备句柄、设备指针调用驱动程序
备  注:
修改记录:

  1.  日期: 2024.12.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

NTKERNELAPI
NTSTATUS
ObReferenceObjectByName(
	IN PUNICODE_STRING ObjectName,
	IN ULONG Attributes,
	IN PACCESS_STATE PassedAccessState OPTIONAL,
	IN ACCESS_MASK DesiredAccess OPTIONAL,
	IN POBJECT_TYPE ObjectType,
	IN KPROCESSOR_MODE AccessMode,
	IN OUT PVOID ParseContext OPTIONAL,
	OUT PVOID* Object
);
extern POBJECT_TYPE *IoDeviceObjectType;

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

/// <summary>
/// 通过设备指针，调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test03(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;
	PFILE_OBJECT ptFileObj = NULL;
	PDEVICE_OBJECT ptDevObj = NULL;
	PIRP pIrp = NULL;

	InitializeObjectAttributes(&tObjAttr, &tSysbolicLinkName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = IoGetDeviceObjectPointer(&tDeviceName, FILE_ANY_ACCESS, &ptFileObj, &ptDevObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("获取设备对象指针出错\n"));
		return;
	}

	KeInitializeEvent(&tKEvent, SynchronizationEvent, FALSE);

	pIrp = IoBuildSynchronousFsdRequest(IRP_MJ_READ, ptDevObj, NULL, 0, &tOffset, &tKEvent, &tIO_Status);

	IoGetNextIrpStackLocation(pIrp)->FileObject = ptFileObj;

	lNTStatus = IoCallDriver(ptDevObj, pIrp);
	if (lNTStatus == STATUS_PENDING)
	{
		KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
		KdPrint(("完成读操作\n"));
	}

	ObDereferenceObject(ptFileObj);
}

/// <summary>
/// 通过设备指针，调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test04(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;
	PFILE_OBJECT ptFileObj = NULL;
	PDEVICE_OBJECT ptDevObj = NULL;
	PIRP pIrp = NULL;

	InitializeObjectAttributes(&tObjAttr, &tSysbolicLinkName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = IoGetDeviceObjectPointer(&tDeviceName, FILE_ANY_ACCESS, &ptFileObj, &ptDevObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("获取设备对象指针出错\n"));
		return;
	}

	KeInitializeEvent(&tKEvent, SynchronizationEvent, FALSE);

	pIrp = IoBuildAsynchronousFsdRequest(IRP_MJ_READ, ptDevObj, NULL, 0, &tOffset, &tIO_Status);
	pIrp->UserEvent = &tKEvent;

	IoGetNextIrpStackLocation(pIrp)->FileObject = ptFileObj;
	
	lNTStatus = IoCallDriver(ptDevObj, pIrp);
	if (lNTStatus == STATUS_PENDING)
	{
		KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
		KdPrint(("完成读操作\n"));
	}

	ObDereferenceObject(ptFileObj);
}

/// <summary>
/// 通过设备指针，调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test05(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;
	PFILE_OBJECT ptFileObj = NULL;
	PDEVICE_OBJECT ptDevObj = NULL;
	PIRP pIrp = NULL;
	PIO_STACK_LOCATION ptIO_Stack;

	InitializeObjectAttributes(&tObjAttr, &tSysbolicLinkName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = IoGetDeviceObjectPointer(&tDeviceName, FILE_ANY_ACCESS, &ptFileObj, &ptDevObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("获取设备对象指针出错\n"));
		return;
	}

	KeInitializeEvent(&tKEvent, SynchronizationEvent, FALSE);

	pIrp = IoAllocateIrp(ptDevObj->StackSize, FALSE);
	if (pIrp)
	{
		pIrp->UserIosb = &tIO_Status;
		pIrp->UserEvent = &tKEvent;
		pIrp->AssociatedIrp.SystemBuffer = NULL;
		pIrp->Tail.Overlay.Thread = PsGetCurrentThread();

		ptIO_Stack = IoGetNextIrpStackLocation(pIrp);
		ptIO_Stack->FileObject = ptFileObj;
		ptIO_Stack->DeviceObject = ptDevObj;
		ptIO_Stack->MajorFunction = IRP_MJ_READ;
		ptIO_Stack->MinorFunction = IRP_MN_NORMAL;

		lNTStatus = IoCallDriver(ptDevObj, pIrp);
		if (lNTStatus == STATUS_PENDING)
		{
			KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
			KdPrint(("完成读操作\n"));
		}
	}
}

/// <summary>
/// 通过设备名称直接获取其指针，调用其它驱动函数测试
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test06(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;
	PFILE_OBJECT ptFileObj = NULL;
	PDEVICE_OBJECT ptDevObj;
	PDRIVER_OBJECT ptDriverObj = NULL;
	PIRP pIrp = NULL;
	PIO_STACK_LOCATION ptIO_Stack;
	
	//TODO:win7专业版调用 ObReferenceObjectByName 返回 0xc0000024，待解决
	lNTStatus = ObReferenceObjectByName(&tSysbolicLinkName, OBJ_CASE_INSENSITIVE, NULL, FILE_ANY_ACCESS, *IoDeviceObjectType, KernelMode, NULL, &ptDevObj);
	if (NT_SUCCESS(lNTStatus))
	{
		KdPrint(("设备对象指针获取成功\n"));
		KdPrint(("%p\n", ptDevObj));
		ObDereferenceObject(ptDevObj);
	}
	else
	{
		KdPrint(("设备对象获取失败 0x%x\n", lNTStatus));
	}
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
	//CallDiver_Async_Test02();
	//CallDiver_Async_Test03();
	//CallDiver_Async_Test04();
	//CallDiver_Async_Test05();
	CallDiver_Async_Test06();

	return lNTStatus;
}


