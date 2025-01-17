/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.17
��  ��: ������ɾ�����������ļ��������ļ���Ŀ¼�ṹ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.17
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdf.h>

//�ļ���������࿽��32MB��С���ļ�
VOID CopyFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName);

//�ļ�ɾ��
VOID DeleteFile(WCHAR* _pSrcFileName);

//�ļ�������
VOID RenameFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName);

//����ָ�����ļ�Ŀ¼
VOID TraverseFileDir(WCHAR* _pSrcDirName);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("�����ɹ�ж��\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	WCHAR* wchSrcFileName = L"\\??\\C:\\Windows\\System32\\drivers\\acpi.sys";		//Դ�ļ�
	WCHAR* wchDesFileName = L"\\??\\C:\\acpi��������.sys";							//Ŀ���ļ�
	WCHAR* wchRenameFileName = L"\\??\\C:\\acpi����������.sys";						//Ŀ���ļ�
	LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);		//��ʱʱ��

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�����ɹ�����\n"));

	CopyFile(wchSrcFileName, wchDesFileName);										//�����ļ�

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
	RenameFile(wchDesFileName, wchRenameFileName);									//�������ļ�

	KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
	DeleteFile(wchRenameFileName);													//ɾ���ļ�

	TraverseFileDir(L"\\??\\C:\\Windows\\System32\\drivers\\");						//�����ļ���Ŀ¼�ṹ

	return lNTStatus;
}

VOID CopyFile(WCHAR* _pSrcFileName, WCHAR* _pDesFileName)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hFile = NULL;
	UNICODE_STRING tSrcFileName;													//Դ�ļ�����
	UNICODE_STRING tDesFileName;													//Ŀ���ļ�����
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	IO_STATUS_BLOCK tIOStatus = { 0 };
	FILE_STANDARD_INFORMATION tFileStandardInfo = { 0 };							//�ļ���׼��Ϣ
	PCHAR pchReadFileDateBuf = NULL;												//�ļ��ڲ���ȡ�������ݻ���

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

	//׼���������ݿ���

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
	UNICODE_STRING tSrcFileName;											//Դ�ļ�����
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
	UNICODE_STRING tSrcFileName;											//Դ�ļ�����
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
	UNICODE_STRING tSrcDirName;											//ԴĿ¼����
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	IO_STATUS_BLOCK tIOStatus = { 0 };
	PFILE_BOTH_DIR_INFORMATION ptFileBothDirInfo = NULL;
	const SIZE_T unFileBothDirInfoLen = 1024 * 1024;					//�ļ�Ŀ¼��Ϣ��󳤶�
	WCHAR wchSingleFileOrDirName[260] = { 0 };							//�����ļ����ƣ�windows�涨�ļ����ļ������Ʋ��ó���255���ַ�

	RtlInitUnicodeString(&tSrcDirName, _pSrcDirName);

	InitializeObjectAttributes(&tObjAttr, &tSrcDirName, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	//��ͬ����ʽ��һ��Ŀ¼ (FILE_DIRECTORY_FILE)�������д���� (FILE_SHARE_READ | FILE_SHARE_WRITE)����֧�ֱ�����; (FILE_OPEN_FOR_BACKUP_INTENT)
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

	//�����йظ����ļ����ָ����Ŀ¼���ļ��ĸ�����Ϣ
	lNTStatus = ZwQueryDirectoryFile(hFile, NULL, NULL, NULL, &tIOStatus, ptFileBothDirInfo, unFileBothDirInfoLen, FileBothDirectoryInformation, FALSE, NULL, TRUE);
	if (!NT_SUCCESS(lNTStatus))
	{
		ZwClose(hFile);
		KdPrint(("ZwQueryDirectoryFile is err.\n"));
		return;
	}

	PFILE_BOTH_DIR_INFORMATION ptFileBothDirInfo_Tmp = ptFileBothDirInfo;

	do//��ӡ�ļ�Ŀ¼�ڲ���Ϣ
	{
		RtlZeroMemory(wchSingleFileOrDirName, sizeof(wchSingleFileOrDirName));
		RtlCopyMemory(wchSingleFileOrDirName, ptFileBothDirInfo_Tmp->FileName, ptFileBothDirInfo_Tmp->FileNameLength);
		
		ptFileBothDirInfo_Tmp->FileAttributes & FILE_ATTRIBUTE_DIRECTORY? KdPrint(("[Ŀ¼]:%ls\n", wchSingleFileOrDirName)): KdPrint(("[�ļ�]:%ls\n", wchSingleFileOrDirName));

		if (ptFileBothDirInfo_Tmp->NextEntryOffset == 0)
			break;

		ptFileBothDirInfo_Tmp = (PFILE_BOTH_DIR_INFORMATION)((PCHAR)ptFileBothDirInfo_Tmp + ptFileBothDirInfo_Tmp->NextEntryOffset);
	} while (TRUE);

	ExFreePool(ptFileBothDirInfo);
	ptFileBothDirInfo = NULL;

	ZwClose(hFile);
	hFile = NULL;
}



