/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.19
��  ��: ͨ���豸���������������
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

VOID APC_Routine(_In_ PVOID ApcContext, _In_ PIO_STATUS_BLOCK IoStatusBlock, _In_ ULONG Reserved)
{
	PKEVENT ptKEvent = (PKEVENT)ApcContext;
	if (!ptKEvent)
		return;

	KeSetEvent(ptKEvent, IO_NO_INCREMENT, FALSE);
}

/// <summary>
/// ͨ���豸�����ͬ����������������������
/// </summary>
/// <param name=""></param>
VOID CallDiver_Sync_Test01(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//�豸������
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//����������
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);

	InitializeObjectAttributes(&tObjAttr, &tDeviceName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL, 
		&tObjAttr, 
		&tIO_Status, 
		NULL, 
		FILE_ATTRIBUTE_NORMAL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		FILE_OPEN, 
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL, 
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("���ļ�ʧ��: 0x%x\n", lNTStatus));
		return;
	}

	ZwReadFile(handFile, NULL, NULL, NULL, &tIO_Status, NULL, 0, &tOffset, NULL);

	ZwClose(handFile);
}

/// <summary>
/// ͨ���豸������첽��������������������
/// </summary>
/// <param name=""></param>
VOID CallDiver_Async_Test02(VOID)
{
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//�豸������
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//����������
	HANDLE handFile = NULL;
	OBJECT_ATTRIBUTES tObjAttr;
	IO_STATUS_BLOCK tIO_Status;
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	LARGE_INTEGER tOffset = RtlConvertLongToLargeInteger(0);
	KEVENT tKEvent;

	InitializeObjectAttributes(&tObjAttr, &tSysbolicLinkName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIO_Status,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("���ļ�ʧ��: 0x%x\n", lNTStatus));
		return;
	}

	KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);
	lNTStatus = ZwReadFile(handFile, NULL, APC_Routine, &tKEvent, &tIO_Status, NULL, 0, &tOffset, NULL);

	//lNTStatus ����ֵΪ STATUS_CANCELLED
	//TODO:����Ĵ���û����Ч
	if (NT_SUCCESS(lNTStatus))
	{
		if (lNTStatus == STATUS_PENDING)
		{
			KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
		}
		
	}
	KdPrint(("ZwReadFile: 0x%x\n", lNTStatus));

	ZwClose(handFile);
}


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptDeviceObj = NULL;

	KdPrint(("�������سɹ�\n"));

	DriverObject->DriverUnload = DriverUnload;

	//CallDiver_Sync_Test01();
	CallDiver_Async_Test02();

	return lNTStatus;
}


