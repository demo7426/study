/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.23
��  ��: Dllģ����
��  ע: 
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

VOID Load_Image_Notify_Routine(_In_opt_ PUNICODE_STRING FullImageName, _In_ HANDLE ProcessId,                // pid into which image is being mapped
	_In_ PIMAGE_INFO ImageInfo)
{
	if (ProcessId == 0)
	{
		KdPrint(("%wZ\n", FullImageName));
	}
	else
	{
		PEPROCESS ptPEProcess = NULL;

		PsLookupProcessByProcessId(ProcessId, &ptPEProcess);
		KdPrint(("%s, %wZ\n", PsGetProcessImageFileName(ptPEProcess), FullImageName));
	}
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PsRemoveLoadImageNotifyRoutine(Load_Image_Notify_Routine);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	lNTStatus = PsSetLoadImageNotifyRoutine(Load_Image_Notify_Routine);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsSetLoadImageNotifyRoutine is err. 0x%x\n", lNTStatus));
		return lNTStatus;
	}

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


