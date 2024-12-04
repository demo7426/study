/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.04
��  ��: �½�ע���Ŀ¼
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.04
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/


#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

/// <summary>
/// ����ע���Ŀ¼
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test01(VOID)
{
	HANDLE handRootKey;
	HANDLE handSubKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//�½���ע������·��
	UNICODE_STRING tSubRegPath = RTL_CONSTANT_STRING(L"MySubKey");										//�������·��
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	InitializeObjectAttributes(&tObj_Attr, &tRootRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	ulNTStatus = ZwCreateKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr, 0, NULL, REG_OPTION_NON_VOLATILE, &ulRet);
	if (NT_SUCCESS(ulNTStatus))
	{
		if(ulRet == REG_CREATED_NEW_KEY)
			KdPrint(("����ڣ������ɹ�\n"));
		else if (ulRet == REG_OPENED_EXISTING_KEY)
			KdPrint(("����ڣ��򿪳ɹ�\n"));
	}
	else
	{
		KdPrint(("���\\��ʧ��\n"));
	}

	//����/������
	InitializeObjectAttributes(&tObj_Attr, &tSubRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, handRootKey, NULL);

	ulNTStatus = ZwCreateKey(&handSubKey, KEY_ALL_ACCESS, &tObj_Attr, 0, NULL, REG_OPTION_NON_VOLATILE, &ulRet);
	if (NT_SUCCESS(ulNTStatus))
	{
		if (ulRet == REG_CREATED_NEW_KEY)
			KdPrint(("������ڣ������ɹ�\n"));
		else if (ulRet == REG_OPENED_EXISTING_KEY)
			KdPrint(("������ڣ��򿪳ɹ�\n"));
	}
	else
	{
		KdPrint(("�����\\��ʧ��\n"));
	}

	ZwClose(handSubKey);
	ZwClose(handRootKey);

	return ulNTStatus;
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("�������سɹ�\n"));

	Test01();

	return STATUS_SUCCESS;
}


