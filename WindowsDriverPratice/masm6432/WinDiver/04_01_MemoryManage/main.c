/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.14
��  ��: �ں��������ڴ����
��  ע: �����ڴ�--�ͷ��ڴ�
		ExAllocatePool--ExFreePool							//���ã��Ƕ� ExAllocatePoolWithTag--ExFreePoolWithTag �ļ��׷�װ
		ExAllocatePoolWithTag--ExFreePoolWithTag			//����
		ExAllocatePoolWithQuota--ExFreePool					//ʹ�ý���
		ExAllocatePoolWithQuotaTag--ExFreePoolWithTag		//ʹ�ý���	
�޸ļ�¼:

  1.  ����: 2024.11.14
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// �ڴ������ͷŲ���
/// </summary>
/// <param name="_Type">��������</param>
/// <returns></returns>
int MemTest(int _Type);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	
	DriverObject->DriverUnload = DriverUnload;

	MemTest(0);

	KdPrint(("�������سɹ�\n"));
	return lNTStatus;
}

int MemTest(int _Type)
{
	PCHAR pchBuf = NULL;
	switch (_Type)
	{
	case 0:				//�ڷ�ҳ�ڴ��Ϸ����ڴ�
	{
		pchBuf = (PCHAR)ExAllocatePool(PagedPool, 1024);				//PagedPool �����ҳ�ڴ�
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "����һ����ҳ�ڴ�洢������.");
		KdPrint(("%s\n", pchBuf));

		ExFreePool(pchBuf);
		pchBuf = NULL;
	}
	break;
	case 1:				//�ڷ�ҳ�ڴ��Ϸ����ڴ�
	{
		ULONG ulTag = 1234;
		pchBuf = (PCHAR)ExAllocatePoolWithTag(PagedPool, 1024, ulTag);				//PagedPool ����Ƿ�ҳ�ڴ�
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "����һ����ҳ�ڴ�洢������.");
		KdPrint(("%s\n", pchBuf));

		ExFreePoolWithTag(pchBuf, ulTag);
		pchBuf = NULL;
	}
	break;
	case 2:				//�ڷǷ�ҳ�ڴ��Ϸ����ڴ�
	{
		pchBuf = (PCHAR)ExAllocatePool(NonPagedPool, 1024);				//NonPagedPool ����Ƿ�ҳ�ڴ�
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "����һ���Ƿ�ҳ�ڴ�洢������.");
		KdPrint(("%s\n", pchBuf));

		ExFreePool(pchBuf);
		pchBuf = NULL;
	}
	break;
	case 3:				//�ڷǷ�ҳ�ڴ��Ϸ����ڴ�
	{
		ULONG ulTag = 1234;
		pchBuf = (PCHAR)ExAllocatePoolWithTag(NonPagedPool, 1024, ulTag);				//NonPagedPool ����Ƿ�ҳ�ڴ�
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "����һ���Ƿ�ҳ�ڴ�洢������.");
		KdPrint(("%s\n", pchBuf));

		ExFreePoolWithTag(pchBuf, ulTag);
		pchBuf = NULL;
	}
	break;
	default:
		break;
	}

	return STATUS_SUCCESS;
}

