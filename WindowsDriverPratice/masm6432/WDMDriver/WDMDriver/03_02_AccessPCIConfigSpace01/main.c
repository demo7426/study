/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.01
��  ��: ����PCI���ÿռ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.01
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>

VOID DisplayPCIConfig(INT32 _Bus, INT32 _Dev, INT32 _Func)
{
	PCI_COMMON_CONFIG tPciComConfig = { 0 };
	PPCI_COMMON_HEADER ptPciComHeader = NULL;
	PCI_SLOT_NUMBER tPciSlotNum = { 0 };
	ULONG ulAddr = 0;
	ULONG ulData = 0;

	tPciSlotNum.u.AsULONG = 0;
	tPciSlotNum.u.bits.DeviceNumber = _Dev;
	tPciSlotNum.u.bits.FunctionNumber = _Func;
	
	ulAddr = 0x80000000 | (_Bus << 16) | (tPciSlotNum.u.AsULONG << 8);

	//��ȡPCI��Ϣ
	for (SHORT i = 0; i < 0x100; i+=4)
	{
		ulAddr |= i;
		WRITE_PORT_ULONG((PULONG)0xcf8, ulAddr);
		
		ulData = READ_PORT_ULONG((PULONG)0xcfc);
		((PULONG)&tPciComConfig)[i >> 2] = ulData;
	}

	//��ʾPCI��Ϣ
	ptPciComHeader = (PPCI_COMMON_HEADER)&tPciComConfig;
	KdPrint(("VendorID:0x%x\n", ptPciComHeader->VendorID));
	KdPrint(("DeviceID:0x%x\n", ptPciComHeader->DeviceID));
	KdPrint(("Command:0x%x\n", ptPciComHeader->Command));
	KdPrint(("Status:0x%x\n", ptPciComHeader->Status));
	KdPrint(("RevisionID:0x%x\n", ptPciComHeader->RevisionID));
	KdPrint(("ProgIf:0x%x\n", ptPciComHeader->ProgIf));
	KdPrint(("SubClass:0x%x\n", ptPciComHeader->SubClass));
	KdPrint(("BaseClass:0x%x\n", ptPciComHeader->BaseClass));
	KdPrint(("CacheLineSize:0x%x\n", ptPciComHeader->CacheLineSize));
	KdPrint(("LatencyTimer:0x%x\n", ptPciComHeader->LatencyTimer));
	KdPrint(("HeaderType:0x%x\n", ptPciComHeader->HeaderType));
	KdPrint(("BIST:0x%x\n", ptPciComHeader->BIST));

	for (CHAR i = 0; i < 6; i++)
	{
		KdPrint(("BaseAddresses[%d]:0x%x\n", i, ptPciComHeader->u.type0.BaseAddresses[i]));
	}

	KdPrint(("InterruptLine:0x%x\n", ptPciComHeader->u.type0.InterruptLine));
	KdPrint(("InterruptPin:0x%x\n", ptPciComHeader->u.type0.InterruptPin));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	for (INT32 unBus = 0; unBus < PCI_MAX_BRIDGE_NUMBER; unBus++)
	{
		for (INT32 unDev = 0; unDev < PCI_MAX_DEVICES; unDev++)
		{
			for (INT32 unFunc = 0; unFunc < PCI_MAX_FUNCTION; unFunc++)
			{
				KdPrint(("*********************************************\n"));
				KdPrint(("unBus = %d, unDev = %d, unFunc = %d\n", unBus, unDev, unFunc));
				DisplayPCIConfig(unBus, unDev, unFunc);
			}
		}
	}

	return STATUS_SUCCESS;
}

