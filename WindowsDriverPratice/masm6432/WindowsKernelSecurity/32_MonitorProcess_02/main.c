/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.23
描  述: 进程监控
备  注: 在项目的链接器添加 /integritycheck ，PsSetCreateProcessNotifyRoutineEx函数要求
		最低受支持的客户端	从 Windows Vista SP1 和 Windows Server 2008 开始可用。
修改记录:

  1.  日期: 2025.01.23
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID Create_Process_Notify_Routine_Ex(_Inout_ PEPROCESS Process, _In_ HANDLE ProcessId, _Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	if (CreateInfo)
	{
		KdPrint(("创建:父进程ID: %d, 当前进程ID: %d, 进程名称: %wZ\n", (INT32)CreateInfo->ParentProcessId, (INT32)ProcessId, CreateInfo->ImageFileName));

		if (_stricmp(PsGetProcessImageFileName(Process), "calc.exe") == 0)		//阻止计算器的启动
		{
			CreateInfo->CreationStatus = STATUS_UNSUCCESSFUL;
		}

	}
	else
	{
		PEPROCESS ptPEProcess = NULL;

		PsLookupProcessByProcessId(ProcessId, &ptPEProcess);
		KdPrint(("销毁:父进程ID: %d, 当前进程ID: %d, 进程名称: %s\n", 
			(INT32)PsGetProcessInheritedFromUniqueProcessId(ptPEProcess),
			(INT32)ProcessId,
			PsGetProcessImageFileName(ptPEProcess)
		));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsSetCreateProcessNotifyRoutineEx(Create_Process_Notify_Routine_Ex, TRUE);

	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	lNTStatus = PsSetCreateProcessNotifyRoutineEx(Create_Process_Notify_Routine_Ex, FALSE);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsSetCreateProcessNotifyRoutineEx is err. 0x%x\n", lNTStatus));
		return lNTStatus;
	}

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


