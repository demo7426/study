/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.23
��  ��: ö���豸ջ�ϵ��豸����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.23
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntifs.h>
#include <ntddk.h>

#ifdef __cplusplus
extern "C"
{
#endif  __cplusplus
NTSYSAPI NTSTATUS NTAPI ObReferenceObjectByName(IN PUNICODE_STRING ObjectName,
		IN ULONG Attributes,
		IN PACCESS_STATE AccessState OPTIONAL,
		IN ACCESS_MASK DesiredAccess OPTIONAL,
		IN POBJECT_TYPE ObjectType,
		IN KPROCESSOR_MODE AccessMode,
		IN OUT PVOID ParseContext OPTIONAL,
		OUT PVOID* Object);

extern POBJECT_TYPE* IoDeviceObjectType;
extern POBJECT_TYPE* IoDriverObjectType;
#ifdef __cplusplus
}
#endif __cplusplus

VOID GetDeviceInfo(PDEVICE_OBJECT _pCurDevObj)
{
	PDEVICE_OBJECT ptCurDevObj = NULL;			//��ǰ�豸����
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	ULONG uLen = 0;
	POBJECT_NAME_INFORMATION ptObjNameInfo = (POBJECT_NAME_INFORMATION)ExAllocatePool(PagedPool, 1024);
	if (!ptObjNameInfo)
	{
		KdPrint(("GetDeviceInfo ExAllocatePool is err.\n"));
		return;
	}

	ptCurDevObj = _pCurDevObj;

	while (ptCurDevObj)
	{
		lNTStatus = ObQueryNameString(ptCurDevObj, ptObjNameInfo, 1024, &uLen);
		if (!NT_SUCCESS(lNTStatus))
			break;

		KdPrint(("��������%p:%wZ\t\t�豸����%p:%wZ\n", ptCurDevObj->DriverObject, &ptCurDevObj->DriverObject->DriverName, ptCurDevObj, &ptObjNameInfo->Name));
		
		ptCurDevObj = ptCurDevObj->AttachedDevice;		//��ȡ���ϲ��豸����
	} 

	ExFreePool(ptObjNameInfo);
	ptObjNameInfo = NULL;
}

/// <summary>
/// ö���豸ջ�ϵ��豸����
/// </summary>
/// <param name=""></param>
VOID EnumDeviceStack_DevObj(VOID)
{
	UNICODE_STRING tDriverName = RTL_CONSTANT_STRING(L"\\Driver\\ACPI");
	PDRIVER_OBJECT ptDriverObj = NULL;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptCurDevObj = NULL;			//��ǰ�豸����

	lNTStatus = ObReferenceObjectByName(&tDriverName, OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE, NULL, FILE_ANY_ACCESS, *IoDriverObjectType, KernelMode, NULL, &ptDriverObj);
	if (!NT_SUCCESS(lNTStatus))
	{
		KdPrint(("ObReferenceObjectByName is err.\n"));
		KdPrint(("0x%x\n", lNTStatus));
		return;
	}

	ptCurDevObj = ptDriverObj->DeviceObject;
	while (ptCurDevObj)
	{
		GetDeviceInfo(ptCurDevObj);
		ptCurDevObj = ptCurDevObj->NextDevice;
	}

	ObDereferenceObject(ptDriverObj);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	EnumDeviceStack_DevObj();

	return STATUS_SUCCESS;
}


