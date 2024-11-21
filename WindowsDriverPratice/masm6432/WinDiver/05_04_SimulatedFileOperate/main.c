/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.21
描  述: 模拟文件操作
备  注:
修改记录:

  1.  日期: 2024.11.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

#define MAX_BUF_LEN 4 * 1024			//最大缓冲区长度

/// <summary>
/// 设备扩展
/// </summary>
typedef struct _DEVICE_EXTENSION
{
	PCHAR Buffer;						//缓冲区起始地址
	UINT32 SumLen;						//缓冲区总长度
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;

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

/// <summary>
/// 写入数据
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_WriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 查询文件信息
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_QueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	pDeviceEx = DriverObject->DeviceObject->DeviceExtension;

	//释放资源，防止内存泄露
	pDeviceEx && pDeviceEx->Buffer ? ExFreePool(pDeviceEx->Buffer) : 0;

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
	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	lNTStatus = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);		//最后一个参数传入的应该是二级指针
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
	DriverObject->MajorFunction[IRP_MJ_WRITE] = Dispatch_WriteData;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = Dispatch_QueryFile;

	pDeviceEx = (PDEVICE_EXTENSION)ptDeviceObject->DeviceExtension;

	pDeviceEx->Buffer = (PCHAR)ExAllocatePool(PagedPool, MAX_BUF_LEN);
	if (pDeviceEx->Buffer == NULL)
	{
		KdPrint(("ExAllocatePool Buffer is err\n"));
		IoDeleteDevice(ptDeviceObject);
		IoDeleteSymbolicLink(&tSymbolicLinkName);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	pDeviceEx->SumLen = MAX_BUF_LEN;

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
	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	__try
	{
		ULONG ulOffset = pIOStack->Parameters.Read.ByteOffset.LowPart;
		
		ulReadLen = pIOStack->Parameters.Read.Length;
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
		
		if (ulReadLen + ulOffset > pDeviceEx->SumLen)
		{
			KdPrint(("读取数据区域有一部分不在缓冲内，失败\n"));
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			RtlCopyMemory(Irp->AssociatedIrp.SystemBuffer, pDeviceEx->Buffer + ulOffset, ulReadLen);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("读取数据抛出异常\n"));

		ulReadLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulReadLen;
	Irp->IoStatus.Status = lNTStatus;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_WriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulWriteLen = 0;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	__try
	{
		ULONG ulOffset = pIOStack->Parameters.Write.ByteOffset.LowPart;
		
		ulWriteLen = pIOStack->Parameters.Write.Length;
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;

		if (ulWriteLen + ulOffset > pDeviceEx->SumLen)
		{
			KdPrint(("写入数据区域有一部分不在缓冲内，失败\n"));
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			if (Irp->AssociatedIrp.SystemBuffer != NULL)
				RtlCopyMemory(pDeviceEx->Buffer + ulOffset, Irp->AssociatedIrp.SystemBuffer, ulWriteLen);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("写入数据抛出异常\n"));

		ulWriteLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulWriteLen;
	Irp->IoStatus.Status = lNTStatus;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_QueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulQueryLen = 0;

	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	__try
	{
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
		ulQueryLen = pIOStack->Parameters.QueryFile.Length;

		if (pIOStack->Parameters.QueryFile.FileInformationClass == FileStandardInformation &&
			ulQueryLen >= sizeof(FILE_STANDARD_INFORMATION))
		{
			PFILE_STANDARD_INFORMATION ptFileStandardInfo = (PFILE_STANDARD_INFORMATION)Irp->AssociatedIrp.SystemBuffer;

			ptFileStandardInfo->EndOfFile.LowPart = pDeviceEx->SumLen;

			ulQueryLen = sizeof(FILE_STANDARD_INFORMATION);
		}
		else
		{
			lNTStatus = STATUS_BUFFER_TOO_SMALL;
			ulQueryLen = 0;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("查询文件抛出异常\n"));

		ulQueryLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulQueryLen;
	Irp->IoStatus.Status = lNTStatus;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}
