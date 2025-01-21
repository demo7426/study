/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.21
��  ��: ö��ssdt(ϵͳ������������)
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

typedef struct _KSYSTEM_SERVICE_TABLE
{
	PULONG ServiceTableBase;							//��������ַ���ַ
	PULONG ServiceCounterTableBase;
	ULONG NumberOfService;								//�������ĸ���
	PULONG ParamTableBase;								//�������������ַ
}KSYSTEM_SERVICE_TABLE, * PKSYSTEM_SERVICE_TABLE;

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
ULONGLONG MyGetKeServiceDescriptorTable()
{
	PUCHAR StartSearchAddress = (PUCHAR)__readmsr(0xC0000082);
	PUCHAR EndSearchAddress = StartSearchAddress + 0x500;
	PUCHAR i = NULL;
	UCHAR b1 = 0, b2 = 0, b3 = 0;
	ULONG templong = 0;
	ULONGLONG addr = 0;

	for (i = StartSearchAddress; i < EndSearchAddress; i++)
	{
		if (MmIsAddressValid(i) && MmIsAddressValid(i + 1) && MmIsAddressValid(i + 1))
		{
			b1 = *i;
			b2 = *(i + 1);
			b3 = *(i + 2);
			if (b1 == 0x4c && b2 == 0x8d && b3 == 0x15) //4c8d15
			{
				memcpy(&templong, i + 3, 4);
				addr = (ULONGLONG)templong + (ULONGLONG)i + 7;
				return addr;
			}
		}
	}
	return 0;
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

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	Enum_ssdt();

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


