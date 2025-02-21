/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Dispatch.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.19
描  述: 派遣函数
备  注:
修改记录:

  1.  日期: 2024.02.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/


#ifndef __DISPATCH_H__
#define __DISPATCH_H__

#include <ntddk.h>

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Pnp(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Power(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Write(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//异步读取
NTSTATUS Dispatch_Read_Async(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//同步读取
NTSTATUS Dispatch_Read_Sync(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

#endif // !__DISPATCH_H__

