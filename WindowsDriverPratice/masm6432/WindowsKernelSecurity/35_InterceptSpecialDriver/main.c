/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.2     新建日期: 2025.01.23
描  述: 拦截指定的驱动
备  注: 测试结果：64为win7拒绝加载 test.sys 驱动，32位的win7 KmdManager.exe程序卡死，test.sys 驱动一样无法正常加载
修改记录:

  1.  日期: 2025.01.23
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

  2.  日期: 2025.01.26
	  作者: 钱锐
	  内容:
		  1) 解决了无法在32位的win7 拦截其它驱动程序加载的bug，调用约定不同；这是由于32位操作系统下，驱动是函数调用方式遵循标准调用约定；
	  版本:V0.0.2

*************************************************/

#include <intrin.h>
#include <ntifs.h>
#include <ntddk.h>
#include <stdio.h>
#include <ntimage.h>

#include "ExportAPI.h"

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

VOID DenyLoadDriver(PCHAR _pImageBase)
{
#ifdef _AMD64_
	char ShellCode[6] = "\xB8\x22\x00\x00\xC0\xC3";
#else
	char ShellCode[8] = "\xB8\x22\x00\x00\xC0\xC2\x08\x00";		//32位，需要返回一个栈单元的字节数，这是由于32位操作系统下，驱动是函数调用方式遵循标准调用约定
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
		if (strstr(_strlwr(pchModuleName), "test.sys") != NULL)			//阻止test.sys驱动的加载
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

	KdPrint(("驱动卸载成功\n"));
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

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


