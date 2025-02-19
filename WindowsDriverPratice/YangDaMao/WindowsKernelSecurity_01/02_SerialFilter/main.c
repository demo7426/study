/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.19
��  ��: ����һ��NTģʽ�Ĺ����������
��  ע: ������ڲ���θ��Ӵ���������ʧ�ܣ��²������ڴ�������ͨ������ֻ����һ�Σ������θ��ӣ�������豸���������˳�����������֮�����Ϊ�����º��������޷���ȷ�����豸��
�޸ļ�¼:

  1.  ����: 2024.02.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	if (!DriverObject->DeviceObject)
		return;

	PDEVICEEXTENSION ptDevExtension = (PDEVICEEXTENSION)DriverObject->DeviceObject->DeviceExtension;
	if (!ptDevExtension)
		return;

	IoAcquireRemoveLock(&ptDevExtension->IORemoveLock, ptDevExtension->IORemoveLock_Tag);				//��֤���²�����ִ�е�ǰIRP�еĻص����̺���ʱ�ɹ�����

	if (ptDevExtension->pFDO)
		IoDetachDevice(ptDevExtension->pFDO);

	IoReleaseRemoveLock(&ptDevExtension->IORemoveLock, ptDevExtension->IORemoveLock_Tag);

	if (DriverObject->DeviceObject)
	{
		IoDeleteDevice(DriverObject->DeviceObject);
	}

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptPDO = NULL;
	PDEVICE_OBJECT ptFDO = NULL;

	DriverObject->DriverUnload = DriverUnload;

	ptPDO = GetDeviceObjectByName(L"\\Device\\Serial0");
	if (!ptPDO)
	{
		KdPrint(("GetDeviceObjectByName is err.\n"));
		return lNTStatus;
	}

	ptFDO = CreateNewDeviceAndAttachedToPDO(DriverObject, ptPDO);
	if (!ptFDO)
	{
		KdPrint(("CreateNewDeviceAndAttachedToPDO is err.\n"));
		ObDereferenceObject(ptPDO);
		ptPDO = NULL;
		return lNTStatus;
	}

	ObDereferenceObject(ptPDO);
	ptPDO = NULL;

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


