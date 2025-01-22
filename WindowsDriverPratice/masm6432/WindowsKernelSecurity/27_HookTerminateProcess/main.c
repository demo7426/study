/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.21
��  ��: ö��ssdt(ϵͳ������������)��hook NtTerminateProcess����
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntddk.h>

#include "ExportAPI.h"

typedef struct _KSYSTEM_SERVICE_TABLE
{
	PULONG ServiceTableBase;							//��������ַ���ַ
	PULONG ServiceCounterTableBase;
	ULONG NumberOfService;								//�������ĸ���
	PULONG ParamTableBase;								//�������������ַ
}KSYSTEM_SERVICE_TABLE, * PKSYSTEM_SERVICE_TABLE;


typedef NTSTATUS(*NtTerminateProcess)(HANDLE ProcessHandle, NTSTATUS ExitStatus);

static NtTerminateProcess g_pOldNtTerminateProcess = NULL;

#ifdef _X86_

extern PKSYSTEM_SERVICE_TABLE KeServiceDescriptorTable;

/// <summary>
/// ö��32λ����ϵͳ�µ�ssdt
/// </summary>
/// <param name=""></param>
static VOID Enum_ssdt(VOID)
{
	for (ULONG i = 0; i < KeServiceDescriptorTable->NumberOfService; i++)
	{
		KdPrint(("%04u 0x%X\n", i, KeServiceDescriptorTable->ServiceTableBase[i]));
	}
}

#else

//��ȡSSDT��ַ
PKSYSTEM_SERVICE_TABLE MyGetKeServiceDescriptorTable()
{
	PKSYSTEM_SERVICE_TABLE ptServiceTable = NULL;
	LONG lOffset = 0;
	PCHAR pchBase = (PCHAR)__readmsr(0xc0000082);
	LONG lFuncOffset = 0;
	ULONG64 ullFuncAddr = 0;

	pchBase += 761;													//ͨ��windbg�������ó���ֵ
	lOffset = *(PULONG)(pchBase - 4);
	ptServiceTable = (PKSYSTEM_SERVICE_TABLE)(pchBase + lOffset);

	return ptServiceTable;
}

/// <summary>
/// ö��64λ����ϵͳ�µ�ssdt
/// </summary>
/// <param name=""></param>
static VOID Enum_ssdt(VOID)
{
	PKSYSTEM_SERVICE_TABLE ptServiceTable = NULL;
	LONG lOffset = 0;
	PCHAR pchBase = (PCHAR)__readmsr(0xc0000082);
	LONG lFuncOffset = 0;
	ULONG64 ullFuncAddr = 0;

	pchBase += 761;													//ͨ��windbg�������ó���ֵ
	lOffset = *(PULONG)(pchBase - 4);
	ptServiceTable = (PKSYSTEM_SERVICE_TABLE)(pchBase + lOffset);

	for (ULONG i = 0; i < ptServiceTable->NumberOfService; i++)
	{
		lFuncOffset = ptServiceTable->ServiceTableBase[i];
		ullFuncAddr = (ULONG64)(ptServiceTable->ServiceTableBase) + (lFuncOffset >> 4);

		KdPrint(("%04u 0x%llx\n", i, ullFuncAddr));
	}
}
	
#endif // _X86_

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

NTSTATUS MyNtTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PEPROCESS ptPEProcess = NULL;

	lNTStatus = ObReferenceObjectByHandle(ProcessHandle, PROCESS_ALL_ACCESS, *PsProcessType, KernelMode, &ptPEProcess, NULL);
	if (NT_SUCCESS(lNTStatus))
	{
		if (strcmp(PsGetProcessImageFileName(ptPEProcess), "calc.exe") == 0 && IoGetCurrentProcess() != ptPEProcess)		//��֤�����ǿ��������رս��̵�
		{
			ObDereferenceObject(ptPEProcess);
			return STATUS_ACCESS_DENIED;
		}
	}

	ObDereferenceObject(ptPEProcess);
	return g_pOldNtTerminateProcess(ProcessHandle, ExitStatus);
}

//����KeBugCheckEx�������޸�����������ת��ַ����ת��MyNtTerminateProcess����
static VOID HookBugCheckEx(VOID)
{
	KIRQL tKIrqL;

	CHAR chJmpCode[] = { "\x48\xB8\xFF\xFF\xFF\xFF\xFF\xFF\xFF\x00\xFF\xE0" };
	
	ULONG64 pullMyFuncAddr = (ULONG64)MyNtTerminateProcess;

	RtlCopyMemory(&(chJmpCode[2]), &pullMyFuncAddr, sizeof(ULONG64));

	tKIrqL = WPOff();

	RtlCopyMemory(KeBugCheckEx, chJmpCode, sizeof chJmpCode);

	WPOn(tKIrqL);
}

VOID HookTerminateProcess(VOID)
{
#ifdef _X86_
	KIRQL tKIrqL;

	g_pOldNtTerminateProcess = (NtTerminateProcess)KeServiceDescriptorTable->ServiceTableBase[370];

	tKIrqL = WPOff();

	(NtTerminateProcess)KeServiceDescriptorTable->ServiceTableBase[370] = MyNtTerminateProcess;

	WPOn(tKIrqL);
#else
	KIRQL tKIrqL;
	ULONG ulOffset = 0;
	PCHAR pchKeBugCheckEx = (PCHAR)KeBugCheckEx;
	PKSYSTEM_SERVICE_TABLE ptServiceTable = NULL;
	const SIZE_T unNtTerminateProcessIndex = 41;		//NtTerminateProcess���̵����

	HookBugCheckEx();

	ptServiceTable = MyGetKeServiceDescriptorTable();

	ulOffset = (ULONG)(pchKeBugCheckEx - (PCHAR)ptServiceTable->ServiceTableBase);
	ulOffset <<= 4;

	tKIrqL = WPOff();

	g_pOldNtTerminateProcess = (NtTerminateProcess)((PCHAR)ptServiceTable->ServiceTableBase + (ptServiceTable->ServiceTableBase[unNtTerminateProcessIndex] >> 4));

	ptServiceTable->ServiceTableBase[unNtTerminateProcessIndex] = ulOffset;

	WPOn(tKIrqL);
#endif // _X86_
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	HookTerminateProcess();

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


