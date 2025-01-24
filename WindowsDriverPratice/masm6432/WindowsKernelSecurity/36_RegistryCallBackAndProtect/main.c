/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.24
描  述: 注册表回调与保护
备  注: 
修改记录:

  1.  日期: 2025.01.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>

LARGE_INTEGER g_tCookie;
WCHAR g_wchKeyPath[1024] = { 0 };			//当前注册表的路径
WCHAR g_wchKeyName[260] = { 0 };			//当前驱动的项名称


//注册表操作回调函数
NTSTATUS Register_CallBack(_In_ PVOID CallbackContext, _In_opt_ PVOID Argument1, _In_opt_ PVOID Argument2)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	switch ((REG_NOTIFY_CLASS)Argument1)
	{
	case RegNtPreOpenKey:
	case RegNtPreOpenKeyEx:
	case RegNtPreCreateKey:
	case RegNtPreCreateKeyEx:
	{
		PREG_CREATE_KEY_INFORMATION ptReg_KeyInfo = (PREG_CREATE_KEY_INFORMATION)Argument2;
		if (!ptReg_KeyInfo)
		{
			lStatus = STATUS_INVALID_PARAMETER;
			return lStatus;
		}

		RtlCopyMemory(g_wchKeyPath, ptReg_KeyInfo->CompleteName->Buffer, ptReg_KeyInfo->CompleteName->Length);
		if (wcsstr(_wcslwr(g_wchKeyPath), _wcslwr(g_wchKeyName)) != NULL)
		{
			lStatus = STATUS_STACK_OVERFLOW;
		}
	}
	default:
		break;
	}

	return lStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	CmUnRegisterCallback(g_tCookie);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	RtlCopyMemory(g_wchKeyName, DriverObject->DriverExtension->ServiceKeyName.Buffer, DriverObject->DriverExtension->ServiceKeyName.Length);

	CmRegisterCallback(Register_CallBack, NULL, &g_tCookie);

	KdPrint(("驱动加载成功\n"));

	return lStatus;
}

