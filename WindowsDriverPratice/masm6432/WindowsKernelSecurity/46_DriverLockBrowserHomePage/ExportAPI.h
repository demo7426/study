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
#include <windef.h>

typedef struct _PEB_LDR_DATA {
    BYTE Reserved1[8];
    PVOID Reserved2[3];
    LIST_ENTRY InMemoryOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _LDR_DATA_TABLE_ENTRY {
    PVOID Reserved1[2];
    LIST_ENTRY InMemoryOrderLinks;
    PVOID Reserved2[2];
    PVOID DllBase;
    PVOID Reserved3[2];
    UNICODE_STRING FullDllName;
    BYTE Reserved4[8];
    PVOID Reserved5[3];
#pragma warning(push)
#pragma warning(disable: 4201) // we'll always use the Microsoft compiler
    union {
        ULONG CheckSum;
        PVOID Reserved6;
    } DUMMYUNIONNAME;
#pragma warning(pop)
    ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    BYTE Reserved1[16];
    PVOID Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef
VOID
(NTAPI* PPS_POST_PROCESS_INIT_ROUTINE) (
    VOID
    );

typedef struct _PEB {
    BYTE Reserved1[2];
    BYTE BeingDebugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    PPEB_LDR_DATA Ldr;
    PRTL_USER_PROCESS_PARAMETERS ProcessParameters;
    PVOID Reserved4[3];
    PVOID AtlThunkSListPtr;
    PVOID Reserved5;
    ULONG Reserved6;
    PVOID Reserved7;
    ULONG Reserved8;
    ULONG AtlThunkSListPtr32;
    PVOID Reserved9[45];
    BYTE Reserved10[96];
    PPS_POST_PROCESS_INIT_ROUTINE PostProcessInitRoutine;
    BYTE Reserved11[128];
    PVOID Reserved12[1];
    ULONG SessionId;
} PEB, * PPEB;

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

NTSYSCALLAPI NTSTATUS ZwQuerySystemInformation(IN SYSTEM_INFORMATION_CLASS SystemInformationClass, OUT PVOID SystemInformation, IN ULONG SystemInformationLength, OUT PULONG ReturnLength OPTIONAL);

typedef VOID (*PFNMIPROCESSLOADERENTRY)(IN PVOID DataTableEntry, IN LOGICAL Insert);

#endif // !__EXPORTAPI_H__



