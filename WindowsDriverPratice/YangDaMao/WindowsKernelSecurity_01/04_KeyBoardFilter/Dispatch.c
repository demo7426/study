/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Dispatch.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.19
��  ��: ��ǲ����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.02.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include "Dispatch.h"

#include <ntddkbd.h>

#include "Device.h"

static NTSTATUS IoCompletionRoutine(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ PIRP Irp,
	_In_reads_opt_(_Inexpressible_("varies")) PVOID Context
);

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(Irp);

	lNTStatus = IoCallDriver(pDevExt->pNextDevice, Irp);

	return lNTStatus;
}

NTSTATUS Dispatch_Pnp(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	return Dispatch_Default(DeviceObject, Irp);
}

NTSTATUS Dispatch_Power(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	PoStartNextPowerIrp(Irp);									//���Դ��������������������׼���ô�����һ����Դ IRP
	IoSkipCurrentIrpStackLocation(Irp);

	//�� Windows Vista ��ʼ����������Ӧ���� IoCallDriver�������� PoCallDriver ����Դ IRP ���ݸ���һ���ϵͼ������������ 
	//���ǣ��� Windows Server 2003��Windows XP �� Windows 2000 �ϣ��������������� PoCallDriver�������� IoCallDriver ���ܽ���Դ IRP ���ݸ���һ���ϵͼ������������
	lNTStatus = IoCallDriver(pDevExt->pNextDevice, Irp);

	return lNTStatus;
}

NTSTATUS Dispatch_Write(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulWriteLen = 0;

	__try
	{
		PVOID systemBuffer = Irp->AssociatedIrp.SystemBuffer;
		PVOID pvBuf = NULL;
		PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

		ulWriteLen = pIOStack->Parameters.Write.Length;

		if (systemBuffer && *(PCHAR)systemBuffer == 'a')			//���ڹ���
		{
			KdPrint(("%s\n", (PCHAR)systemBuffer));

			IoSkipCurrentIrpStackLocation(Irp);

			lNTStatus = IoCallDriver(pDevExt->pNextDevice, Irp);
			return lNTStatus;
		}
		else
		{
			ulWriteLen = 0;
			KdPrint(("SystemBuffer is null\n"));
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("д�������׳��쳣\n"));
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulWriteLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_Read_Async(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	KdPrint(("Dispatch_Read_Async is enter.\n"));

	IoAcquireRemoveLock(&pDevExt->IORemoveLock, pDevExt->IORemoveLock_Tag);				//��֤���²�����ִ�е�ǰIRP�еĻص����̺���ʱ�ɹ�����

	//IoSkipCurrentIrpStackLocation(Irp);
	IoCopyCurrentIrpStackLocationToNext(Irp);

	IoSetCompletionRoutine((PIRP)Irp, IoCompletionRoutine, NULL, TRUE, TRUE, TRUE);

	lNTStatus = IoCallDriver(pDevExt->pNextDevice, Irp);

	KdPrint(("Dispatch_Read_Async is end.\n"));

	return lNTStatus;
}

NTSTATUS Dispatch_Read_Sync(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	KdPrint(("Dispatch_Read_Sync is enter.\n"));

	IoAcquireRemoveLock(&pDevExt->IORemoveLock, pDevExt->IORemoveLock_Tag);				//��֤���²�����ִ�е�ǰIRP�еĻص����̺���ʱ�ɹ�����

	//IoSkipCurrentIrpStackLocation(Irp);
	IoCopyCurrentIrpStackLocationToNext(Irp);

	//���ȡ�ÿ���Ȩ
	KEVENT tKEvent;

	KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);
	IoSetCompletionRoutine((PIRP)Irp, IoCompletionRoutine, &tKEvent, TRUE, TRUE, TRUE);

	lNTStatus = IoCallDriver(pDevExt->pNextDevice, Irp);
	if (lNTStatus == STATUS_PENDING)
	{
		KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);
	}

	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	KdPrint(("Dispatch_Read_Sync is end.\n"));

	return STATUS_SUCCESS;
}

static NTSTATUS IoCompletionRoutine(
	_In_ PDEVICE_OBJECT DeviceObject,
	_In_ PIRP Irp,
	_In_reads_opt_(_Inexpressible_("varies")) PVOID Context
)
{
	PKEVENT ptKEvent = Context;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;
	
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	if (Irp->PendingReturned)
		IoMarkIrpPending(Irp);

	if (Irp->IoStatus.Information && pIOStack->MajorFunction == IRP_MJ_READ)
	{
		PKEYBOARD_INPUT_DATA ptKeyBoard_InputData = Irp->AssociatedIrp.SystemBuffer;
		if (ptKeyBoard_InputData->Flags & KEY_BREAK)
			KdPrint(("Key = 0x%x is up\n", ptKeyBoard_InputData->MakeCode));
		else
			KdPrint(("Key = 0x%x is down\n", ptKeyBoard_InputData->MakeCode));
	}

	if (ptKEvent != NULL)		//�����Ƿ���Ҫ����ͬ������
	{
		KeSetEvent(ptKEvent, IO_NO_INCREMENT, FALSE);

		IoReleaseRemoveLock(&pDevExt->IORemoveLock, pDevExt->IORemoveLock_Tag);
		KdPrint(("IoReleaseRemoveLock sync is enter\n"));

		return STATUS_MORE_PROCESSING_REQUIRED;
	}

	IoReleaseRemoveLock(&pDevExt->IORemoveLock, pDevExt->IORemoveLock_Tag);
	KdPrint(("IoReleaseRemoveLock async is enter\n"));

	return STATUS_CONTINUE_COMPLETION;

}

