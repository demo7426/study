/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.21
描  述: 通过替换派遣函数，实现键盘过滤驱动
备  注: 
修改记录:

  1.  日期: 2024.02.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"
#include "Dispatch.h"


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return;
	}

#ifdef _X86_
	InterlockedExchange((volatile LONG32*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG32)g_pfOld_Dispatch_Read);
#else
	InterlockedExchange64((volatile LONG64*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG64)Old_Dispatch_Read);
#endif // _WIN32_

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;

	DriverObject->DriverUnload = DriverUnload;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return lNTStatus;
	}

	//替换派遣函数
#ifdef _X86_
	g_pfOld_Dispatch_Read = (Dispatch_Read_FuncType)InterlockedExchange((volatile LONG32*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG32)Dispatch_Read);
#else
	Old_Dispatch_Read = (Dispatch_Read_FuncType)InterlockedExchange64((volatile LONG64*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG64)Dispatch_Read);
#endif // _WIN32_

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


