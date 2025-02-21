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

#include <wdm.h>

//对应的驱动被替换前的派遣函数指针
typedef NTSTATUS (*Dispatch_Read_FuncType)(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Pnp(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Power(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Write(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

Dispatch_Read_FuncType g_pfOld_Dispatch_Read;

#endif // !__DISPATCH_H__

