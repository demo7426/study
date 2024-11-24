/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.24
��  ��: IO���ƣ�ʹ�������ķ�ʽ
��  ע:	�Ƿ�Ϊ�����ķ�ʽ���� IO Method ��������������Ǵ����豸�ļ�ʱ�� Flags ����
�޸ļ�¼:

  1.  ����: 2024.11.24
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_READ_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)			//������
#define IO_WRITE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_NEITHER, FILE_ANY_ACCESS)			//д����
#define IO_QUERY_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)			//��ѯ��Ϣ

/// <summary>
/// ��ǲ����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ��������ʽ��IO����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_BufferIOControl(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");

	IoDeleteDevice(DriverObject->DeviceObject);
	IoDeleteSymbolicLink(&tSymbolicLinkName);

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	UNICODE_STRING tDeviceName = RTL_CONSTANT_STRING(L"\\Device\\HelloDDK");
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_OBJECT ptDeviceObject = NULL;

	lNTStatus = IoCreateDevice(DriverObject, NULL, &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);		//���һ�����������Ӧ���Ƕ���ָ��
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�����豸�ļ�ʧ��\n"));
		return lNTStatus;
	}

	ptDeviceObject->Flags |= DO_DIRECT_IO;					//���û���Ĳ�����ʽ
	ptDeviceObject->Flags &= ~DO_DEVICE_INITIALIZING;			//�����ʼ����־

	lNTStatus = IoCreateSymbolicLink(&tSymbolicLinkName, &tDeviceName);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�������������ļ�ʧ��\n"));
		IoDeleteDevice(ptDeviceObject);
		return lNTStatus;
	}

	for (size_t i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
	{
		DriverObject->MajorFunction[i] = Driver_Dispatch;
	}
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = Dispatch_BufferIOControl;


	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));
	return lNTStatus;
}

NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	const char* pchIrpNames[] = {
		"IRP_MJ_CREATE					   ",
		"IRP_MJ_CREATE_NAMED_PIPE		   ",
		"IRP_MJ_CLOSE					   ",
		"IRP_MJ_READ					   ",
		"IRP_MJ_WRITE					   ",
		"IRP_MJ_QUERY_INFORMATION		   ",
		"IRP_MJ_SET_INFORMATION			   ",
		"IRP_MJ_QUERY_EA				   ",
		"IRP_MJ_SET_EA					   ",
		"IRP_MJ_FLUSH_BUFFERS			   ",
		"IRP_MJ_QUERY_VOLUME_INFORMATION   ",
		"IRP_MJ_SET_VOLUME_INFORMATION	   ",
		"IRP_MJ_DIRECTORY_CONTROL		   ",
		"IRP_MJ_FILE_SYSTEM_CONTROL		   ",
		"IRP_MJ_DEVICE_CONTROL			   ",
		"IRP_MJ_INTERNAL_DEVICE_CONTROL	   ",
		"IRP_MJ_SHUTDOWN				   ",
		"IRP_MJ_LOCK_CONTROL			   ",
		"IRP_MJ_CLEANUP					   ",
		"IRP_MJ_CREATE_MAILSLOT			   ",
		"IRP_MJ_QUERY_SECURITY			   ",
		"IRP_MJ_SET_SECURITY			   ",
		"IRP_MJ_POWER					   ",
		"IRP_MJ_SYSTEM_CONTROL			   ",
		"IRP_MJ_DEVICE_CHANGE			   ",
		"IRP_MJ_QUERY_QUOTA				   ",
		"IRP_MJ_SET_QUOTA				   ",
		"IRP_MJ_PNP						   ",
		"IRP_MJ_PNP_POWER				   ",
		"IRP_MJ_MAXIMUM_FUNCTION		   "
	};

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	KdPrint(("irp name:%s\n", pchIrpNames[pIOStack->MajorFunction]));

	Irp->IoStatus.Information = 0;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS Dispatch_BufferIOControl(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	//IO����
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulCtrlCode = pIOStack->Parameters.DeviceIoControl.IoControlCode;

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulRtnLen = 0;

	ULONG ulInBufLen = pIOStack->Parameters.DeviceIoControl.InputBufferLength;			//����buf�ĳ���
	ULONG ulOutBufLen = pIOStack->Parameters.DeviceIoControl.OutputBufferLength;		//���buf�ĳ���
	PCHAR pchInBuf = pIOStack->Parameters.DeviceIoControl.Type3InputBuffer;				//����buf
	PCHAR pchOutBuf = Irp->UserBuffer;													//���buf
	__try
	{
		switch (ulCtrlCode)
		{
		case IO_READ_CODE:				//��ȡ����
		{
			const char* pchBuf = "����һ���������ں˲���ַ���";
			if (ulOutBufLen >= strlen(pchBuf))
			{
				RtlCopyMemory(pchOutBuf, pchBuf, strlen(pchBuf));

				lNTStatus = STATUS_SUCCESS;
				ulRtnLen = strlen(pchBuf);
			}
			else
			{
				lNTStatus = STATUS_BUFFER_TOO_SMALL;
				ulRtnLen = 0;
			}
		}
		break;
		case IO_WRITE_CODE:				//д������
		{
			PCHAR pchBuf = ExAllocatePool(PagedPool, ulInBufLen + 1);			//����һ������Ļ������������ݣ���ֹ֮���ӡ����ʱ�����ʵ��Ƿ��ڴ�
			if (pchBuf == NULL)
			{
				lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
				ulRtnLen = 0;
			}
			else
			{
				RtlZeroMemory(pchBuf, ulInBufLen + 1);
				RtlCopyMemory(pchBuf, pchInBuf, ulInBufLen);

				KdPrint(("%s\n", pchBuf));

				lNTStatus = STATUS_SUCCESS;
				ulRtnLen = strlen(pchBuf);

				ExFreePool(pchBuf);
				pchBuf = NULL;
			}
		}
		break;
		case IO_QUERY_CODE:				//��ѯ����
		{
			KdPrint(("IO_QUERY_CODE\n"));
			lNTStatus = STATUS_SUCCESS;
			ulRtnLen = 4 * 1024;
		}
		break;
		default:
			break;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulRtnLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulRtnLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}