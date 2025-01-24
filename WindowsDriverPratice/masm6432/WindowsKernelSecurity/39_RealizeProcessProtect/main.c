/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.24
描  述: 实现进程保护
备  注: 该驱动只能在win7 64位上正常加载
修改记录:

  1.  日期: 2025.01.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdm.h>

#include "ExportAPI.h"

#define PROCESS_TERMINATE 0x0001

HANDLE g_hOb = NULL;

//通过驱动签名检测
NTSTATUS BypassDriverCheck(PDRIVER_OBJECT DriverObject)
{
	if (DriverObject == NULL)
	{
		return STATUS_INVALID_PARAMETER;
	}

	PLDR_DATA_TABLE_ENTRY ptLdrData = (PLDR_DATA_TABLE_ENTRY)DriverObject->DriverSection;
	
	ptLdrData->Flags |= 0x20;		//内核会检测是否具有驱动签名，检测依据Flags是否为0x20，
	
	return STATUS_SUCCESS;
}

//进程操作回调函数
OB_PREOP_CALLBACK_STATUS Ob_Pre_Operation_CallBack(_In_ PVOID RegistrationContext,	_Inout_ POB_PRE_OPERATION_INFORMATION OperationInformation)
{
	PEPROCESS ptPEProcess = NULL;

	if (OperationInformation->ObjectType != *PsProcessType)
	{
		return OB_PREOP_SUCCESS;
	}

	ptPEProcess = OperationInformation->Object;
	if (_stricmp(PsGetProcessImageFileName(ptPEProcess), "calc.exe") != 0)
		return OB_PREOP_SUCCESS;

	if (OperationInformation->Operation == OB_OPERATION_HANDLE_CREATE || OperationInformation->Operation == OB_OPERATION_HANDLE_DUPLICATE)
	{
		if (OperationInformation->Parameters->CreateHandleInformation.DesiredAccess & PROCESS_TERMINATE)
			OperationInformation->Parameters->CreateHandleInformation.DesiredAccess &= ~PROCESS_TERMINATE;
	}

	return OB_PREOP_SUCCESS;
}

//是否使能进程保护
NTSTATUS EnableProtectProcess(BOOLEAN _IsEnable)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	if (_IsEnable)
	{
		OB_CALLBACK_REGISTRATION tOb_Cb = { 0 };
		OB_OPERATION_REGISTRATION tOb_Op = { 0 };

		tOb_Cb.Version = OB_FLT_REGISTRATION_VERSION;
		tOb_Cb.RegistrationContext = NULL;
		tOb_Cb.OperationRegistrationCount = 1;
		tOb_Cb.OperationRegistration = &tOb_Op;
		RtlInitUnicodeString(&tOb_Cb.Altitude, L"123456");

		tOb_Op.ObjectType = PsProcessType;
		tOb_Op.Operations = OB_OPERATION_HANDLE_CREATE | OB_OPERATION_HANDLE_DUPLICATE;
		tOb_Op.PreOperation = Ob_Pre_Operation_CallBack;
	
		lStatus = ObRegisterCallbacks(&tOb_Cb, &g_hOb);
		if (!NT_SUCCESS(lStatus))
		{
			KdPrint(("注册失败\n"));
			return lStatus;
		}
	}
	else
	{
		if (g_hOb)
		{
			ObUnRegisterCallbacks(g_hOb);
			g_hOb = NULL;
		}
	}

	return lStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	EnableProtectProcess(FALSE);
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	BypassDriverCheck(DriverObject);
	EnableProtectProcess(TRUE);

	KdPrint(("驱动加载成功\n"));

	return lStatus;
}

