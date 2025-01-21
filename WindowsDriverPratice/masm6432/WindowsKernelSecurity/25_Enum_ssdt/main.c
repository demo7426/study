/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.21
描  述: 枚举ssdt(系统服务描述符表)
备  注: 
修改记录:

  1.  日期: 2025.01.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <intrin.h>
#include <ntddk.h>

typedef struct _KSYSTEM_SERVICE_TABLE
{
	PULONG ServiceTableBase;							//服务函数地址表基址
	PULONG ServiceCounterTableBase;
	ULONG NumberOfService;								//服务函数的个数
	PULONG ParamTableBase;								//服务函数参数表基址
}KSYSTEM_SERVICE_TABLE, * PKSYSTEM_SERVICE_TABLE;

#ifdef _X86_

extern PKSYSTEM_SERVICE_TABLE KeServiceDescriptorTable;

/// <summary>
/// 枚举32位操作系统下的ssdt
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

//获取SSDT地址
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
/// 枚举64位操作系统下的ssdt
/// </summary>
/// <param name=""></param>
static VOID Enum_ssdt(VOID)
{
	PKSYSTEM_SERVICE_TABLE ptServiceTable = NULL;
	LONG lOffset = 0;
	PCHAR pchBase = (PCHAR)__readmsr(0xc0000082);
	LONG lFuncOffset = 0;
	ULONG64 ullFuncAddr = 0;

	pchBase += 761;													//通过windbg逆向计算得出的值
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	Enum_ssdt();

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


