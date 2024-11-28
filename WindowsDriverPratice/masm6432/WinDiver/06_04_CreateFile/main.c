/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.28
��  ��: �ں�ģʽ�µĴ����ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.28
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/


#include <ntddk.h>

/// <summary>
/// �����ļ�����
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
		KdPrint(("�ļ�����/��ʧ��\n"));
		return lNTStatus;
	}

	KdPrint(("�ļ�����/�򿪳ɹ�\n"));
	ZwClose(handFile);
}

/// <summary>
/// �����ļ�����
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
		KdPrint(("�ļ�����/��ʧ��\n"));
		return lNTStatus;
	}

	KdPrint(("�ļ�����/�򿪳ɹ�\n"));
	ZwClose(handFile);
}

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DiverUnload;

	KdPrint(("�������سɹ�\n"));

	Test01();
	Test02();

	return lNTStatus;
}

