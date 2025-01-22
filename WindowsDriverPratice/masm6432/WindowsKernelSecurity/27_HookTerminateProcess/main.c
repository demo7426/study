/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.21
描  述: 枚举ssdt(系统服务描述符表)、hook NtTerminateProcess进程
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

#include "ExportAPI.h"

typedef struct _KSYSTEM_SERVICE_TABLE
{
	PULONG ServiceTableBase;							//服务函数地址表基址
	PULONG ServiceCounterTableBase;
	ULONG NumberOfService;								//服务函数的个数
	PULONG ParamTableBase;								//服务函数参数表基址
}KSYSTEM_SERVICE_TABLE, * PKSYSTEM_SERVICE_TABLE;


typedef NTSTATUS(*NtTerminateProcess)(HANDLE ProcessHandle, NTSTATUS ExitStatus);

static NtTerminateProcess g_pOldNtTerminateProcess = NULL;

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
PKSYSTEM_SERVICE_TABLE MyGetKeServiceDescriptorTable()
{
	PKSYSTEM_SERVICE_TABLE ptServiceTable = NULL;
	LONG lOffset = 0;
	PCHAR pchBase = (PCHAR)__readmsr(0xc0000082);
	LONG lFuncOffset = 0;
	ULONG64 ullFuncAddr = 0;

	pchBase += 761;													//通过windbg逆向计算得出的值
	lOffset = *(PULONG)(pchBase - 4);
	ptServiceTable = (PKSYSTEM_SERVICE_TABLE)(pchBase + lOffset);

	return ptServiceTable;
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

//关闭写保护
KIRQL WPOff(VOID)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();		//硬件优先级提高到 IRQL = DISPATCH_LEVEL，从而屏蔽当前处理器上等效或更低 IRQL 的中断。
	ULONG_PTR ulCr0 = __readcr0();

	//写保护寄存器置零
#ifdef _X86_
	ulCr0 &= ~0x00010000;
#else
	ulCr0 &= ~0x0000000000010000;
#endif // _X86_

	_disable();									//禁用中断
	__writecr0(ulCr0);

	return tKIrqL;
}

//开启写保护
VOID WPOn(KIRQL _KIrqL)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();
	ULONG_PTR ulCr0 = __readcr0();

	ulCr0 |= 0x10000;							//写保护寄存器置1

	_enable();									//开启中断
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
		if (strcmp(PsGetProcessImageFileName(ptPEProcess), "calc.exe") == 0 && IoGetCurrentProcess() != ptPEProcess)		//保证自身是可以正常关闭进程的
		{
			ObDereferenceObject(ptPEProcess);
			return STATUS_ACCESS_DENIED;
		}
	}

	ObDereferenceObject(ptPEProcess);
	return g_pOldNtTerminateProcess(ProcessHandle, ExitStatus);
}

//借用KeBugCheckEx函数，修改其汇编代码的跳转地址，跳转到MyNtTerminateProcess函数
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
	const SIZE_T unNtTerminateProcessIndex = 41;		//NtTerminateProcess进程的序号

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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	HookTerminateProcess();

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


