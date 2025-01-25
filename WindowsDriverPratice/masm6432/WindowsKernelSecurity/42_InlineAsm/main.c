/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.25
��  ��: ����32λ��࣬64λ�����Ҫ��װ�µ�vs ��࿪������
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.25
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntifs.h>
#include <ntddk.h>
#include <wdm.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	__asm
	{
		mov al, 0feh
		out 64h, al
	}

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	return lStatus;
}

