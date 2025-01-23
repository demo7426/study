/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.23
��  ��: ���̼��
��  ע: ����Ŀ����������� /integritycheck ��PsSetCreateProcessNotifyRoutineEx����Ҫ��
		�����֧�ֵĿͻ���	�� Windows Vista SP1 �� Windows Server 2008 ��ʼ���á�
�޸ļ�¼:

  1.  ����: 2025.01.23
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

VOID Create_Process_Notify_Routine_Ex(_Inout_ PEPROCESS Process, _In_ HANDLE ProcessId, _Inout_opt_ PPS_CREATE_NOTIFY_INFO CreateInfo)
{
	if (CreateInfo)
	{
		KdPrint(("����:������ID: %d, ��ǰ����ID: %d, ��������: %wZ\n", (INT32)CreateInfo->ParentProcessId, (INT32)ProcessId, CreateInfo->ImageFileName));

		if (_stricmp(PsGetProcessImageFileName(Process), "calc.exe") == 0)		//��ֹ������������
		{
			CreateInfo->CreationStatus = STATUS_UNSUCCESSFUL;
		}

	}
	else
	{
		PEPROCESS ptPEProcess = NULL;

		PsLookupProcessByProcessId(ProcessId, &ptPEProcess);
		KdPrint(("����:������ID: %d, ��ǰ����ID: %d, ��������: %s\n", 
			(INT32)PsGetProcessInheritedFromUniqueProcessId(ptPEProcess),
			(INT32)ProcessId,
			PsGetProcessImageFileName(ptPEProcess)
		));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsSetCreateProcessNotifyRoutineEx(Create_Process_Notify_Routine_Ex, TRUE);

	KdPrint(("����ж�سɹ�\n"));
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

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


