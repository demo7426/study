/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.14
��  ��: ����һ�������ķ��Ŷ��󣬼���ӡ��������Ĳ�����Ϣ
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.14
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// ��ӡ�������������Ϣ
/// </summary>
/// <param name="_pDriverObject"></param>
VOID EnumDriver(PDRIVER_OBJECT _pDriverObject);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	
	IoDeleteSymbolicLink(&tSysbolicLinkName);
	IoDeleteDevice(DriverObject->DeviceObject);
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	UNICODE_STRING tSysbolicLinkName = RTL_CONSTANT_STRING(L"\\??\\HelloDDK");
	PDEVICE_OBJECT ptDeviceObject = NULL;

	KdPrint(("�������ؿ�ʼ\n"));

	DriverObject->DriverUnload = DriverUnload;
	lNTStatus = IoCreateDevice(DriverObject, 0, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�����豸����ʧ��\n"));
		return lNTStatus;
	}

	lNTStatus = IoCreateSymbolicLink(&tSysbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�������ű����Ӷ���ʧ��\n"));
		return lNTStatus;
	}

	DriverObject->Flags |= DO_BUFFERED_IO;				//��ʾʹ����������IO�ķ�ʽ�������ڴ���ΪI/O������仺����
	DriverObject->Flags &= ~DO_DEVICE_INITIALIZING;		//��� DO_DEVICE_INITIALIZING ��־��֪ͨϵͳ�豸�ѳ�ʼ����ɣ����Կ�ʼ��������

	EnumDriver(DriverObject);

	KdPrint(("�������سɹ�\n"));
	return lNTStatus;
}

VOID EnumDriver(PDRIVER_OBJECT _pDriverObject)
{
	KdPrint(("Driver:0x%p\n", _pDriverObject));
	KdPrint(("Device:0x%p\n", _pDriverObject->DeviceObject));
	KdPrint(("����������:%wZ\n", &_pDriverObject->DriverName));
	KdPrint(("������:%wZ\n", &_pDriverObject->DriverExtension->ServiceKeyName));
	KdPrint(("Ӳ�����ݿ���:%wZ\n", _pDriverObject->HardwareDatabase));
}
