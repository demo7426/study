/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: 创建一个驱动的符号对象，及打印驱动对象的部分信息
备  注:
修改记录:

  1.  日期: 2024.11.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 打印驱动部分相关信息
/// </summary>
/// <param name="_pDriverObject"></param>
VOID EnumDriver(PDRIVER_OBJECT _pDriverObject);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	
	IoDeleteSymbolicLink(&tSysbolicLinkName);
	IoDeleteDevice(DriverObject->DeviceObject);
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");
	PDEVICE_OBJECT ptDeviceObject = NULL;

	KdPrint(("驱动加载开始\n"));

	DriverObject->DriverUnload = DriverUnload;
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建设备对象失败\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSysbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("创建符号表链接对象失败\n"));
		return lNTStatus;
	}

	DriverObject->Flags |= DO_BUFFERED_IO;				//表示使用驱动缓冲IO的方式，即在内存中为I/O请求分配缓冲区
	DriverObject->Flags &= ~DO_DEVICE_INITIALIZING;		//清除 DO_DEVICE_INITIALIZING 标志，通知系统设备已初始化完成，可以开始接收请求

	EnumDriver(DriverObject);

	KdPrint(("驱动加载成功\n"));
	return lNTStatus;
}

VOID EnumDriver(PDRIVER_OBJECT _pDriverObject)
{
	KdPrint(("Driver:0x%p\n", _pDriverObject));
	KdPrint(("Device:0x%p\n", _pDriverObject->DeviceObject));
	KdPrint(("驱动对象名:%wZ\n", &_pDriverObject->DriverName));
	KdPrint(("服务名:%wZ\n", &_pDriverObject->DriverExtension->ServiceKeyName));
	KdPrint(("硬件数据库名:%wZ\n", _pDriverObject->HardwareDatabase));
}
