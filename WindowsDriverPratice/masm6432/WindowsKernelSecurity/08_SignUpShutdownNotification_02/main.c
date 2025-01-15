/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.15
描  述: 使用已经存在的设备文件，对其注册关机通知
备  注:
修改记录:

  1.  日期: 2025.01.15
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/


#include <ntddk.h>
#include <wdf.h>

/// <summary>
/// 写文件
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS WriteFile(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\Shutdown01.log");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	CHAR chBuf[1024] = { 0 };
	FILE_POSITION_INFORMATION tFilePosInfo;

	InitializeObjectAttributes(&tObjAttr, &tUniStrFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN_IF,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0
	);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件创建/打开失败\n"));
		return lNTStatus;
	}

	//向文件写入数据
	ZwWriteFile(handFile, NULL, NULL, NULL, &tIOStatus, "系统关机时写入的数据", strlen("系统关机时写入的数据"), NULL, NULL);

	ZwClose(handFile);

	return lNTStatus;
}

NTSTATUS Driver_Shutdown(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	WriteFile();

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PFILE_OBJECT ptNullFileObj = NULL;
	PDEVICE_OBJECT ptNullDevObj = NULL;

	UNICODE_STRING tNullDevName = RTL_CONSTANT_STRING(L"\\Device\\Null");

	//DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = Driver_Shutdown;

	lNTStatus = IoGetDeviceObjectPointer(&tNullDevName, FILE_ANY_ACCESS, &ptNullFileObj, &ptNullDevObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("获取设备文件句柄失败\n"));
		return lNTStatus;
	}

	ObDereferenceObject(ptNullFileObj);

	ptNullDevObj->DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = Driver_Shutdown;

	IoRegisterShutdownNotification(ptNullDevObj);										//对指定的设备注册关机通知

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}

