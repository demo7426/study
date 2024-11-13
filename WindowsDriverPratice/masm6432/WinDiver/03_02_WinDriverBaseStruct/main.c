/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.13
描  述: 实现一个windows 驱动程序的基本结构
备  注:
修改记录:

  1.  日期: 2024.11.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	IoDeleteDevice(DriverObject->DeviceObject);
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	DEVICE_OBJECT tDeviceObj;

	KdPrint(("驱动加载开始\n"));

	DriverObject->DriverUnload = DriverUnload;
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &tDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("驱动加载失败\n"));
		return lNTStatus;
	}

	DriverObject->Flags |= DO_BUFFERED_IO;				//表示使用驱动缓冲IO的方式，即在内存中为I/O请求分配缓冲区
	DriverObject->Flags &= ~DO_DEVICE_INITIALIZING;		//清除 DO_DEVICE_INITIALIZING 标志，通知系统设备已初始化完成，可以开始接收请求

	KdPrint(("驱动加载成功\n"));
	return lNTStatus;
}


