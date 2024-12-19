/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.19
描  述: 时间函数与irp超时处理
备  注:	
修改记录:

  1.  日期: 2024.12.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

KTIMER g_tKTimer;
KDPC g_tkDpc;
LARGE_INTEGER g_tTimeout;		//DPC定时器间隔

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Driver_Close (_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DPC_Timer_Routine(_In_ struct _KDPC* Dpc, _In_opt_ PVOID DeferredContext, _In_opt_ PVOID SystemArgument1, _In_opt_ PVOID SystemArgument2)
{
	KdPrint(("DPC_Timer_Routine is called.\n"));

	PIRP pIrp = (PIRP)DeferredContext;
	if (!pIrp)
		return;

	pIrp->IoStatus.Information = 0;
	pIrp->IoStatus.Status = STATUS_CANCELLED;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	//KeSetTimer(&g_tKTimer, g_tTimeout, &g_tkDpc);
}

/// <summary>
/// 打印本地时间
/// </summary>
/// <param name=""></param>
VOID PrintLocalTime(VOID)
{
	LARGE_INTEGER tSystemTime;
	LARGE_INTEGER tLocalTime;
	TIME_FIELDS tTimeFields;

	KeQuerySystemTime(&tSystemTime);
	ExSystemTimeToLocalTime(&tSystemTime, &tLocalTime);
	RtlTimeToTimeFields(&tLocalTime, &tTimeFields);

	KdPrint(("本地时间: %4d-%2d-%2d %2d:%2d:%2d:%3d",
		tTimeFields.Year, tTimeFields.Month, tTimeFields.Day,
		tTimeFields.Hour, tTimeFields.Minute, tTimeFields.Second, tTimeFields.Milliseconds));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));

	if (DriverObject->DeviceObject)
	{
		UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");			//符号链接名

		KeCancelTimer(&g_tKTimer);

		IoDeleteSymbolicLink(&tSysbolicLinkName);
		IoDeleteDevice(DriverObject->DeviceObject);
	}
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptDeviceObj = NULL;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//设备对象名
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//符号链接名

	KdPrint(("驱动加载成功\n"));

	DriverObject->DriverUnload = DriverUnload;

	//创建一个设备对象，其设备对象名称有操作系统自动生成
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建设备对象失败\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSysbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建符号链接失败\n"));
		return lNTStatus;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = Driver_Create;
	DriverObject->MajorFunction[IRP_MJ_READ] = Driver_Read;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Driver_Close;

	PrintLocalTime();

	return lNTStatus;
}

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Create is enter.\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Read is enter.\n"));

	KeInitializeTimer(&g_tKTimer);
	KeInitializeDpc(&g_tkDpc, DPC_Timer_Routine, Irp);

	g_tTimeout = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);
	KeSetTimer(&g_tKTimer, g_tTimeout, &g_tkDpc);

	IoMarkIrpPending(Irp);

	return STATUS_PENDING;
}

NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Close is enter.\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
