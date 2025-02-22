/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.22
��  ��: ͨ���滻����λ����룬ʵ�ּ��̹�������
��  ע: ��֧��x86�ܹ���64λ����ϵͳ
�޸ļ�¼:

  1.  ����: 2024.02.22
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"
#include "Dispatch.h"

extern MYCODE g_tNewMyCode;
extern MYCODE g_tOldMyCode;

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;
	KIRQL tKIrqL = { 0 };

	tKIrqL = WPOff();
	RtlCopyMemory(g_pfOld_Dispatch_Read, &g_tOldMyCode, sizeof(MYCODE));
	WPOn(tKIrqL);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDRIVER_OBJECT ptDriverObj = NULL;
	KIRQL tKIrqL = { 0 };

	DriverObject->DriverUnload = DriverUnload;

	ptDriverObj = GetDriverObjectByName(L"\\Driver\\kbdclass");
	if (!ptDriverObj)
	{
		KdPrint(("GetDriverObjectByName is err.\n"));
		return lNTStatus;
	}
	
	g_pfOld_Dispatch_Read = ptDriverObj->MajorFunction[IRP_MJ_READ];

	g_tNewMyCode.TargetAddr = Dispatch_Read;

	//�ں�ֱ���޸�Irp��ǲ�����Ĵ����
	tKIrqL = WPOff();
	RtlCopyMemory(&g_tOldMyCode, g_pfOld_Dispatch_Read, sizeof(MYCODE));
	RtlCopyMemory(g_pfOld_Dispatch_Read, &g_tNewMyCode, sizeof(MYCODE));
	WPOn(tKIrqL);

	ObfDereferenceObject(ptDriverObj);
	ptDriverObj = NULL;

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


