/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.20
��  ��: ö������
��  ע: TODO:��һ��ͨ������ö�������ķ�ʽ����win7 32λ����ϵͳ����,�޷�����ʹ��
		�Ƽ�ʹ�õڶ��֣����ǵڶ��ֻ�ö�ٳ��û�̬�Ĳ�����Ϣ����Ҫʹ�ã���Ҫ�������
�޸ļ�¼:

  1.  ����: 2025.01.20
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

//ʹ��������Ϣö������
//TODO:ͨ������ö�������ķ�ʽ����win7 32λ����ϵͳ����,�޷�����ʹ��
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

	KdPrint(("������\t����ַ\t��С\t��������\t����·��\n"));
	
	while(ptListEntryCurrent->Flink != ptListEntryHeader)
	{
		ptLdrDataTableEntry = CONTAINING_RECORD(ptListEntryCurrent, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		//KdPrint(("%llx\n", &ptLdrDataTableEntry->SizeOfImage));

		KdPrint(("����������:%u, ������:%wZ ��ַ:0x%p ��С:%llu ��������:0x%p ����·��:%wZ\n",
			ptLdrDataTableEntry->BaseDllName.Length,
			&(ptLdrDataTableEntry->BaseDllName),
			ptLdrDataTableEntry->DllBase,
			ptLdrDataTableEntry->SizeOfImage,
			DriverObject,
			&(ptLdrDataTableEntry->FullDllName)));

		ptListEntryCurrent = ptListEntryCurrent->Flink;
	} 

}

//ʹ��windows�ṩ�Ľӿ�ö������
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
		KdPrint(("ģ����:%s,\t ��ַ: 0x%p, ģ���С%u Byte", ptSysModuleInfo->Module[i].ImageName, ptSysModuleInfo->Module[i].Base, ptSysModuleInfo->Module[i].Size));
	}

	ExFreePool(ptSysModuleInfo);
	ptSysModuleInfo = NULL;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	//EnumDriver_00(DriverObject);
	EnumDriver_01();

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}



