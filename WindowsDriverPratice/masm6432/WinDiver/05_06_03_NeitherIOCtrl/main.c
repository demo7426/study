/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.24
描  述: IO控制，使用其它的方式
备  注:	是否为其它的方式，有 IO Method 操作码决定，而非创建设备文件时的 Flags 决定
修改记录:

  1.  日期: 2024.11.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

//Function 需要从 0x800 开始，前面的被内核系统占用
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)			//读数据
#define IO_WRITE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)			//写数据
#define IO_QUERY_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)			//查询信息

/// <summary>
/// 派遣函数
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 缓冲区方式的IO控制
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_BufferIOControl(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");

	IoDeleteDevice(DriverObject->DeviceObject);
	IoDeleteSymbolicLink(&tSymbolicLinkName);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_OBJECT ptDeviceObject = NULL;

	lNTStatus = IoCreateDevice(DriverObject, NULL, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);		//最后一个参数传入的应该是二级指针
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建设备文件失败\n"));
		return lNTStatus;
	}

	ptDeviceObject->Flags |= DO_DIRECT_IO;					//设置缓冲的操作方式
	ptDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;			//清除初始化标志

	lNTStatus = IoCreateSymbolicLink(&tSymbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建符号链接文件失败\n"));
		IoDeleteDevice(ptDeviceObject);
		return lNTStatus;
	}

	for (size_t i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = Driver_Dispatch;
	}
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Dispatch_BufferIOControl;


	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));
	return lNTStatus;
}

NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	const char* pchIrpNames[] = {
		"IRP_MJ_CREATE					   ",
		"IRP_MJ_CREATE_NAMED_PIPE		   ",
		"IRP_MJ_CLOSE					   ",
		"IRP_MJ_READ					   ",
		"IRP_MJ_WRITE					   ",
		"IRP_MJ_QUERY_INFORMATION		   ",
		"IRP_MJ_SET_INFORMATION			   ",
		"IRP_MJ_QUERY_EA				   ",
		"IRP_MJ_SET_EA					   ",
		"IRP_MJ_FLUSH_BUFFERS			   ",
		"IRP_MJ_QUERY_VOLUME_INFORMATION   ",
		"IRP_MJ_SET_VOLUME_INFORMATION	   ",
		"IRP_MJ_DIRECTORY_CONTROL		   ",
		"IRP_MJ_FILE_SYSTEM_CONTROL		   ",
		"IRP_MJ_DEVICE_CONTROL			   ",
		"IRP_MJ_INTERNAL_DEVICE_CONTROL	   ",
		"IRP_MJ_SHUTDOWN				   ",
		"IRP_MJ_LOCK_CONTROL			   ",
		"IRP_MJ_CLEANUP					   ",
		"IRP_MJ_CREATE_MAILSLOT			   ",
		"IRP_MJ_QUERY_SECURITY			   ",
		"IRP_MJ_SET_SECURITY			   ",
		"IRP_MJ_POWER					   ",
		"IRP_MJ_SYSTEM_CONTROL			   ",
		"IRP_MJ_DEVICE_CHANGE			   ",
		"IRP_MJ_QUERY_QUOTA				   ",
		"IRP_MJ_SET_QUOTA				   ",
		"IRP_MJ_PNP						   ",
		"IRP_MJ_PNP_POWER				   ",
		"IRP_MJ_MAXIMUM_FUNCTION		   "
	};

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	KdPrint(("irp name:%s\n", pchIrpNames[pIOStack->MajorFunction]));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Dispatch_BufferIOControl(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	//IO控制
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulCtrlCode = pIOStack->Parameters.DeviceIoControl.IoControlCode;

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulRtnLen = 0;

	ULONG ulInBufLen = pIOStack->Parameters.DeviceIoControl.InputBufferLength;			//输入buf的长度
	ULONG ulOutBufLen = pIOStack->Parameters.DeviceIoControl.OutputBufferLength;		//输出buf的长度
	PCHAR pchInBuf = pIOStack->Parameters.DeviceIoControl.Type3InputBuffer;				//输入buf
	PCHAR pchOutBuf = Irp->UserBuffer;													//输出buf
	__try
	{
		switch (ulCtrlCode)
		{
		case IO_READ_CODE:				//读取数据
		{
			const char* pchBuf = "这是一条来自于内核层的字符串";
			if (ulOutBufLen >= strlen(pchBuf))
			{
				RtlCopyMemory(pchOutBuf, pchBuf, strlen(pchBuf));

				lNTStatus = STATUS_SUCCESS;
				ulRtnLen = strlen(pchBuf);
			}
			else
			{
				lNTStatus = STATUS_BUFFER_TOO_SMALL;
				ulRtnLen = 0;
			}
		}
		break;
		case IO_WRITE_CODE:				//写入数据
		{
			PCHAR pchBuf = ExAllocatePool(PagedPool, ulInBufLen + 1);			//创建一个更大的缓冲区接收数据，防止之后打印数据时，访问到非法内存
			if (pchBuf == NULL)
			{
				lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
				ulRtnLen = 0;
			}
			else
			{
				RtlZeroMemory(pchBuf, ulInBufLen + 1);
				RtlCopyMemory(pchBuf, pchInBuf, ulInBufLen);

				KdPrint(("%s\n", pchBuf));

				lNTStatus = STATUS_SUCCESS;
				ulRtnLen = strlen(pchBuf);

				ExFreePool(pchBuf);
				pchBuf = NULL;
			}
		}
		break;
		case IO_QUERY_CODE:				//查询数据
		{
			KdPrint(("IO_QUERY_CODE\n"));
			lNTStatus = STATUS_SUCCESS;
			ulRtnLen = 4 * 1024;
		}
		break;
		default:
			break;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulRtnLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulRtnLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}