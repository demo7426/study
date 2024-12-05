/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.05
��  ��: ɾ��ע����ֵ
��  ע:	ZwDeleteKey--ɾ����
		ZwDeleteValueKey--ɾ��ֵ
�޸ļ�¼:

  1.  ����: 2024.12.05
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
		if (ulRet == REG_CREATED_NEW_KEY)
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

/// <summary>
/// �½�����ѯע���ֵ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test02(VOID)
{
	HANDLE handRootKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//�½���ע������·��
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	UNICODE_STRING tUnicKeyName;
	DWORD32 dwValue = 10;
	CHAR chBuf[] = "Hello world";

	InitializeObjectAttributes(&tObj_Attr, &tRootRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	ulNTStatus = ZwOpenKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr);
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("��򿪳ɹ�\n"));
	}
	else
	{
		KdPrint(("���ʧ��\n"));
		return ulNTStatus;
	}

	//������ֵ
	RtlInitUnicodeString(&tUnicKeyName, L"�ַ���");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_SZ, L"���", wcslen(L"���") * sizeof(WCHAR));

	RtlInitUnicodeString(&tUnicKeyName, L"����");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_DWORD, &dwValue, sizeof(dwValue));

	RtlInitUnicodeString(&tUnicKeyName, L"������");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_BINARY, chBuf, strlen(chBuf));

	ZwClose(handRootKey);

	return ulNTStatus;
}

/// <summary>
/// ɾ��ע����ֵ
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test03(VOID)
{
	HANDLE handRootKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//�½���ע������·��
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	UNICODE_STRING tUnicKeyName;

	InitializeObjectAttributes(&tObj_Attr, &tRootRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	ulNTStatus = ZwOpenKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr);
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("��򿪳ɹ�\n"));
	}
	else
	{
		KdPrint(("���ʧ��\n"));
		return ulNTStatus;
	}

	//ɾ����ֵ
	RtlInitUnicodeString(&tUnicKeyName, L"�ַ���");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	RtlInitUnicodeString(&tUnicKeyName, L"����");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	RtlInitUnicodeString(&tUnicKeyName, L"������");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	//ɾ����
	ZwDeleteKey(handRootKey);

	ZwClose(handRootKey);

	return ulNTStatus;
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("�������سɹ�\n"));

	Test01();
	Test02();
	Test03();

	return STATUS_SUCCESS;
}