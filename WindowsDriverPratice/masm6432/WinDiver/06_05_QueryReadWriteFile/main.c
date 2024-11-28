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
/// 文件信息查询
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test01(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\Program Files\\Windows Media Player\\setup_wm.exe");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	FILE_STANDARD_INFORMATION tFileStandInfo;

	InitializeObjectAttributes(&tObjAttr, &tUniStrFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwOpenFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		FILE_SHARE_READ,
		FILE_SYNCHRONOUS_IO_NONALERT
		);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件打开失败\n"));
		return lNTStatus;
	}

	lNTStatus = ZwQueryInformationFile(handFile, &tIOStatus, &tFileStandInfo, sizeof(tFileStandInfo), FileStandardInformation);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件查询信息失败\n"));
		return lNTStatus;
	}

	KdPrint(("文件大小 = %d字节\n", tFileStandInfo.EndOfFile.LowPart));
	ZwClose(handFile);
}

/// <summary>
/// 读写文件测试
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test02(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\test01.log");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	CHAR chBuf[1024] = { 0 };
	FILE_POSITION_INFORMATION tFilePosInfo;

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
		0
	);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件创建/打开失败\n"));
		return lNTStatus;
	}

	//向文件写入数据
	ZwWriteFile(handFile, NULL, NULL, NULL, &tIOStatus, "这是文件内部数据", strlen("这是文件内部数据"), NULL, NULL);

	//设置文件指针偏移
	tFilePosInfo.CurrentByteOffset.QuadPart = 0;		//必须 LARGE_INTEGER 的 QuadPart 将其高低位所有数据赋值为0
	ZwSetInformationFile(handFile, &tIOStatus, &tFilePosInfo, sizeof(tFilePosInfo), FilePositionInformation);

	//读取文件数据
	lNTStatus = ZwReadFile(handFile, NULL, NULL, NULL, &tIOStatus, chBuf, sizeof(chBuf), NULL, NULL);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("文件读取失败: 0x%x\n", lNTStatus));
		ZwClose(handFile);
		return lNTStatus;
	}

	KdPrint(("%s\n", chBuf));
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

