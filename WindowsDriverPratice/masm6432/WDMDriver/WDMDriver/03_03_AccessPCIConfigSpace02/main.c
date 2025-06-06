/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.03
描  述: 使用HalGetBusData系统API获取PCI信息
备  注:
修改记录:

  1.  日期: 2025.01.03
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>

#ifdef _WIN64
ULONG HalGetBusData(
	BUS_DATA_TYPE BusDataType,
	ULONG BusNumber,
	ULONG SlotNumber,
	PVOID Buffer,
	ULONG Length
);
#endif // _WIN64

VOID DisplayPCIConfig(INT32 _Bus, INT32 _Dev, INT32 _Func)
{
	PCI_COMMON_CONFIG tPciComConfig = { 0 };
	PPCI_COMMON_HEADER ptPciComHeader = NULL;
	PCI_SLOT_NUMBER tPciSlotNum = { 0 };

	tPciSlotNum.u.AsULONG = 0;
	tPciSlotNum.u.bits.DeviceNumber = _Dev;
	tPciSlotNum.u.bits.FunctionNumber = _Func;

	//获取PCI信息
	if (HalGetBusData(PCIConfiguration, _Bus, tPciSlotNum.u.AsULONG, &tPciComConfig, PCI_COMMON_HDR_LENGTH) != PCI_COMMON_HDR_LENGTH)
	{
		return;
	}

	KdPrint(("*********************************************\n"));
	KdPrint(("_Bus = %d, _Dev = %d, _Func = %d\n", _Bus, _Dev, _Func));

	//显示PCI信息
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	for (INT32 unBus = 0; unBus < PCI_MAX_BRIDGE_NUMBER; unBus++)
	{
		for (INT32 unDev = 0; unDev < PCI_MAX_DEVICES; unDev++)
		{
			for (INT32 unFunc = 0; unFunc < PCI_MAX_FUNCTION; unFunc++)
			{
				DisplayPCIConfig(unBus, unDev, unFunc);
			}
		}
	}

	return STATUS_SUCCESS;
}

