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

#endif // !__EXPORTAPI_H__



