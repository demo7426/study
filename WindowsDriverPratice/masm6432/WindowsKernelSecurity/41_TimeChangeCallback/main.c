/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.25
描  述: 时间变更回调
备  注: 
修改记录:

  1.  日期: 2025.01.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdm.h>

VOID TimeChangeCallBack_Func(
	_In_opt_ PVOID CallbackContext,
	_In_opt_ PVOID Argument1,
	_In_opt_ PVOID Argument2
)
{
	KdPrint(("时间被修改.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;
	UNICODE_STRING tTimeChangeCbName = RTL_CONSTANT_STRING(L"\\Callback\\SetSystemTime");
	OBJECT_ATTRIBUTES tObjAttr = { 0 };
	PCALLBACK_OBJECT ptCbObj = NULL;

	DriverObject->DriverUnload = DriverUnload;

	InitializeObjectAttributes(&tObjAttr, &tTimeChangeCbName, OBJ_CASE_INSENSITIVE, NULL, NULL);
	lStatus = ExCreateCallback(&ptCbObj, &tObjAttr, TRUE, FALSE);
	if (!NT_SUCCESS(lStatus))
	{
		KdPrint(("ExCreateCallback is err.\n"));
		return lStatus;
	}

	ExRegisterCallback(ptCbObj, TimeChangeCallBack_Func, NULL);

	ObDereferenceObject(ptCbObj);
	ptCbObj = NULL;

	KdPrint(("驱动加载成功\n"));

	return lStatus;
}

