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
/// �ļ���Ϣ��ѯ
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
		KdPrint(("�ļ���ʧ��\n"));
		return lNTStatus;
	}

	lNTStatus = ZwQueryInformationFile(handFile, &tIOStatus, &tFileStandInfo, sizeof(tFileStandInfo), FileStandardInformation);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�ļ���ѯ��Ϣʧ��\n"));
		return lNTStatus;
	}

	KdPrint(("�ļ���С = %d�ֽ�\n", tFileStandInfo.EndOfFile.LowPart));
	ZwClose(handFile);
}

/// <summary>
/// ��д�ļ�����
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
		KdPrint(("�ļ�����/��ʧ��\n"));
		return lNTStatus;
	}

	//���ļ�д������
	ZwWriteFile(handFile, NULL, NULL, NULL, &tIOStatus, "�����ļ��ڲ�����", strlen("�����ļ��ڲ�����"), NULL, NULL);

	//�����ļ�ָ��ƫ��
	tFilePosInfo.CurrentByteOffset.QuadPart = 0;		//���� LARGE_INTEGER �� QuadPart ����ߵ�λ�������ݸ�ֵΪ0
	ZwSetInformationFile(handFile, &tIOStatus, &tFilePosInfo, sizeof(tFilePosInfo), FilePositionInformation);

	//��ȡ�ļ�����
	lNTStatus = ZwReadFile(handFile, NULL, NULL, NULL, &tIOStatus, chBuf, sizeof(chBuf), NULL, NULL);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�ļ���ȡʧ��: 0x%x\n", lNTStatus));
		ZwClose(handFile);
		return lNTStatus;
	}

	KdPrint(("%s\n", chBuf));
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

