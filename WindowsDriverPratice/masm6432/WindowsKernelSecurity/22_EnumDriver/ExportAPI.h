/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	ExportAPI.h
��  ��:	Ǯ��      �汾: V0.0.2     �½�����: 2025.01.19
��  ��: �����ں�API
��  ע: �в��ֽӿڵ����ˣ�����ͷ�ļ�δ����
�޸ļ�¼:

  1.  ����: 2025.01.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

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
	ULONG Count;	//�ں����Լ��ص�ģ��ĸ���
	SYSTEM_MODULE_INFORMATION_ENTRY Module[1];
}SYSTEM_MODULE_INFORMATION, * PSYSTEM_MODULE_INFORMATION;

//���ݽ�����Ϣ,��ȡ��������
PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);

//�������
NTSTATUS PsSuspendProcess(IN PEPROCESS Process);

//�ָ�����
NTSTATUS PsResumeProcess(IN PEPROCESS Process);

//��ȡ������
HANDLE PsGetProcessInheritedFromUniqueProcessId(IN PEPROCESS Process);

// �򿪶�Ӧ�̣߳�����������
NTSYSCALLAPI NTSTATUS ZwOpenThread(_Out_ PHANDLE ThreadHandle, _In_ ACCESS_MASK DesiredAccess, _In_ POBJECT_ATTRIBUTES ObjectAttributes, _In_ PCLIENT_ID ClientId);

// δ���ں˵���������Ҫ�ֶ���ȡ���������Ӳ����ķ�ʽ
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



