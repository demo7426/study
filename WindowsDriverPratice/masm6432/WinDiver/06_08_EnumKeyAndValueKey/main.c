/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.05
��  ��: ö��ע����ֵ
��  ע:	ZwEnumerateKey--ö�ٵ�ǰ��
		ZwEnumerateValueKey--ö�ٵ�ǰֵ
�޸ļ�¼:

  1.  ����: 2024.12.05
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// ö��ע����ֵ
/// </summary>
/// <param name=""></param>
VOID Test01(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE handRootKey; 
	UNICODE_STRING tUnicKeyPath = RTL_CONSTANT_STRING(L"\\Registry\\MACHINE\\SYSTEM\\CurrentControlSet\\Control");
	OBJECT_ATTRIBUTES tObj_Attr;

	ULONG ulResLen = 0;									//�ں��ڲ�,ʵ������Ҫ���ֽڳ���
	const SIZE_T ulAllocateLen = 1024;					//����������ݳ���
	PKEY_FULL_INFORMATION pKeyFullInfo = (PKEY_FULL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//������������Ϣ
	if (!pKeyFullInfo)
	{
		KdPrint(("ExAllocatePool PKEY_FULL_INFORMATION is err.\n"));
		return;
	}

	PKEY_NODE_INFORMATION pKeyNodeInfo = (PKEY_NODE_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//�������ڵ������Ϣ
	if (!pKeyNodeInfo)
	{
		ExFreePool(pKeyFullInfo);
		pKeyFullInfo = NULL;

		KdPrint(("ExAllocatePool PKEY_NODE_INFORMATION is err.\n"));
		return;
	}

	PKEY_VALUE_FULL_INFORMATION pKeyValuFullInfo = (PKEY_VALUE_FULL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//ֵ�Ľڵ������Ϣ
	if (!pKeyValuFullInfo)
	{
		ExFreePool(pKeyFullInfo);
		pKeyFullInfo = NULL;

		ExFreePool(pKeyNodeInfo);
		pKeyNodeInfo = NULL;

		KdPrint(("ExAllocatePool PKEY_VALUE_FULL_INFORMATION is err.\n"));
		return;
	}

	InitializeObjectAttributes(&tObj_Attr, &tUnicKeyPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	//����
	lNTStatus = ZwOpenKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwOpenKey is err.\n"));
		return;
	}
	
	//��ѯ���������Ϣ
	lNTStatus = ZwQueryKey(handRootKey, KeyFullInformation, pKeyFullInfo, ulAllocateLen, &ulResLen);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwQueryKey is err.\n"));
		return;
	}

	KdPrint(("**************************************************����**************************************************\n"));

	for (size_t i = 0; i < pKeyFullInfo->SubKeys; i++)		//������������
	{
		RtlZeroMemory(pKeyNodeInfo, ulAllocateLen);

		lNTStatus = ZwEnumerateKey(handRootKey, i, KeyNodeInformation, pKeyNodeInfo, ulAllocateLen, &ulResLen);
		if (!NT_SUCCESS(lNTStatus))
		{
			KdPrint(("ZwEnumerateKey is err.\n"));
			break;
		}

		KdPrint(("%ls\n", pKeyNodeInfo->Name));
	}

	KdPrint(("**************************************************��ǰ��ֵ**************************************************\n"));

	for (size_t i = 0; i < pKeyFullInfo->Values; i++)		//������ǰ��ֵ
	{
		RtlZeroMemory(pKeyNodeInfo, ulAllocateLen);

		lNTStatus = ZwEnumerateValueKey(handRootKey, i, KeyValueFullInformation, pKeyValuFullInfo, ulAllocateLen, &ulResLen);
		if (!NT_SUCCESS(lNTStatus))
		{
			KdPrint(("ZwEnumerateValueKey is err.\n"));
			break;
		}

		switch (pKeyValuFullInfo->Type)
		{
		case REG_DWORD:
			KdPrint(("%ls: %u\n", pKeyValuFullInfo->Name, *(PULONG)((PCHAR)pKeyValuFullInfo->Name + pKeyValuFullInfo->DataOffset)));
			break;
		case REG_SZ:
		case REG_EXPAND_SZ:
		case REG_MULTI_SZ:
		case REG_BINARY:
			KdPrint(("%ls: %ls\n", pKeyValuFullInfo->Name, (PWCHAR)((PCHAR)pKeyValuFullInfo->Name + pKeyValuFullInfo->DataOffset)));
			break;
		default:
			break;
		}
	}

	//�ͷ���Դ
	ZwClose(handRootKey);
	if (pKeyFullInfo)
	{
		ExFreePool(pKeyFullInfo);
		pKeyFullInfo = NULL;
	}

	if (pKeyNodeInfo)
	{
		ExFreePool(pKeyNodeInfo);
		pKeyNodeInfo = NULL;
	}

	if (pKeyValuFullInfo)
	{
		ExFreePool(pKeyValuFullInfo);
		pKeyValuFullInfo = NULL;
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));
	
	__try
	{
		Test01();
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("Test01 is err: %u\n", GetExceptionCode()));
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	return STATUS_SUCCESS;
}

