/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.16
��  ��: ����Windowsϵͳ���һ��������ڴ�
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.16
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>
//#include <wdf.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	KUSER_SHARED_DATA* ptKUserSharedData = SharedUserData;

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	KdPrint(("ϵͳ��Ŀ¼:\t%ls\n", ptKUserSharedData->NtSystemRoot));
	KdPrint(("ϵͳ�ں˰汾��:\t%u.%u\n", ptKUserSharedData->NtMajorVersion, ptKUserSharedData->NtMinorVersion));
	KdPrint(("������ʽ:\t%s\n", ptKUserSharedData->SafeBootMode? "��ȫģʽ������": "��������"));

	return lNTStatus;
}


