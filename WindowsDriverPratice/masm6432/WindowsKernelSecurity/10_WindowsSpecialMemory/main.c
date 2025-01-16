/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.16
描  述: 访问Windows系统里的一块特殊的内存
备  注: 
修改记录:

  1.  日期: 2025.01.16
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>
//#include <wdf.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	KUSER_SHARED_DATA* ptKUserSharedData = SharedUserData;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	KdPrint(("系统根目录:\t%ls\n", ptKUserSharedData->NtSystemRoot));
	KdPrint(("系统内核版本号:\t%u.%u\n", ptKUserSharedData->NtMajorVersion, ptKUserSharedData->NtMinorVersion));
	KdPrint(("启动方式:\t%s\n", ptKUserSharedData->SafeBootMode? "安全模式下启动": "正常启动"));

	return lNTStatus;
}


