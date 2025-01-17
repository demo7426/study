/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.17
描  述: 拷贝、删除、重命名文件，遍历文件夹目录结构
备  注:
修改记录:

  1.  日期: 2025.01.17
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>

//文件拷贝，最多拷贝32MB大小的文件
VOID CopyFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName);

//文件删除
VOID DeleteFile(WCHAR* _pSrcFileName);

//文件重命名
VOID RenameFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName);

//遍历指定的文件目录
VOID TraverseFileDir(WCHAR* _pSrcDirName);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动成功卸载\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	WCHAR* wchSrcFileName = L"\\??\\C:\\Windows\\System32\\drivers\\acpi.sys";		//源文件
	WCHAR* wchDesFileName = L"\\??\\C:\\acpi拷贝副本.sys";							//目标文件
	WCHAR* wchRenameFileName = L"\\??\\C:\\acpi重命名副本.sys";						//目标文件
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//延时时间

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动成功加载\n"));

	CopyFile(wchSrcFileName, wchDesFileName);										//拷贝文件

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
	RenameFile(wchDesFileName, wchRenameFileName);									//重命名文件

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
	DeleteFile(wchRenameFileName);													//删除文件

	TraverseFileDir(L"\\??\\C:\\Windows\\System32\\drivers\\");						//遍历文件夹目录结构

	return lNTStatus;
}

VOID CopyFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hFile = NULL;
	UNICODE_STRING tSrcFileName;													//源文件名称
	UNICODE_STRING tDesFileName;													//目标文件名称
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	IO_STATUS_BLOCK tIOStatus = { 0 };
	FILE_STANDARD_INFORMATION tFileStandardInfo = { 0 };							//文件标准信息
	PCHAR pchReadFileDateBuf = NULL;												//文件内部读取出的数据缓冲

	RtlInitUnicodeString(&tSrcFileName, _pSrcFileName);
	RtlInitUnicodeString(&tDesFileName, _pDesFileName);

	InitializeObjectAttributes(&tObjAttr, &tSrcFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&hFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwCreateFile is err.\n"));
		return;
	}

	lNTStatus = ZwQueryInformationFile(hFile, &tIOStatus, &tFileStandardInfo, sizeof tFileStandardInfo, FileStandardInformation);
	if (!NT_SUCCESS(lNTStatus))
	{
		ZwClose(hFile);
		KdPrint(("ZwQueryInformationFile is err.\n"));
		return;
	}

	if (tFileStandardInfo.EndOfFile.LowPart > 32 * 1024 * 1024)
	{
		ZwClose(hFile);
		KdPrint(("Copy file is too large.\n"));
		return;
	}

	pchReadFileDateBuf = ExAllocatePool(PagedPool, tFileStandardInfo.EndOfFile.LowPart);
	if (!pchReadFileDateBuf)
	{
		ZwClose(hFile);
		KdPrint(("ExAllocatePool is err.\n"));
		return;
	}

	lNTStatus = ZwReadFile(hFile, NULL, NULL, NULL, &tIOStatus, pchReadFileDateBuf, tFileStandardInfo.EndOfFile.LowPart, NULL, NULL);
	if (!NT_SUCCESS(lNTStatus))
	{
		ZwClose(hFile);
		KdPrint(("ZwReadFile is err.\n"));
		return;
	}

	ZwClose(hFile);
	hFile = NULL;

	//准备进行数据拷贝

	InitializeObjectAttributes(&tObjAttr, &tDesFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&hFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OVERWRITE_IF,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwCreateFile is err.\n"));
		return;
	}

	lNTStatus = ZwWriteFile(hFile, NULL, NULL, NULL, &tIOStatus, pchReadFileDateBuf, tFileStandardInfo.EndOfFile.LowPart, NULL, NULL);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwWriteFile is err.\n"));
		return;
	}

	ExFreePool(pchReadFileDateBuf);
	pchReadFileDateBuf = NULL;

	ZwClose(hFile);
	hFile = NULL;
}

VOID DeleteFile(WCHAR* _pSrcFileName)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tSrcFileName;											//源文件名称
	OBJECT_ATTRIBUTES tObjAttr = { 0 };

	RtlInitUnicodeString(&tSrcFileName, _pSrcFileName);

	InitializeObjectAttributes(&tObjAttr, &tSrcFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwDeleteFile(&tObjAttr);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwDeleteFile is err.\n"));
		return;
	}

	return;
}

