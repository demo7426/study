/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.2     �½�����: 2025.01.23
��  ��: ����ָ��������
��  ע: ���Խ����64Ϊwin7�ܾ����� test.sys ������32λ��win7 KmdManager.exe��������test.sys ����һ���޷���������
�޸ļ�¼:

  1.  ����: 2025.01.23
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

  2.  ����: 2025.01.26
	  ����: Ǯ��
	  ����:
		  1) ������޷���32λ��win7 ������������������ص�bug������Լ����ͬ����������32λ����ϵͳ�£������Ǻ������÷�ʽ��ѭ��׼����Լ����
	  �汾:V0.0.2

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>
#include <stdio.h>
#include <ntimage.h>

#include "ExportAPI.h"

//�ر�д����
KIRQL WPOff(VOID)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();		//Ӳ�����ȼ���ߵ� IRQL = DISPATCH_LEVEL���Ӷ����ε�ǰ�������ϵ�Ч����� IRQL ���жϡ�
	ULONG_PTR ulCr0 = __readcr0();

	//д�����Ĵ�������
#ifdef _X86_
	ulCr0 &= ~0x00010000;
#else
	ulCr0 &= ~0x0000000000010000;
#endif // _X86_

	_disable();									//�����ж�
	__writecr0(ulCr0);

	return tKIrqL;
}

//����д����
VOID WPOn(KIRQL _KIrqL)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();
	ULONG_PTR ulCr0 = __readcr0();

	ulCr0 |= 0x10000;							//д�����Ĵ�����1

	_enable();									//�����ж�
	__writecr0(ulCr0);

	KeLowerIrql(_KIrqL);
}

VOID DenyLoadDriver(PCHAR _pImageBase)
{
#ifdef _AMD64_
	char ShellCode[6] = "\xB8\x22\x00\x00\xC0\xC3";
#else
	char ShellCode[8] = "\xB8\x22\x00\x00\xC0\xC2\x08\x00";		//32λ����Ҫ����һ��ջ��Ԫ���ֽ�������������32λ����ϵͳ�£������Ǻ������÷�ʽ��ѭ��׼����Լ��
																//mov eax, c0000022
																//ret 8
#endif // _x86_


	PIMAGE_DOS_HEADER ptDosHeader = (PIMAGE_DOS_HEADER)_pImageBase;
	PIMAGE_NT_HEADERS ptNtHeader = (PIMAGE_NT_HEADERS)(_pImageBase + ptDosHeader->e_lfanew);
	PCHAR pchAddrEntry = _pImageBase + ptNtHeader->OptionalHeader.AddressOfEntryPoint;
	KIRQL tKIrql;

	tKIrql = WPOff();

	RtlCopyMemory(pchAddrEntry, ShellCode, sizeof(ShellCode));

	WPOn(tKIrql);
}

VOID Load_Image_Notify_Routine(_In_opt_ PUNICODE_STRING FullImageName, _In_ HANDLE ProcessId,                // pid into which image is being mapped
	_In_ PIMAGE_INFO ImageInfo)
{
	if (ProcessId == 0)
	{
		PCHAR pchModuleName = (PCHAR)ExAllocatePool(PagedPool, FullImageName->Length + 1);
		if (pchModuleName == NULL)
		{
			KdPrint(("ExAllocatePool is err\n"));
			return;
		}

		sprintf(pchModuleName, "%wZ", FullImageName);
		if (strstr(_strlwr(pchModuleName), "test.sys") != NULL)			//��ֹtest.sys�����ļ���
		{
			DenyLoadDriver(ImageInfo->ImageBase);
		}

		ExFreePool(pchModuleName);
		pchModuleName = NULL;

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


