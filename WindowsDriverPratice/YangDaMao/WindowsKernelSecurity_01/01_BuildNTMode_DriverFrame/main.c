/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.19
描  述: 创建一个NT模式的过滤驱动框架
备  注: 
修改记录:

  1.  日期: 2024.02.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	if (!DriverObject->DeviceObject)
		return;

	PDEVICEEXTENSION ptDevExtension = (PDEVICEEXTENSION)DriverObject->DeviceObject->DeviceExtension;
	if (!ptDevExtension)
		return;

	IoAcquireRemoveLock(&ptDevExtension->IORemoveLock, ptDevExtension->IORemoveLock_Tag);				//保证当下层驱动执行当前IRP中的回调例程函数时成功调用

	if (ptDevExtension->pNextDevice)
		IoDetachDevice(ptDevExtension->pNextDevice);

	IoReleaseRemoveLockAndWait(&ptDevExtension->IORemoveLock, ptDevExtension->IORemoveLock_Tag);		//保证所有的irp请求正常处理完毕

	if (DriverObject->DeviceObject)
	{
		IoDeleteDevice(DriverObject->DeviceObject);
	}

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptPDO = NULL;
	PDEVICE_OBJECT ptFDO = NULL;

	DriverObject->DriverUnload = DriverUnload;

	ptPDO = GetDeviceObjectByName(L"\\Device\\HelloDDK");
	if (!ptPDO)
	{
		KdPrint(("GetDeviceObjectByName is err.\n"));
		return lNTStatus;
	}

	ptFDO = CreateNewDeviceAndAttachedToPDO(DriverObject, ptPDO);
	if (!ptFDO)
	{
		KdPrint(("CreateNewDeviceAndAttachedToPDO is err.\n"));
		ObDereferenceObject(ptPDO);
		ptPDO = NULL;
		return lNTStatus;
	}

	ObDereferenceObject(ptPDO);
	ptPDO = NULL;

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


