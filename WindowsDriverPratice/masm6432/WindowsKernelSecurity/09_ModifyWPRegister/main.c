/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.16
描  述: 修改写保护寄存器;
备  注: 默认写保护为1,即开启状态;0--关闭写保护;1--开启写保护;
修改记录:

  1.  日期: 2025.01.16
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>
#include <intrin.h>

//关闭写保护
KIRQL WPOff(VOID)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();		//硬件优先级提高到 IRQL = DISPATCH_LEVEL，从而屏蔽当前处理器上等效或更低 IRQL 的中断。
	ULONG_PTR ulCr0  = __readcr0();

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

VOID Test01(VOID)
{
	const SIZE_T unBufSize = 1024;				//缓冲区大小
	PCHAR pchBuf00, pchBuf01;

	pchBuf00 = (PCHAR)ExAllocatePool(NonPagedPool, unBufSize);		//因为将硬件优先级提高到 IRQL = DISPATCH_LEVEL了，不能使用分页内存，会有系统崩溃风险
	if (!pchBuf00)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return;
	}

	pchBuf01 = (PCHAR)ExAllocatePool(NonPagedPool, unBufSize);
	if (!pchBuf01)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return;
	}

	RtlZeroMemory(pchBuf00, unBufSize);
	RtlCopyMemory(pchBuf00, "非分页内存中的一条字符串数据", strlen("非分页内存中的一条字符串数据"));

	RtlZeroMemory(pchBuf01, unBufSize);
	RtlCopyMemory(pchBuf01, pchBuf00, strlen(pchBuf00));		//将连续的字符串数据拷贝到另外非分页内存中

	KdPrint(("pchBuf00 = %s\n", pchBuf00));
	KdPrint(("pchBuf01 = %s\n", pchBuf01));

	ExFreePool(pchBuf00);
	ExFreePool(pchBuf01);

	pchBuf00 = NULL;
	pchBuf01 = NULL;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	KIRQL tKIrqL = WPOff();			//关闭写保护，并且拉高当前的硬件优先级，后续可以使用hook操作

	Test01();

	WPOn(tKIrqL);					//开启写保护，并且降低当前的硬件优先级

	return lNTStatus;
}


