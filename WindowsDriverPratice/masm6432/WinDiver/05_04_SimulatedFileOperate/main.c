/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.21
��  ��: ģ���ļ�����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.21
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

#define MAX_BUF_LEN 4 * 1024			//��󻺳�������

/// <summary>
/// �豸��չ
/// </summary>
typedef struct _DEVICE_EXTENSION
{
	PCHAR Buffer;						//��������ʼ��ַ
	UINT32 SumLen;						//�������ܳ���
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;

/// <summary>
/// ��ǲ����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ��ȡ����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_ReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// д������
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_WriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ��ѯ�ļ���Ϣ
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_QueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	pDeviceEx = DriverObject->DeviceObject->DeviceExtension;

	//�ͷ���Դ����ֹ�ڴ�й¶
	pDeviceEx && pDeviceEx->Buffer ? ExFreePool(pDeviceEx->Buffer) : 0;

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
	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	lNTStatus = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION), &tDeviceName, FILE_DEVICE_UNKNOWN, 0, FALSE, &ptDeviceObject);		//���һ�����������Ӧ���Ƕ���ָ��
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�����豸�ļ�ʧ��\n"));
		return lNTStatus;
	}

	ptDeviceObject->Flags |= DO_BUFFERED_IO;					//���� DO_BUFFERED_IO ��־
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
	DriverObject->MajorFunction[IRP_MJ_READ] = Dispatch_ReadData;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = Dispatch_WriteData;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = Dispatch_QueryFile;

	pDeviceEx = (PDEVICE_EXTENSION)ptDeviceObject->DeviceExtension;

	pDeviceEx->Buffer = (PCHAR)ExAllocatePool(PagedPool, MAX_BUF_LEN);
	if (pDeviceEx->Buffer == NULL)
	{
		KdPrint(("ExAllocatePool Buffer is err\n"));
		IoDeleteDevice(ptDeviceObject);
		IoDeleteSymbolicLink(&tSymbolicLinkName);
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	pDeviceEx->SumLen = MAX_BUF_LEN;

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

NTSTATUS Dispatch_ReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulReadLen = 0;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	__try
	{
		ULONG ulOffset = pIOStack->Parameters.Read.ByteOffset.LowPart;
		
		ulReadLen = pIOStack->Parameters.Read.Length;
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
		
		if (ulReadLen + ulOffset > pDeviceEx->SumLen)
		{
			KdPrint(("��ȡ����������һ���ֲ��ڻ����ڣ�ʧ��\n"));
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			RtlCopyMemory(Irp->AssociatedIrp.SystemBuffer, pDeviceEx->Buffer + ulOffset, ulReadLen);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("��ȡ�����׳��쳣\n"));

		ulReadLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulReadLen;
	Irp->IoStatus.Status = lNTStatus;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_WriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG ulWriteLen = 0;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	__try
	{
		ULONG ulOffset = pIOStack->Parameters.Write.ByteOffset.LowPart;
		
		ulWriteLen = pIOStack->Parameters.Write.Length;
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;

		if (ulWriteLen + ulOffset > pDeviceEx->SumLen)
		{
			KdPrint(("д������������һ���ֲ��ڻ����ڣ�ʧ��\n"));
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			if (Irp->AssociatedIrp.SystemBuffer != NULL)
				RtlCopyMemory(pDeviceEx->Buffer + ulOffset, Irp->AssociatedIrp.SystemBuffer, ulWriteLen);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("д�������׳��쳣\n"));

		ulWriteLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulWriteLen;
	Irp->IoStatus.Status = lNTStatus;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_QueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG ulQueryLen = 0;

	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	__try
	{
		pDeviceEx = (PDEVICE_EXTENSION)DeviceObject->DeviceExtension;
		ulQueryLen = pIOStack->Parameters.QueryFile.Length;

		if (pIOStack->Parameters.QueryFile.FileInformationClass == FileStandardInformation &&
			ulQueryLen >= sizeof(FILE_STANDARD_INFORMATION))
		{
			PFILE_STANDARD_INFORMATION ptFileStandardInfo = (PFILE_STANDARD_INFORMATION)Irp->AssociatedIrp.SystemBuffer;

			ptFileStandardInfo->EndOfFile.LowPart = pDeviceEx->SumLen;

			ulQueryLen = sizeof(FILE_STANDARD_INFORMATION);
		}
		else
		{
			lNTStatus = STATUS_BUFFER_TOO_SMALL;
			ulQueryLen = 0;
		}

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("��ѯ�ļ��׳��쳣\n"));

		ulQueryLen = 0;
		lNTStatus = GetExceptionCode();
	}

	Irp->IoStatus.Information = ulQueryLen;
	Irp->IoStatus.Status = lNTStatus;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}
