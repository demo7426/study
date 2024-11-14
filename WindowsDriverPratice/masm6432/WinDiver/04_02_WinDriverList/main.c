/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.14
��  ��: ��������ʹ������
��  ע: InitializeListHead--��ʼ������
		IsListEmpty--��������Ƿ�Ϊ��
		InsertHeadList--������ͷ����������
		InsertTailList--������β����������
		RemoveHeadList--�Ƴ�����ͷ�����ݣ��ҷ��ص�ǰ�ڵ�����
		RemoveTailList--�Ƴ�����β�����ݣ��ҷ��ص�ǰ�ڵ�����
�޸ļ�¼:

  1.  ����: 2024.11.14
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

typedef struct _DATA
{
	LIST_ENTRY tListEntry;
	int Num;
}DATA, *PDATA;

/// <summary>
/// �����ṩ���������
/// </summary>
/// <param name=""></param>
VOID ListTest01(VOID);

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DiverUnload;

	ListTest01();
	KdPrint(("�������سɹ�\n"));
	return lNTStatus;
}

VOID ListTest01(VOID)
{
	const size_t unCount = 10;					//����
	LIST_ENTRY tListEntry;

	InitializeListHead(&tListEntry);

	for (size_t i = 0; i < unCount; i++)		//�������д������
	{
		PDATA ptData = (PDATA)ExAllocatePool(PagedPool, sizeof(DATA));
		if(ptData == NULL)
		{
			KdPrint(("ExAllocatePool is err\n"));
			return;
		}

		ptData->Num = i;
		InsertTailList(&tListEntry, &(ptData->tListEntry));
	}

	while (!IsListEmpty(&tListEntry))
	{
		PLIST_ENTRY ptListEntry = NULL;
		PDATA ptData = NULL;

		ptListEntry = RemoveHeadList(&tListEntry);

		ptData = CONTAINING_RECORD(ptListEntry, DATA, tListEntry);			//���ݽṹ���ֶε�ƫ�ƣ�������ṹ���׵�ַ
		KdPrint(("%d\n", ptData->Num));
		ExFreePool(ptData);
	}
		


}