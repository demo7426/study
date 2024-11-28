/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.28
描  述: 内核模式下的创建文件
备  注:
修改记录:

  1.  日期: 2024.11.28
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/


#include <ntddk.h>

/// <summary>
/// 创建文件测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test01(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\test01.log");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	InitializeObjectAttributes(&tObjAttr, &tUniStrFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL, 
		&tObjAttr,
		&tIOStatus, 
		NULL, 
		FILE_ATTRIBUTE_NORMAL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		FILE_OPEN_IF, 
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL, 
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件创建/打开失败\n"));
		return lNTStatus;
	}

	KdPrint(("文件创建/打开成功\n"));
	ZwClose(handFile);
}

/// <summary>
/// 创建文件测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test02(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\test02.log");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	InitializeObjectAttributes(&tObjAttr, &tUniStrFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);
	
	lNTStatus = IoCreateFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN_IF,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0,
		CreateFileTypeNone,
		NULL,
		IO_NO_PARAMETER_CHECKING
		);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件创建/打开失败\n"));
		return lNTStatus;
	}

	KdPrint(("文件创建/打开成功\n"));
	ZwClose(handFile);
}

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DiverUnload;

	KdPrint(("驱动加载成功\n"));

	Test01();
	Test02();

	return lNTStatus;
}