VOID RenameFile(WCHAR* _pSrcFileName, WCHAR* _pRenameFileName)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hFile = NULL;
	UNICODE_STRING tSrcFileName;											//源文件名称
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	IO_STATUS_BLOCK tIOStatus = { 0 };
	PFILE_RENAME_INFORMATION ptFileRenameInfo = NULL;
	SIZE_T unRenameLen = sizeof(FILE_RENAME_INFORMATION) + wcslen(_pRenameFileName) * sizeof(WCHAR);

	RtlInitUnicodeString(&tSrcFileName, _pSrcFileName);

	InitializeObjectAttributes(&tObjAttr, &tSrcFileName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&hFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwCreateFile is err.\n"));
		return;
	}

	ptFileRenameInfo = ExAllocatePool(PagedPool, unRenameLen);
	if (!ptFileRenameInfo)
	{
		ZwClose(hFile);
		KdPrint(("ZwCreateFile is err.\n"));
		return;
	}

	RtlZeroMemory(ptFileRenameInfo, unRenameLen);

	RtlCopyMemory(ptFileRenameInfo->FileName, _pRenameFileName, wcslen(_pRenameFileName) * sizeof(WCHAR));
	ptFileRenameInfo->FileNameLength = wcslen(_pRenameFileName) * sizeof(WCHAR);
	ptFileRenameInfo->ReplaceIfExists = TRUE;

	lNTStatus = ZwSetInformationFile(hFile, &tIOStatus, ptFileRenameInfo, unRenameLen, FileRenameInformation);
	if (!NT_SUCCESS(lNTStatus))
	{
		ZwClose(hFile);
		KdPrint(("ZwSetInformationFile is err.\n"));
		return;
	}

	ExFreePool(ptFileRenameInfo);
	ptFileRenameInfo = NULL;

	ZwClose(hFile);
	hFile = NULL;
}

VOID TraverseFileDir(WCHAR* _pSrcDirName)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hFile = NULL;
	UNICODE_STRING tSrcDirName;											//源目录名称
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	IO_STATUS_BLOCK tIOStatus = { 0 };
	PFILE_BOTH_DIR_INFORMATION ptFileBothDirInfo = NULL;
	const SIZE_T unFileBothDirInfoLen = 1024 * 1024;					//文件目录信息最大长度
	WCHAR wchSingleFileOrDirName[260] = { 0 };							//单个文件名称，windows规定文件或文件夹名称不得超过255个字符

	RtlInitUnicodeString(&tSrcDirName, _pSrcDirName);

	InitializeObjectAttributes(&tObjAttr, &tSrcDirName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	//以同步方式打开一个目录 (FILE_DIRECTORY_FILE)，允许读写共享 (FILE_SHARE_READ | FILE_SHARE_WRITE)，并支持备份用途 (FILE_OPEN_FOR_BACKUP_INTENT)
	lNTStatus = ZwCreateFile(&hFile,
		FILE_ANY_ACCESS | FILE_LIST_DIRECTORY | SYNCHRONIZE,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE | FILE_OPEN_FOR_BACKUP_INTENT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwCreateFile is err.\n"));
		return;
	}

	ptFileBothDirInfo = ExAllocatePool(PagedPool, unFileBothDirInfoLen);
	if (!ptFileBothDirInfo)
	{
		KdPrint(("ExAllocatePool is err.\n"));
		return;
	}

	//返回有关给定文件句柄指定的目录中文件的各种信息
	lNTStatus = ZwQueryDirectoryFile(hFile, NULL, NULL, NULL, &tIOStatus, ptFileBothDirInfo, unFileBothDirInfoLen, FileBothDirectoryInformation, FALSE, NULL, TRUE);
	if (!NT_SUCCESS(lNTStatus))
	{
		ZwClose(hFile);
		KdPrint(("ZwQueryDirectoryFile is err.\n"));
		return;
	}

	PFILE_BOTH_DIR_INFORMATION ptFileBothDirInfo_Tmp = ptFileBothDirInfo;

	do//打印文件目录内部信息
	{
		RtlZeroMemory(wchSingleFileOrDirName, sizeof(wchSingleFileOrDirName));
		RtlCopyMemory(wchSingleFileOrDirName, ptFileBothDirInfo_Tmp->FileName, ptFileBothDirInfo_Tmp->FileNameLength);
		
		ptFileBothDirInfo_Tmp->FileAttributes & FILE_ATTRIBUTE_DIRECTORY? KdPrint(("[目录]:%ls\n", wchSingleFileOrDirName)): KdPrint(("[文件]:%ls\n", wchSingleFileOrDirName));

		if (ptFileBothDirInfo_Tmp->NextEntryOffset == 0)
			break;

		ptFileBothDirInfo_Tmp = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)ptFileBothDirInfo_Tmp + ptFileBothDirInfo_Tmp->NextEntryOffset);
	} while (TRUE);

	ExFreePool(ptFileBothDirInfo);
	ptFileBothDirInfo = NULL;

	ZwClose(hFile);
	hFile = NULL;
}



