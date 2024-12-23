/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.23
描  述: 枚举设备栈上的设备对象
备  注:
修改记录:

  1.  日期: 2024.12.23
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

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
	PDEVICE_OBJECT ptCurDevObj = NULL;			//当前设备对象
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

		KdPrint(("驱动对象%p:%wZ\t\t设备对象%p:%wZ\n", ptCurDevObj->DriverObject, &ptCurDevObj->DriverObject->DriverName, ptCurDevObj, &ptObjNameInfo->Name));
		
		ptCurDevObj = ptCurDevObj->AttachedDevice;		//获取其上层设备对象
	} 

	ExFreePool(ptObjNameInfo);
	ptObjNameInfo = NULL;
}

/// <summary>
/// 枚举设备栈上的设备对象
/// </summary>
/// <param name=""></param>
VOID EnumDeviceStack_DevObj(VOID)
{
	UNICODE_STRING tDriverName = RTL_CONSTANT_STRING(L"\\Driver\\ACPI");
	PDRIVER_OBJECT ptDriverObj = NULL;
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	PDEVICE_OBJECT ptCurDevObj = NULL;			//当前设备对象

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
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	EnumDeviceStack_DevObj();

	return STATUS_SUCCESS;
}


