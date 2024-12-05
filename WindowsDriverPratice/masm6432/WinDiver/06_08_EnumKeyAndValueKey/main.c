/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.05
描  述: 枚举注册表项、值
备  注:	ZwEnumerateKey--枚举当前项
		ZwEnumerateValueKey--枚举当前值
修改记录:

  1.  日期: 2024.12.05
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// 枚举注册表项、值
/// </summary>
/// <param name=""></param>
VOID Test01(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE handRootKey; 
	UNICODE_STRING tUnicKeyPath = RTL_CONSTANT_STRING(L"\\Registry\\MACHINE\\SYSTEM\\CurrentControlSet\\Control");
	OBJECT_ATTRIBUTES tObj_Attr;

	ULONG ulResLen = 0;									//内核内部,实际所需要的字节长度
	const SIZE_T ulAllocateLen = 1024;					//待分配的数据长度
	PKEY_FULL_INFORMATION pKeyFullInfo = (PKEY_FULL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//项的所有相关信息
	if (!pKeyFullInfo)
	{
		KdPrint(("ExAllocatePool PKEY_FULL_INFORMATION is err.\n"));
		return;
	}

	PKEY_NODE_INFORMATION pKeyNodeInfo = (PKEY_NODE_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//项的这个节点相关信息
	if (!pKeyNodeInfo)
	{
		ExFreePool(pKeyFullInfo);
		pKeyFullInfo = NULL;

		KdPrint(("ExAllocatePool PKEY_NODE_INFORMATION is err.\n"));
		return;
	}

	PKEY_VALUE_FULL_INFORMATION pKeyValuFullInfo = (PKEY_VALUE_FULL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);					//值的节点相关信息
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

	//打开项
	lNTStatus = ZwOpenKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwOpenKey is err.\n"));
		return;
	}
	
	//查询项的所有信息
	lNTStatus = ZwQueryKey(handRootKey, KeyFullInformation, pKeyFullInfo, ulAllocateLen, &ulResLen);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ZwQueryKey is err.\n"));
		return;
	}

	KdPrint(("**************************************************子项**************************************************\n"));

	for (size_t i = 0; i < pKeyFullInfo->SubKeys; i++)		//遍历所有子项
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

	KdPrint(("**************************************************当前项值**************************************************\n"));

	for (size_t i = 0; i < pKeyFullInfo->Values; i++)		//遍历当前项值
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

	//释放资源
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));
	
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

