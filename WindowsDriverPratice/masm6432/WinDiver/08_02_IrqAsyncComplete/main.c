/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.15
��  ��: irq�첽���
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.15
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

LIST_ENTRY g_tListEntry;

//��������ļ��жϻص�����
NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//��ȡ�ļ������жϻص�����
NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//�����ļ��жϻص�����
NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//�ر��ļ��жϻص�����
NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//�����ļ�·����

	if(DriverObject->DeviceObject)
		IoDeleteDevice(DriverObject->DeviceObject);

	IoDeleteSymbolicLink(&tSymbolicName);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;												//����״̬����ֵ
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");			//�豸�ļ�·����
	UNICODE_STRING tSymbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//�����ļ�·����
	PDEVICE_OBJECT ptDeviceObj = NULL;													//�豸����

	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�����豸�ļ�ʧ��\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSymbolicName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("������������ʧ��\n"));
		IoDeleteDevice(ptDeviceObj);
		return lNTStatus;
	}

	DriverObject->DriverUnload = DriverUnload;
	
	DriverObject->MajorFunction[IRP_MJ_CREATE] = Driver_Create;
	DriverObject->MajorFunction[IRP_MJ_READ] = Driver_Read;
	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = Driver_Cleanup;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Driver_Close;

	ptDeviceObj->Flags |= DO_BUFFERED_IO;
	ptDeviceObj->Flags &= ~DO_DEVICE_INITIALIZING;

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("�򿪴��ļ��ɹ�\n"));

	InitializeListHead(&g_tListEntry);

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("����Read\n"));

	IoMarkIrpPending(Irp);											//��irq���ڴ�����״̬

	InsertHeadList(&g_tListEntry, &Irp->Tail.Overlay.ListEntry);	//����δ�����irq

	KdPrint(("�˳�Read\n"));

	return STATUS_PENDING;
}

NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	INT32 nIrqCounter = 0;

	KdPrint(("����Cleanup\n"));
	
	while (!IsListEmpty(&g_tListEntry))
	{
		PLIST_ENTRY ptListEntry = RemoveTailList(&g_tListEntry);
		PIRP ptIrq = CONTAINING_RECORD(ptListEntry, IRP, Tail.Overlay.ListEntry);

		ptIrq->IoStatus.Information = 0;
		ptIrq->IoStatus.Status = STATUS_SUCCESS;

		IoCompleteRequest(ptIrq, IO_NO_INCREMENT);

		KdPrint(("��Ӧ��%05d Irq\n", nIrqCounter++));
	}

	RemoveEntryList(&g_tListEntry);

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("�˳�Cleanup\n"));

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("����Close\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("�˳�Close\n"));

	return STATUS_SUCCESS;
}



