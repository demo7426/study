/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.21
��  ��: ͨ���滻��ǲ������ʵ�ּ��̹�������
��  ע: 
�޸ļ�¼:

  1.  ����: 2024.02.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"
#include "Dispatch.h"


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return;
	}

#ifdef _X86_
	InterlockedExchange((volatile LONG32*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG32)g_pfOld_Dispatch_Read);
#else
	InterlockedExchange64((volatile LONG64*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG64)Old_Dispatch_Read);
#endif // _WIN32_

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;

	DriverObject->DriverUnload = DriverUnload;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return lNTStatus;
	}

	//�滻��ǲ����
#ifdef _X86_
	g_pfOld_Dispatch_Read = (Dispatch_Read_FuncType)InterlockedExchange((volatile LONG32*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG32)Dispatch_Read);
#else
	Old_Dispatch_Read = (Dispatch_Read_FuncType)InterlockedExchange64((volatile LONG64*)&ptDriverObj->MajorFunction[IRP_MJ_READ], (LONG64)Dispatch_Read);
#endif // _WIN32_

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


