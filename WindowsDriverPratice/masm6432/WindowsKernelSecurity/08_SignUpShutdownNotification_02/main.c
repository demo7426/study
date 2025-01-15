/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.15
��  ��: ʹ���Ѿ����ڵ��豸�ļ�������ע��ػ�֪ͨ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.15
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/


#include <ntddk.h>
#include <wdf.h>

/// <summary>
/// д�ļ�
/// </summary>
/// <param name=""></param>
/// <returns></returns>
NTSTATUS WriteFile(VOID)
{
	HANDLE handFile;
	OBJECT_ATTRIBUTES tObjAttr;
	UNICODE_STRING tUniStrFilePath = RTL_CONSTANT_STRING(L"\\??\\C:\\Shutdown01.log");
	IO_STATUS_BLOCK tIOStatus;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	CHAR chBuf[1024] = { 0 };
	FILE_POSITION_INFORMATION tFilePosInfo;

	InitializeObjectAttributes(&tObjAttr, &tUniStrFilePath, OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwCreateFile(&handFile,
		GENERIC_ALL,
		&tObjAttr,
		&tIOStatus,
		NULL,
		FILE_ATTRIBUTE_NORMAL,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		FILE_OPEN_IF,
		FILE_SYNCHRONOUS_IO_NONALERT,
		NULL,
		0
	);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("�ļ�����/��ʧ��\n"));
		return lNTStatus;
	}

	//���ļ�д������
	ZwWriteFile(handFile, NULL, NULL, NULL, &tIOStatus, "ϵͳ�ػ�ʱд�������", strlen("ϵͳ�ػ�ʱд�������"), NULL, NULL);

	ZwClose(handFile);

	return lNTStatus;
}

NTSTATUS Driver_Shutdown(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;

	WriteFile();

	Irp->IoStatus.Status = lNTStatus;
	Irp->IoStatus.Information = 0;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return lNTStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PFILE_OBJECT ptNullFileObj = NULL;
	PDEVICE_OBJECT ptNullDevObj = NULL;

	UNICODE_STRING tNullDevName = RTL_CONSTANT_STRING(L"\\Device\\Null");

	//DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = Driver_Shutdown;

	lNTStatus = IoGetDeviceObjectPointer(&tNullDevName, FILE_ANY_ACCESS, &ptNullFileObj, &ptNullDevObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("��ȡ�豸�ļ����ʧ��\n"));
		return lNTStatus;
	}

	ObDereferenceObject(ptNullFileObj);

	ptNullDevObj->DriverObject->MajorFunction[IRP_MJ_SHUTDOWN] = Driver_Shutdown;

	IoRegisterShutdownNotification(ptNullDevObj);										//��ָ�����豸ע��ػ�֪ͨ

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}

