/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.13
��  ��: ʵ��һ��windows ��������Ļ����ṹ
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.13
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	IoDeleteDevice(DriverObject->DeviceObject);
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	DEVICE_OBJECT tDeviceObj;

	KdPrint(("�������ؿ�ʼ\n"));

	DriverObject->DriverUnload = DriverUnload;
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &tDeviceObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("��������ʧ��\n"));
		return lNTStatus;
	}

	DriverObject->Flags |= DO_BUFFERED_IO;				//��ʾʹ����������IO�ķ�ʽ�������ڴ���ΪI/O������仺����
	DriverObject->Flags &= ~DO_DEVICE_INITIALIZING;		//��� DO_DEVICE_INITIALIZING ��־��֪ͨϵͳ�豸�ѳ�ʼ����ɣ����Կ�ʼ��������

	KdPrint(("�������سɹ�\n"));
	return lNTStatus;
}


