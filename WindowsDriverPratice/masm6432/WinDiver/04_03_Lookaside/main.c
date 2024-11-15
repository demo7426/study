/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.15
描  述: 在驱动中使用快查表(即内存池，减少内存碎片)
备  注: ExInitializePagedLookasideList--初始化分页快查表
		ExAllocateFromPagedLookasideList--从分页快查表申请空间
		ExFreeToPagedLookasideList--将内存控制权归还给分页快查表
		ExDeletePagedLookasideList--销毁分页快查表

		ExInitializeNPagedLookasideList--初始化非分页快查表
		ExAllocateFromNPagedLookasideList--从非分页快查表申请空间
		ExFreeToNPagedLookasideList--将内存控制权归还给非分页快查表
		ExDeleteNPagedLookasideList--销毁非分页快查表
修改记录:

  1.  日期: 2024.11.15
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

#define MAX_ARRAY_COUNT 100				//数组最大数量

typedef struct _MYDATA
{
	int Num;
}MYDATA, *PMYDATA;

/// <summary>
/// 分页快查表测试
/// </summary>
/// <param name=""></param>
VOID Page_Lookaside(VOID);

/// <summary>
/// 非分页快查表测试
/// </summary>
/// <param name=""></param>
VOID NPage_Lookaside(VOID);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("分页快查表测试\n"));
	Page_Lookaside();

	KdPrint(("非分页快查表测试\n"));
	NPage_Lookaside();

	KdPrint(("驱动加载成功\n"));
	return STATUS_SUCCESS;
}

VOID Page_Lookaside(VOID)
{
	PAGED_LOOKASIDE_LIST tPaged_Lookaside_List;
	ULONG ulTag = 'abcd';

	PMYDATA ptMyData[MAX_ARRAY_COUNT] = { NULL };

	//初始化快查表
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

	//初始化快查表
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