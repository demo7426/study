/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.25
��  ��: ��д���̿ռ������
��  ע:	����ʹ�ý��̹ҿ���ǿ��CR3�ķ�ʽ��д��������
		��δ���Ը�����
�޸ļ�¼:

  1.  ����: 2025.01.25
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>
#include <wdm.h>

PVOID GetPdt(PEPROCESS Process)
{
	if (sizeof(PVOID))
	{
		return *(PVOID*)((PCHAR)Process + 0x18);
	}
	else
	{
		return *(PVOID*)((PCHAR)Process + 0x28);
	}
}

//ʹ��ǿ��CR3��ʽ��д��������
VOID ReadProcessMemory(PEPROCESS Process, PVOID Address, ULONG Length, PVOID Buffer)
{
	PVOID pvPdt = GetPdt(Process);
	PVOID pvOldPdt = NULL;

	//����������Ӧ��pdt�л�Ϊ Process ��,ʹ�����ͽ������Ƕ�Ӧͬһ�������ַ
	_disable();
	pvOldPdt = (PVOID)__readcr3();
	__writecr3((UINT_PTR)pvPdt);
	_enable();

	if (MmIsAddressValid(Address))
	{
		RtlCopyMemory(Buffer, Address, Length);
	}

	_disable();
	__writecr3((UINT_PTR)pvOldPdt);
	_enable();
}

//ʹ�ý��̹ҿ��ķ�ʽ��д��������
VOID WriteProcessMemory(PEPROCESS Process, PVOID Address, ULONG Length, PVOID Buffer)
{
	KAPC_STATE tKApc_State = { 0 };

	KeStackAttachProcess(Process, &tKApc_State);

	if (MmIsAddressValid(Address))
	{
		RtlCopyMemory(Address, Buffer, Length);
	}

	KeUnstackDetachProcess(&tKApc_State);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	return lStatus;
}

