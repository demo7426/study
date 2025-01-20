/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.20
描  述: 枚举驱动
备  注: TODO:第一种通过链表枚举驱动的方式导致win7 32位操作系统崩溃,无法正常使用
		推荐使用第二种，但是第二种会枚举出用户态的部分信息；如要使用，需要代码过滤
修改记录:

  1.  日期: 2025.01.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

//使用链表信息枚举驱动
//TODO:通过链表枚举驱动的方式导致win7 32位操作系统崩溃,无法正常使用
VOID EnumDriver_00(IN PDRIVER_OBJECT DriverObject)
{
	PLDR_DATA_TABLE_ENTRY ptLdrDataTableEntry = (PLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection;
	if (!ptLdrDataTableEntry)
	{
		KdPrint(("ptLdrDataTableEntry is empty.\n"));
		return;
	}

	PLIST_ENTRY ptListEntryHeader = &ptLdrDataTableEntry->InLoadOrderLinks;
	if (!ptLdrDataTableEntry)
	{
		KdPrint(("ptListEntryHeader is empty.\n"));
		return;
	}

	PLIST_ENTRY ptListEntryCurrent = ptListEntryHeader;

	KdPrint(("驱动名\t基地址\t大小\t驱动对象\t驱动路径\n"));
	
	while(ptListEntryCurrent->Flink != ptListEntryHeader)
	{
		ptLdrDataTableEntry = CONTAINING_RECORD(ptListEntryCurrent, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		//KdPrint(("%llx\n", &ptLdrDataTableEntry->SizeOfImage));

		KdPrint(("驱动名长度:%u, 驱动名:%wZ 地址:0x%p 大小:%llu 驱动对象:0x%p 驱动路径:%wZ\n",
			ptLdrDataTableEntry->BaseDllName.Length,
			&(ptLdrDataTableEntry->BaseDllName),
			ptLdrDataTableEntry->DllBase,
			ptLdrDataTableEntry->SizeOfImage,
			DriverObject,
			&(ptLdrDataTableEntry->FullDllName)));

		ptListEntryCurrent = ptListEntryCurrent->Flink;
	} 

}

//使用windows提供的接口枚举驱动
VOID EnumDriver_01()
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	const SIZE_T unMemSize = 1024 * 1024;
	ULONG ulRet = 0;
	PSYSTEM_MODULE_INFORMATION ptSysModuleInfo = (PSYSTEM_MODULE_INFORMATION)ExAllocatePool(PagedPool, unMemSize);
	if (!ptSysModuleInfo)
	{
		KdPrint(("ExAllocatePool is err.\n"));
		return;
	}

	lNTStatus = ZwQuerySystemInformation(SystemModuleInformation, ptSysModuleInfo, unMemSize, &ulRet);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwQuerySystemInformation is err\n"));

		ExFreePool(ptSysModuleInfo);
		ptSysModuleInfo = NULL;
		return;
	}

	for (size_t i = 0; i < ptSysModuleInfo->Count; i++)
	{
		KdPrint(("模块名:%s,\t 基址: 0x%p, 模块大小%u Byte", ptSysModuleInfo->Module[i].ImageName, ptSysModuleInfo->Module[i].Base, ptSysModuleInfo->Module[i].Size));
	}

	ExFreePool(ptSysModuleInfo);
	ptSysModuleInfo = NULL;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	//EnumDriver_00(DriverObject);
	EnumDriver_01();

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}



