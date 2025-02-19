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
#include "Device.h"

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICEEXTENSION pDevExt = DeviceObject->DeviceExtension;

	IoSkipCurrentIrpStackLocation(Irp);

	lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);

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
	lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);

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

			lNTStatus = IoCallDriver(pDevExt->pFDO, Irp);
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



