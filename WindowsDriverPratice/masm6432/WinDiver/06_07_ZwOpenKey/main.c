/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.04
描  述: 新建、查询注册表值
备  注:
修改记录:

  1.  日期: 2024.12.04
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/


#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

/// <summary>
/// 创建注册表目录
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test01(VOID)
{
	HANDLE handRootKey;
	HANDLE handSubKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//新建的注册表绝对路径
	UNICODE_STRING tSubRegPath = RTL_CONSTANT_STRING(L"MySubKey");										//子项相对路径
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	InitializeObjectAttributes(&tObj_Attr, &tRootRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	ulNTStatus = ZwCreateKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr, 0, NULL, REG_OPTION_NON_VOLATILE, &ulRet);
	if (NT_SUCCESS(ulNTStatus))
	{
		if (ulRet == REG_CREATED_NEW_KEY)
			KdPrint(("项不存在，创建成功\n"));
		else if (ulRet == REG_OPENED_EXISTING_KEY)
			KdPrint(("项存在，打开成功\n"));
	}
	else
	{
		KdPrint(("项创建\\打开失败\n"));
	}

	//创建/打开子项
	InitializeObjectAttributes(&tObj_Attr, &tSubRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, handRootKey, NULL);

	ulNTStatus = ZwCreateKey(&handSubKey, KEY_ALL_ACCESS, &tObj_Attr, 0, NULL, REG_OPTION_NON_VOLATILE, &ulRet);
	if (NT_SUCCESS(ulNTStatus))
	{
		if (ulRet == REG_CREATED_NEW_KEY)
			KdPrint(("子项不存在，创建成功\n"));
		else if (ulRet == REG_OPENED_EXISTING_KEY)
			KdPrint(("子项存在，打开成功\n"));
	}
	else
	{
		KdPrint(("子项创建\\打开失败\n"));
	}

	ZwClose(handSubKey);
	ZwClose(handRootKey);

	return ulNTStatus;
}

/// <summary>
/// 新建、查询注册表值
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test02(VOID)
{
	HANDLE handRootKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//新建的注册表绝对路径
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	UNICODE_STRING tUnicKeyName;
	DWORD32 dwValue = 10;
	CHAR chBuf[] = "Hello world";

	ULONG ulLen;
	const SIZE_T ulAllocateLen = 1024;				//分配内存空间大小
	PKEY_VALUE_PARTIAL_INFORMATION ptKeyValue_PartialInfo = (PKEY_VALUE_PARTIAL_INFORMATION)ExAllocatePool(PagedPool, ulAllocateLen);
	if (!ptKeyValue_PartialInfo)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return STATUS_INSUFFICIENT_POWER;
	}

	InitializeObjectAttributes(&tObj_Attr, &tRootRegPath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	ulNTStatus = ZwOpenKey(&handRootKey, KEY_ALL_ACCESS, &tObj_Attr);
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("项打开成功\n"));
	}
	else
	{
		KdPrint(("项打开失败\n"));
		return ulNTStatus;
	}

	//新增键值
	RtlInitUnicodeString(&tUnicKeyName, L"字符串");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_SZ, L"你好", wcslen(L"你好") * sizeof(WCHAR));

	RtlInitUnicodeString(&tUnicKeyName, L"整数");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_DWORD, &dwValue, sizeof(dwValue));

	RtlInitUnicodeString(&tUnicKeyName, L"二进制");
	ZwSetValueKey(handRootKey, &tUnicKeyName, 0, REG_BINARY, chBuf, strlen(chBuf));

	//读取键值
	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"字符串");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_SZ)
	{
		KdPrint(("%ls\n", ptKeyValue_PartialInfo->Data));
	}

	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"整数");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_DWORD)
	{
		KdPrint(("%u\n", *(PDWORD32)ptKeyValue_PartialInfo->Data));
	}

	RtlZeroMemory(ptKeyValue_PartialInfo, ulAllocateLen);
	RtlInitUnicodeString(&tUnicKeyName, L"二进制");
	ZwQueryValueKey(handRootKey, &tUnicKeyName, KeyValuePartialInformation, ptKeyValue_PartialInfo, ulAllocateLen, &ulLen);
	if (ptKeyValue_PartialInfo->Type == REG_BINARY)
	{
		KdPrint(("%s\n", ptKeyValue_PartialInfo->Data));
	}

	//防止内存泄露
	ExFreePool(ptKeyValue_PartialInfo);
	ptKeyValue_PartialInfo = NULL;

	ZwClose(handRootKey);

	return ulNTStatus;
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("驱动加载成功\n"));

	Test01();
	Test02();

	return STATUS_SUCCESS;
}


