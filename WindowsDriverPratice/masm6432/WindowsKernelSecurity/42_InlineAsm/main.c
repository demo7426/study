/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.25
描  述: 内联32位汇编，64位汇编需要安装新的vs 汇编开发环境
备  注: 
修改记录:

  1.  日期: 2025.01.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdm.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	__asm
	{
		mov al, 0feh
		out 64h, al
	}

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	return lStatus;
}

