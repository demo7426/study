/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.19
描  述: 缓冲区读取数据
备  注:
修改记录:

  1.  日期: 2024.11.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 派遣函数
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 读取数据
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_ReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

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

	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);		//最后一个参数传入的应该是二级指针
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建设备文件失败\n"));
		return lNTStatus;
	}

	ptDeviceObject->Flags |= DO_BUFFERED_IO;					//设置 DO_BUFFERED_IO 标志
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
	DriverObject->MajorFunction[IRP_MJ_READ] = Dispatch_ReadData;

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

NTSTATUS Dispatch_ReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulReadLen = 0;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	__try 
	{
		if (pIOStack->Parameters.Read.Length < 1024)					//保证读取数据缓冲区数据必须大于1024字节
		{
			ulReadLen = 0;
			lNTStatus = IO_ERR_INSUFFICIENT_RESOURCES;
		}
		else
		{
			const char* pchBuf = "这是一个来自于内核层的字符串";

			PVOID systemBuffer = Irp->AssociatedIrp.SystemBuffer;
			if (systemBuffer) {
				RtlCopyMemory(systemBuffer, pchBuf, strlen(pchBuf)); // 安全写入数据
			}
			else
				KdPrint(("SystemBuffer is null\n"));

			ulReadLen = strlen(pchBuf);
			lNTStatus = STATUS_SUCCESS;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("读取数据抛出异常\n"));
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulReadLen;
	Irp->IoStatus.Status = lNTStatus;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}
