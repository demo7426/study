/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.15
��  ��: ��������ʹ�ÿ���(���ڴ�أ������ڴ���Ƭ)
��  ע: ExInitializePagedLookasideList--��ʼ����ҳ����
		ExAllocateFromPagedLookasideList--�ӷ�ҳ��������ռ�
		ExFreeToPagedLookasideList--���ڴ����Ȩ�黹����ҳ����
		ExDeletePagedLookasideList--���ٷ�ҳ����

		ExInitializeNPagedLookasideList--��ʼ���Ƿ�ҳ����
		ExAllocateFromNPagedLookasideList--�ӷǷ�ҳ��������ռ�
		ExFreeToNPagedLookasideList--���ڴ����Ȩ�黹���Ƿ�ҳ����
		ExDeleteNPagedLookasideList--���ٷǷ�ҳ����
�޸ļ�¼:

  1.  ����: 2024.11.15
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

#define MAX_ARRAY_COUNT 100				//�����������

typedef struct _MYDATA
{
	int Num;
}MYDATA, *PMYDATA;

/// <summary>
/// ��ҳ�������
/// </summary>
/// <param name=""></param>
VOID Page_Lookaside(VOID);

/// <summary>
/// �Ƿ�ҳ�������
/// </summary>
/// <param name=""></param>
VOID NPage_Lookaside(VOID);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("��ҳ�������\n"));
	Page_Lookaside();

	KdPrint(("�Ƿ�ҳ�������\n"));
	NPage_Lookaside();

	KdPrint(("�������سɹ�\n"));
	return STATUS_SUCCESS;
}

VOID Page_Lookaside(VOID)
{
	PAGED_LOOKASIDE_LIST tPaged_Lookaside_List;
	ULONG ulTag = 'abcd';

	PMYDATA ptMyData[MAX_ARRAY_COUNT] = { NULL };

	//��ʼ������
	ExInitializePagedLookasideList(&tPaged_Lookaside_List, NULL, NULL, 0, sizeof(MYDATA), ulTag, 0);

	for (size_t i = 0; i < MAX_ARRAY_COUNT; i++)
	{
		ptMyData[i] = ExAllocateFromPagedLookasideList(&tPaged_Lookaside_List);
		if (ptMyData[i] == NULL)
		{
			KdPrint(("ExAllocateFromPagedLookasideList is err\n"));
			return;
		}

		ptMyData[i]->Num = i;
		KdPrint(("%d\n", ptMyData[i]->Num));
	}

	for (size_t i = 0; i < MAX_ARRAY_COUNT; i++)
		ExFreeToPagedLookasideList(&tPaged_Lookaside_List, ptMyData[i]);

	ExDeletePagedLookasideList(&tPaged_Lookaside_List);
}

VOID NPage_Lookaside(VOID)
{
	PAGED_LOOKASIDE_LIST tPaged_Lookaside_List;
	ULONG ulTag = 'abcd';

	PMYDATA ptMyData[MAX_ARRAY_COUNT] = { NULL };

	//��ʼ������
	ExInitializeNPagedLookasideList(&tPaged_Lookaside_List, NULL, NULL, 0, sizeof(MYDATA), ulTag, 0);

	for (size_t i = 0; i < MAX_ARRAY_COUNT; i++)
	{
		ptMyData[i] = ExAllocateFromNPagedLookasideList(&tPaged_Lookaside_List);
		if (ptMyData[i] == NULL)
		{
			KdPrint(("ExAllocateFromNPagedLookasideList is err\n"));
			return;
		}

		ptMyData[i]->Num = i;
		KdPrint(("%d\n", ptMyData[i]->Num));
	}

	for (size_t i = 0; i < MAX_ARRAY_COUNT; i++)
		ExFreeToNPagedLookasideList(&tPaged_Lookaside_List, ptMyData[i]);

	ExDeleteNPagedLookasideList(&tPaged_Lookaside_List);
}