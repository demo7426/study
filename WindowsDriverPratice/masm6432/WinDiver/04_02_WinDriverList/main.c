/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: 在驱动中使用链表
备  注: InitializeListHead--初始化链表
		IsListEmpty--检查链表是否为空
		InsertHeadList--向链表头部插入数据
		InsertTailList--向链表尾部插入数据
		RemoveHeadList--移除链表头部数据，且返回当前节点数据
		RemoveTailList--移除链表尾部数据，且返回当前节点数据
修改记录:

  1.  日期: 2024.11.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

typedef struct _DATA
{
	LIST_ENTRY tListEntry;
	int Num;
}DATA, *PDATA;

/// <summary>
/// 驱动提供的链表测试
/// </summary>
/// <param name=""></param>
VOID ListTest01(VOID);

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DiverUnload;

	ListTest01();
	KdPrint(("驱动加载成功\n"));
	return lNTStatus;
}

VOID ListTest01(VOID)
{
	const size_t unCount = 10;					//个数
	LIST_ENTRY tListEntry;

	InitializeListHead(&tListEntry);

	for (size_t i = 0; i < unCount; i++)		//向链表中存放数据
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

		ptData = CONTAINING_RECORD(ptListEntry, DATA, tListEntry);			//根据结构体字段的偏移，计算出结构体首地址
		KdPrint(("%d\n", ptData->Num));
		ExFreePool(ptData);
	}
		


}