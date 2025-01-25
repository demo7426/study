/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.25
描  述: 读写进程空间的数据
备  注:	可以使用进程挂靠、强行CR3的方式读写进程数据
		暂未测试该驱动
修改记录:

  1.  日期: 2025.01.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

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

//使用强行CR3方式读写进程数据
VOID ReadProcessMemory(PEPROCESS Process, PVOID Address, ULONG Length, PVOID Buffer)
{
	PVOID pvPdt = GetPdt(Process);
	PVOID pvOldPdt = NULL;

	//将本驱动对应的pdt切换为 Process 的,使驱动和进程它们对应同一个物理地址
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

//使用进程挂靠的方式读写进程数据
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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lStatus = STATUS_SUCCESS;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	return lStatus;
}

