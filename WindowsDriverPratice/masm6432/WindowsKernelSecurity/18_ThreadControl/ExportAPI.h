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

#endif // !__EXPORTAPI_H__



