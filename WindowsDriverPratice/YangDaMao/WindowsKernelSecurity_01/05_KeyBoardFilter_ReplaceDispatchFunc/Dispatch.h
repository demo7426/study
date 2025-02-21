/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Dispatch.h
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


#ifndef __DISPATCH_H__
#define __DISPATCH_H__

#include <wdm.h>

//��Ӧ���������滻ǰ����ǲ����ָ��
typedef NTSTATUS (*Dispatch_Read_FuncType)(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Pnp(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Power(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Write(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

NTSTATUS Dispatch_Read(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp);

Dispatch_Read_FuncType g_pfOld_Dispatch_Read;

#endif // !__DISPATCH_H__

