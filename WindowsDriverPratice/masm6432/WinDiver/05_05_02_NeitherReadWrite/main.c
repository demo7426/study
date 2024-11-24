/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.22
描  述: 其它方式读写文件
		内核层直接操作用户层的虚拟地址修改数据；在用户层出现线程切换时，容易导致用户层的虚拟地址为非法，造成系统崩溃；
		TODO:获取文件属性时出现Mdl的内存映射为空的情况，待解决
备  注:
修改记录:

  1.  日期: 2024.11.22
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
}DEVICE_EXTENSION, * PDEVICE_EXTENSION;

/// <summary>
/// 派遣函数
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 其它方式读取数据
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_NeitherReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 其它方式写入数据
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_NeitherWriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// 其它方式查询文件信息
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_NeitherQueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_EXTENSION pDeviceEx = NULL;			//设备扩展

	pDeviceEx = DriverObject->DeviceObject->DeviceExtension;

	//释放资源，防止内存泄露
	pDeviceEx&& pDeviceEx->Buffer ? ExFreePool(pDeviceEx->Buffer) : 0;

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

	ptDeviceObject->Flags |= 0;									//设置其它方式读取方式，在内核层直接操作用户层的虚拟地址修改数据
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
	DriverObject->MajorFunction[IRP_MJ_READ] = Dispatch_NeitherReadData;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = Dispatch_NeitherWriteData;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = Dispatch_NeitherQueryFile;

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

NTSTATUS Dispatch_NeitherReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulReadLen = 0;

	__try
	{
		ulReadLen = pIOStack->Parameters.Read.Length;
		if (ulReadLen >= 256)							//保证内核层数据正常写入
		{
			RtlCopyMemory(Irp->UserBuffer, "这是一条来自于内核层的数据", strlen("这是一条来自于内核层的数据"));

			lNTStatus = STATUS_SUCCESS;
			ulReadLen = strlen("这是一条来自于内核层的数据");
		}
		else
		{
			lNTStatus = STATUS_BUFFER_TOO_SMALL;
			ulReadLen = 0;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulReadLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulReadLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_NeitherWriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulWriteLen = 0;

	__try
	{
		PCHAR pchStartAddr = NULL;

		ulWriteLen = pIOStack->Parameters.Write.Length;

		pchStartAddr = (PCHAR)ExAllocatePool(PagedPool, ulWriteLen + 1);
		if (!pchStartAddr)
		{
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
			ulWriteLen = 0;
		}
		else
		{
			RtlZeroMemory(pchStartAddr, ulWriteLen + 1);
			RtlCopyMemory(pchStartAddr, Irp->UserBuffer, ulWriteLen);
			KdPrint(("%s\n", pchStartAddr));

			ExFreePool(pchStartAddr);
			pchStartAddr = NULL;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulWriteLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulWriteLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_NeitherQueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulRtnLen = 0;

	__try
	{
		ulRtnLen = pIOStack->Parameters.QueryFile.Length;

		if (pIOStack->Parameters.QueryFile.FileInformationClass == FileStandardInformation &&
			pIOStack->Parameters.QueryFile.Length >= sizeof(FILE_STANDARD_INFORMATION))
		{
			PFILE_STANDARD_INFORMATION ptFileStandInfo = Irp->UserBuffer;

			ptFileStandInfo->EndOfFile.LowPart = 4 * 1024;
		}
		else
		{
			lNTStatus = STATUS_BUFFER_TOO_SMALL;
			ulRtnLen = 0;
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