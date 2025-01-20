/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	ExportAPI.h
作  者:	钱锐      版本: V0.0.2     新建日期: 2025.01.19
描  述: 声明内核API
备  注: 有部分接口导出了，但是头文件未声明
修改记录:

  1.  日期: 2025.01.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.0.1

*************************************************/

#ifndef __EXPORTAPI_H__
#define __EXPORTAPI_H__

#include <ntddk.h>

typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	UCHAR Initialized[4];
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitalizationOrderModuleList;
	PVOID EntryInProgress;
	UCHAR ShutdownInProcess[8];
	PVOID ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _PEB
{
	UCHAR InheritedAddressSpace;
	UCHAR ReadImageFileExecOptions;
	UCHAR BeingDebugged;
	union {
		UCHAR BitField[5];
	};
	PVOID Mutant;
	PVOID ImageBaseAddress;
	PPEB_LDR_DATA Ldr;
	PVOID ProcessParameters;
	ULONG64 SubSystemData;
} PEB, * PPEB;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	UINT64 SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	UINT32 Flags;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;
typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemModuleInformation = 11
} SYSTEM_INFORMATION_CLASS;

typedef struct _SYSTEM_MODULE_INFORMATION_ENTRY
{
	HANDLE  Section;
	PVOID  MappedBase;
	PVOID  Base;
	ULONG  Size;
	ULONG  Flags;
	USHORT  LoadOrderIndex;
	USHORT  InitOrderIndex;
	USHORT  LoadCount;
	USHORT  PathLength;
	CHAR    ImageName[256];
}SYSTEM_MODULE_INFORMATION_ENTRY, * PSYSTEM_MODULE_INFORMATION_ENTRY;

typedef struct _SYSTEM_MODULE_INFORMATION
{
	ULONG Count;	//内核中以加载的模块的个数
	SYSTEM_MODULE_INFORMATION_ENTRY Module[1];
}SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

//根据进程信息,获取进程名称
PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);

//挂起进程
NTSTATUS PsSuspendProcess(IN PEPROCESS Process);

//恢复进程
NTSTATUS PsResumeProcess(IN PEPROCESS Process);

//获取父进程
HANDLE PsGetProcessInheritedFromUniqueProcessId(IN PEPROCESS Process);

// 打开对应线程，导出需声明
NTSYSCALLAPI NTSTATUS ZwOpenThread(_Out_ PHANDLE ThreadHandle, _In_ ACCESS_MASK DesiredAccess, _In_ POBJECT_ATTRIBUTES ObjectAttributes, _In_ PCLIENT_ID ClientId);

// 未从内核导出，所以要手动获取，这里采用硬编码的方式
typedef NTSTATUS(*PFNZWTERMINATETHREAD)(HANDLE hThread, ULONG uExitCode);

NTSYSCALLAPI PPEB PsGetProcessPeb(PEPROCESS Process);

NTSYSCALLAPI NTSTATUS
ZwQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength OPTIONAL
);

#endif // !__EXPORTAPI_H__



