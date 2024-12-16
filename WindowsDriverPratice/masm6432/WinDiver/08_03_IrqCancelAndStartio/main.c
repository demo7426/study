/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.16
描  述: irq取消和startio函数
备  注:
修改记录:

  1.  日期: 2024.12.16
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

//创建或打开文件中断回调函数
NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//读取文件数据中断回调函数
NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//清理文件中断回调函数
NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//关闭文件中断回调函数
NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

#ifdef _STARTIO 
//startio函数
VOID Driver_Startio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);
#endif

//Irq取消函数
VOID Irp_Cancel(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ _IRQL_uses_cancel_ struct _IRP* Irp);


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号文件路径名

	if (DriverObject->DeviceObject)
		IoDeleteDevice(DriverObject->DeviceObject);

	IoDeleteSymbolicLink(&tSymbolicName);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;												//函数状态返回值
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");			//设备文件路径名
	UNICODE_STRING tSymbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号文件路径名
	PDEVICE_OBJECT ptDeviceObj = NULL;													//设备对象

	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建设备文件失败\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSymbolicName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建符号链接失败\n"));
		IoDeleteDevice(ptDeviceObj);
		return lNTStatus;
	}

	DriverObject->DriverUnload = DriverUnload;

#ifdef _STARTIO 
	DriverObject->DriverStartIo = Driver_Startio;
#endif // _STARTIO 


	DriverObject->MajorFunction[IRP_MJ_CREATE] = Driver_Create;
	DriverObject->MajorFunction[IRP_MJ_READ] = Driver_Read;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = Driver_Cleanup;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Driver_Close;

	ptDeviceObj->Flags |= DO_BUFFERED_IO;
	ptDeviceObj->Flags &= ~DO_DEVICE_INITIALIZING;

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("打开打开文件成功\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("进入Read\n"));


#ifdef _STARTIO 
	IoMarkIrpPending(Irp);											//将irq置于待处理状态

	IoStartPacket(DeviceObject, Irp, NULL, Irp_Cancel);				//如果有 挂起的Irp请求，则调用 Driver_Startio 函数进行处理
#else
	IoSetCancelRoutine(Irp, Irp_Cancel);

	IoMarkIrpPending(Irp);											//将irq置于待处理状态
#endif


	KdPrint(("退出Read\n"));

	return STATUS_PENDING;
}

NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	INT32 nIrqCounter = 0;

	KdPrint(("进入Cleanup\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("退出Cleanup\n"));

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("进入Close\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("退出Close\n"));

	return STATUS_SUCCESS;
}


VOID Irp_Cancel(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ _IRQL_uses_cancel_ struct _IRP* Irp)
{
	KdPrint(("进入Cancel\n"));

	IoReleaseCancelSpinLock(Irp->CancelIrql);			//必须释放自旋锁;TODO：必须调用该函数的原因未知

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_CANCELLED;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("退出Cancel\n"));
}

#ifdef _STARTIO 
VOID Driver_Startio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("进入Driver_Startio\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	IoStartNextPacket(DeviceObject, TRUE);

	KdPrint(("退出Driver_Startio\n"));
}
#endif

