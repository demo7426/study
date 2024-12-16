/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.16
��  ��: �Զ���startio����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.16
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

KDEVICE_QUEUE g_tKDevice_Queue;

//��������ļ��жϻص�����
NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//��ȡ�ļ������жϻص�����
NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//�����ļ��жϻص�����
NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//�ر��ļ��жϻص�����
NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//startio����
VOID Driver_Startio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//�Զ���startio����
VOID MyStartio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

//Irqȡ������
VOID Irp_Cancel(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ _IRQL_uses_cancel_ struct _IRP* Irp);


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//�����ļ�·����

	if (DriverObject->DeviceObject)
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

	DriverObject->DriverStartIo = Driver_Startio;

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

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KeInitializeDeviceQueue(&g_tKDevice_Queue);

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("����Read\n"));

	IoMarkIrpPending(Irp);											//��irq���ڴ�����״̬

	if (!KeInsertDeviceQueue(&g_tKDevice_Queue, &Irp->Tail.Overlay.DeviceQueueEntry))
	{
		MyStartio(DeviceObject, Irp);
	}

	//IoStartPacket(DeviceObject, Irp, NULL, Irp_Cancel);				//����� �����Irp��������� Driver_Startio �������д���


	KdPrint(("�˳�Read\n"));

	return STATUS_PENDING;
}

NTSTATUS Driver_Cleanup(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	INT32 nIrqCounter = 0;

	KdPrint(("����Cleanup\n"));

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


VOID Irp_Cancel(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ _IRQL_uses_cancel_ struct _IRP* Irp)
{
	KdPrint(("����Cancel\n"));

	IoReleaseCancelSpinLock(Irp->CancelIrql);			//�����ͷ�������;TODO��������øú�����ԭ��δ֪

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_CANCELLED;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	KdPrint(("�˳�Cancel\n"));
}

VOID Driver_Startio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("����Driver_Startio\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	IoStartNextPacket(DeviceObject, TRUE);

	KdPrint(("�˳�Driver_Startio\n"));
}

VOID MyStartio(_Inout_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	PIRP ptCurIrp = Irp;
	PKDEVICE_QUEUE_ENTRY ptCurEntry = NULL;

	KdPrint(("����MyStartio\n"));

	while (TRUE)
	{
		ptCurIrp->IoStatus.Information = 0;
		ptCurIrp->IoStatus.Status = STATUS_SUCCESS;

		IoCompleteRequest(ptCurIrp, IO_NO_INCREMENT);

		ptCurEntry = KeRemoveDeviceQueue(&g_tKDevice_Queue);
		if (!ptCurEntry)
		{
			break;
		}

		ptCurIrp = CONTAINING_RECORD(ptCurEntry, IRP, Tail.Overlay.DeviceQueueEntry);
	}


	KdPrint(("�˳�MyStartio\n"));
}

