/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.19
��  ��: ʱ�亯����irp��ʱ����
��  ע:	
�޸ļ�¼:

  1.  ����: 2024.12.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

KTIMER g_tKTimer;
KDPC g_tkDpc;
LARGE_INTEGER g_tTimeout;		//DPC��ʱ�����

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Driver_Close (_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DPC_Timer_Routine(_In_ struct _KDPC* Dpc, _In_opt_ PVOID DeferredContext, _In_opt_ PVOID SystemArgument1, _In_opt_ PVOID SystemArgument2)
{
	KdPrint(("DPC_Timer_Routine is called.\n"));

	PIRP pIrp = (PIRP)DeferredContext;
	if (!pIrp)
		return;

	pIrp->IoStatus.Information = 0;
	pIrp->IoStatus.Status = STATUS_CANCELLED;

	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	//KeSetTimer(&g_tKTimer, g_tTimeout, &g_tkDpc);
}

/// <summary>
/// ��ӡ����ʱ��
/// </summary>
/// <param name=""></param>
VOID PrintLocalTime(VOID)
{
	LARGE_INTEGER tSystemTime;
	LARGE_INTEGER tLocalTime;
	TIME_FIELDS tTimeFields;

	KeQuerySystemTime(&tSystemTime);
	ExSystemTimeToLocalTime(&tSystemTime, &tLocalTime);
	RtlTimeToTimeFields(&tLocalTime, &tTimeFields);

	KdPrint(("����ʱ��: %4d-%2d-%2d %2d:%2d:%2d:%3d",
		tTimeFields.Year, tTimeFields.Month, tTimeFields.Day,
		tTimeFields.Hour, tTimeFields.Minute, tTimeFields.Second, tTimeFields.Milliseconds));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));

	if (DriverObject->DeviceObject)
	{
		UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");			//����������

		KeCancelTimer(&g_tKTimer);

		IoDeleteSymbolicLink(&tSysbolicLinkName);
		IoDeleteDevice(DriverObject->DeviceObject);
	}
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptDeviceObj = NULL;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");				//�豸������
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");				//����������

	KdPrint(("�������سɹ�\n"));

	DriverObject->DriverUnload = DriverUnload;

	//����һ���豸�������豸���������в���ϵͳ�Զ�����
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�����豸����ʧ��\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSysbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("������������ʧ��\n"));
		return lNTStatus;
	}

	DriverObject->MajorFunction[IRP_MJ_CREATE] = Driver_Create;
	DriverObject->MajorFunction[IRP_MJ_READ] = Driver_Read;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = Driver_Close;

	PrintLocalTime();

	return lNTStatus;
}

NTSTATUS Driver_Create(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Create is enter.\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Driver_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Read is enter.\n"));

	KeInitializeTimer(&g_tKTimer);
	KeInitializeDpc(&g_tkDpc, DPC_Timer_Routine, Irp);

	g_tTimeout = RtlConvertLongToLargeInteger(-10 * 2000 * 1000);
	KeSetTimer(&g_tKTimer, g_tTimeout, &g_tkDpc);

	IoMarkIrpPending(Irp);

	return STATUS_PENDING;
}

NTSTATUS Driver_Close(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	KdPrint(("Driver_Close is enter.\n"));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}
