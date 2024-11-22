/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.22
��  ��: ֱ���ļ���ȡ��
		TODO:��ȡ�ļ�����ʱ����Mdl���ڴ�ӳ��Ϊ�յ�����������
��  ע:
�޸ļ�¼:

  1.  ����: 2024.11.22
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
}DEVICE_EXTENSION, * PDEVICE_EXTENSION;

/// <summary>
/// ��ǲ����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ֱ�Ӷ�ȡ����
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_DirectReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ֱ��д������
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_DirectWriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

/// <summary>
/// ֱ�Ӳ�ѯ�ļ���Ϣ
/// </summary>
/// <param name="DeviceObject"></param>
/// <param name="Irp"></param>
/// <returns></returns>
NTSTATUS Dispatch_DirectQueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	UNICODE_STRING tSymbolicLinkName = RTL_CONSTANT_STRING(L"\\GLOBAL??\\HelloDDK");
	PDEVICE_EXTENSION pDeviceEx = NULL;			//�豸��չ

	pDeviceEx = DriverObject->DeviceObject->DeviceExtension;

	//�ͷ���Դ����ֹ�ڴ�й¶
	pDeviceEx&& pDeviceEx->Buffer ? ExFreePool(pDeviceEx->Buffer) : 0;

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

	ptDeviceObject->Flags |= DO_DIRECT_IO;						//����ֱ�Ӷ�ȡ��ʽ,���û��ռ��ڴ�ӳ�䵽�ں˿ռ䣬��д�ں˿ռ伴���޸ĵ��û��ռ������
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
	DriverObject->MajorFunction[IRP_MJ_READ] = Dispatch_DirectReadData;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = Dispatch_DirectWriteData;
	DriverObject->MajorFunction[IRP_MJ_QUERY_INFORMATION] = Dispatch_DirectQueryFile;

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

NTSTATUS Dispatch_DirectReadData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulMdlByteCount = 0;					//�ܳ���
	ULONG ulMdlOffset = 0;						//ƫ��
	PVOID pvUserVirAddr = NULL;					//�û��ռ仺������ʼ��ַ
	PVOID pvSystemVirAddr = NULL;				//�ں˿ռ仺������ʼ��ַ

	ULONG ulReadLen = 0;

	__try 
	{
		//ֱ�Ӷ�ȡ����
		ulMdlByteCount = MmGetMdlByteCount(Irp->MdlAddress);
		ulMdlOffset = MmGetMdlByteOffset(Irp->MdlAddress);
		pvUserVirAddr = MmGetMdlBaseVa(Irp->MdlAddress);

		KdPrint(("Dispatch_DirectReadData: ByteCount=%u, Offset=%u, UserVirAddr=0x%p\n", ulMdlByteCount, ulMdlOffset, pvUserVirAddr));

		pvSystemVirAddr = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority);

		if (pIOStack->Parameters.Read.Length <= ulMdlByteCount)
		{
			RtlCopyMemory(pvSystemVirAddr, "����һ���������ں˵��ַ���", strlen("����һ���������ں˵��ַ���"));

			lNTStatus = STATUS_SUCCESS;
			ulReadLen = strlen("����һ���������ں˵��ַ���");
		}
		else
		{
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
			ulReadLen = 0;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulReadLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulReadLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_DirectWriteData(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulMdlByteCount = 0;					//�ܳ���
	ULONG ulMdlOffset = 0;						//ƫ��
	PVOID pvUserVirAddr = NULL;					//�û��ռ仺������ʼ��ַ
	PVOID pvSystemVirAddr = NULL;				//�ں˿ռ仺������ʼ��ַ

	ULONG ulWriteLen = 0;

	__try
	{
		//ֱ�Ӷ�ȡ����
		ulMdlByteCount = MmGetMdlByteCount(Irp->MdlAddress);
		ulMdlOffset = MmGetMdlByteOffset(Irp->MdlAddress);
		pvUserVirAddr = MmGetMdlBaseVa(Irp->MdlAddress);

		KdPrint(("Dispatch_DirectWriteData: ByteCount=%u, Offset=%u, UserVirAddr=0x%p\n", ulMdlByteCount, ulMdlOffset, pvUserVirAddr));

		pvSystemVirAddr = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority);

		if (pIOStack->Parameters.Write.Length <= ulMdlByteCount)
		{
			KdPrint(("Dispatch_DirectWriteData: %s", (char*)pvSystemVirAddr));

			lNTStatus = STATUS_SUCCESS;
			ulWriteLen = pIOStack->Parameters.Write.Length;
		}
		else
		{
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
			ulWriteLen = 0;
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		lNTStatus = GetExceptionCode();
		ulWriteLen = 0;
	}

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = ulWriteLen;

	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

NTSTATUS Dispatch_DirectQueryFile(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	PIO_STACK_LOCATION pIOStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG ulMdlByteCount = 0;					//�ܳ���
	ULONG ulMdlOffset = 0;						//ƫ��
	PVOID pvUserVirAddr = NULL;					//�û��ռ仺������ʼ��ַ
	PVOID pvSystemVirAddr = NULL;				//�ں˿ռ仺������ʼ��ַ

	ULONG ulRtnLen = 0;

	__try
	{
		if (!Irp->MdlAddress)
			KdPrint(("Dispatch_DirectQueryFile: MdlAddress is null\n"));
	
		//ֱ�Ӷ�ȡ����
		ulMdlByteCount = MmGetMdlByteCount(Irp->MdlAddress);
		ulMdlOffset = MmGetMdlByteOffset(Irp->MdlAddress);
		pvUserVirAddr = MmGetMdlBaseVa(Irp->MdlAddress);

		KdPrint(("Dispatch_DirectQueryFile: ByteCount=%u, Offset=%u, UserVirAddr=0x%p\n", ulMdlByteCount, ulMdlOffset, pvUserVirAddr));

		pvSystemVirAddr = MmGetSystemAddressForMdlSafe(Irp->MdlAddress, NormalPagePriority);

		if (pvSystemVirAddr && pIOStack->Parameters.QueryFile.FileInformationClass == FileStandardInformation &&
			pIOStack->Parameters.QueryFile.Length >= sizeof(FILE_STANDARD_INFORMATION))
		{
			PFILE_STANDARD_INFORMATION pFileStandInfo = (PFILE_STANDARD_INFORMATION)pvSystemVirAddr;

			pFileStandInfo->EndOfFile.LowPart = 4 * 1024;

			lNTStatus = STATUS_SUCCESS;
			ulRtnLen = pFileStandInfo->EndOfFile.LowPart;
		}
		else
		{
			lNTStatus = STATUS_INSUFFICIENT_RESOURCES;
			ulRtnLen = 0;
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