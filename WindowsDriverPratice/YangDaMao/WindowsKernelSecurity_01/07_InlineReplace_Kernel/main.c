/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.22
描  述: 通过替换代码段机器码，实现键盘过滤驱动
备  注: 仅支持x86架构的64位操作系统
修改记录:

  1.  日期: 2024.02.22
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"
#include "Dispatch.h"

extern MYCODE g_tNewMyCode;
extern MYCODE g_tOldMyCode;

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;
	KIRQL tKIrqL = { 0 };

	tKIrqL = WPOff();
	RtlCopyMemory(g_pfOld_Dispatch_Read, &g_tOldMyCode, sizeof(MYCODE));
	WPOn(tKIrqL);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;
	KIRQL tKIrqL = { 0 };

	DriverObject->DriverUnload = DriverUnload;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return lNTStatus;
	}
	
	g_pfOld_Dispatch_Read = ptDriverObj->MajorFunction[IRP_MJ_READ];

	g_tNewMyCode.TargetAddr = Dispatch_Read;

	//内核直接修改Irp派遣函数的代码段
	tKIrqL = WPOff();
	RtlCopyMemory(&g_tOldMyCode, g_pfOld_Dispatch_Read, sizeof(MYCODE));
	RtlCopyMemory(g_pfOld_Dispatch_Read, &g_tNewMyCode, sizeof(MYCODE));
	WPOn(tKIrqL);

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


