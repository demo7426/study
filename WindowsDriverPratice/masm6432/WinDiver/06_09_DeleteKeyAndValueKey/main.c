/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.05
描  述: 删除注册表项、值
备  注:	ZwDeleteKey--删除项
		ZwDeleteValueKey--删除值

		RtlCreateRegistryKey--创建\打开注册表项
		RtlCheckRegistryKey--检测注册表项是否已经存在
		RtlWriteRegistryValue--新建注册表值
		RtlDeleteRegistryValue--删除注册表值
		RtlQueryRegistryValues--查询注册表值
修改记录:

  1.  日期: 2024.12.05
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

	ZwClose(handRootKey);

	return ulNTStatus;
}

/// <summary>
/// 删除注册表项、值
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS Test03(VOID)
{
	HANDLE handRootKey;
	OBJECT_ATTRIBUTES tObj_Attr;
	UNICODE_STRING tRootRegPath = RTL_CONSTANT_STRING(L"\\Registry\\Machine\\SOFTWARE\\MyKey");			//新建的注册表绝对路径
	ULONG ulRet;
	NTSTATUS ulNTStatus = STATUS_SUCCESS;

	UNICODE_STRING tUnicKeyName;

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

	//删除键值
	RtlInitUnicodeString(&tUnicKeyName, L"字符串");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	RtlInitUnicodeString(&tUnicKeyName, L"整数");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	RtlInitUnicodeString(&tUnicKeyName, L"二进制");
	ZwDeleteValueKey(handRootKey, &tUnicKeyName);

	//删除项
	ZwDeleteKey(handRootKey);

	ZwClose(handRootKey);

	return ulNTStatus;
}

/// <summary>
/// 使用更上层的API对注册表项、值进行增删改查
/// </summary>
/// <param name=""></param>
VOID Test04(VOID)
{
	NTSTATUS ulNTStatus = STATUS_SUCCESS;
	WCHAR* pwchName = L"MyService";

	ulNTStatus = RtlCreateRegistryKey(RTL_REGISTRY_SERVICES, pwchName);
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("Rtl创建子项成功.\n"));
	}

	ulNTStatus = RtlCheckRegistryKey(RTL_REGISTRY_SERVICES, pwchName);
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("注册表存在.\n"));
	}

	ulNTStatus = RtlWriteRegistryValue(RTL_REGISTRY_SERVICES, pwchName, L"字符串", REG_SZ, L"你好世界", wcslen(L"你好世界"));
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("写入成功.\n"));
	}

	ulNTStatus = RtlDeleteRegistryValue(RTL_REGISTRY_SERVICES, pwchName, L"字符串");
	if (NT_SUCCESS(ulNTStatus))
	{
		KdPrint(("删除成功.\n"));
	}
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("驱动加载成功\n"));

#if 0			//使用Zw接口
	Test01();
	Test02();
	Test03();
#else			//使用Rtl接口
	Test04();
#endif // 0

	
	return STATUS_SUCCESS;
}