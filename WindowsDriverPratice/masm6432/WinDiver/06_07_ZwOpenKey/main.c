/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.04
��  ��: �½�����ѯע���ֵ
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

	ULONG ulLen;
	const SIZE_T ulAllocateLen = 1024;				//�����ڴ�ռ��С
	PKEY_VALUE_PARTIAL_INFORMATION ptKeyValue_PartialInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);
	if (!ptKeyValue_PartialInfo)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return STATUS_INSUFFICIENT_POWER;
	}

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

	//��ȡ��ֵ
	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"�ַ���");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_SZ)
	{
		KdPrint(("%ls\n", ptKeyValue_PartialInfo->Data));
	}

	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"����");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_DWORD)
	{
		KdPrint(("%u\n", *(PDWORD32)ptKeyValue_PartialInfo->Data));
	}

	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"������");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_BINARY)
	{
		KdPrint(("%s\n", ptKeyValue_PartialInfo->Data));
	}

	//��ֹ�ڴ�й¶
	ExFreePool(ptKeyValue_PartialInfo);
	ptKeyValue_PartialInfo = NULL;

	ZwClose(handRootKey);

	return ulNTStatus;
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("�������سɹ�\n"));

	Test01();
	Test02();

	return STATUS_SUCCESS;
}


