/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.14
描  述: 内核驱动的内存管理
备  注: 申请内存--释放内存
		ExAllocatePool--ExFreePool							//常用，是对 ExAllocatePoolWithTag--ExFreePoolWithTag 的简易分装
		ExAllocatePoolWithTag--ExFreePoolWithTag			//常用
		ExAllocatePoolWithQuota--ExFreePool					//使用较少
		ExAllocatePoolWithQuotaTag--ExFreePoolWithTag		//使用较少	
修改记录:

  1.  日期: 2024.11.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 内存申请释放测试
/// </summary>
/// <param name="_Type">测试类型</param>
/// <returns></returns>
int MemTest(int _Type);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	
	DriverObject->DriverUnload = DriverUnload;

	MemTest(0);

	KdPrint(("驱动加载成功\n"));
	return lNTStatus;
}

int MemTest(int _Type)
{
	PCHAR pchBuf = NULL;
	switch (_Type)
	{
	case 0:				//在分页内存上分配内存
	{
		pchBuf = (PCHAR)ExAllocatePool(PagedPool, 1024);				//PagedPool 代表分页内存
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "这是一个分页内存存储的数据.");
		KdPrint(("%s\n", pchBuf));

		ExFreePool(pchBuf);
		pchBuf = NULL;
	}
	break;
	case 1:				//在分页内存上分配内存
	{
		ULONG ulTag = 1234;
		pchBuf = (PCHAR)ExAllocatePoolWithTag(PagedPool, 1024, ulTag);				//PagedPool 代表非分页内存
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "这是一个分页内存存储的数据.");
		KdPrint(("%s\n", pchBuf));

		ExFreePoolWithTag(pchBuf, ulTag);
		pchBuf = NULL;
	}
	break;
	case 2:				//在非分页内存上分配内存
	{
		pchBuf = (PCHAR)ExAllocatePool(NonPagedPool, 1024);				//NonPagedPool 代表非分页内存
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "这是一个非分页内存存储的数据.");
		KdPrint(("%s\n", pchBuf));

		ExFreePool(pchBuf);
		pchBuf = NULL;
	}
	break;
	case 3:				//在非分页内存上分配内存
	{
		ULONG ulTag = 1234;
		pchBuf = (PCHAR)ExAllocatePoolWithTag(NonPagedPool, 1024, ulTag);				//NonPagedPool 代表非分页内存
		if (!pchBuf)
		{
			KdPrint(("ExAllocatePool is err.\n"));
			return STATUS_INSUFFICIENT_RESOURCES;
		}

		strcpy(pchBuf, "这是一个非分页内存存储的数据.");
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

