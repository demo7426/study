/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Device.h
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.07
��  ��: �豸�ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <ntddk.h>
#include <wdf.h>

//�豸��������Ϣ�ṹ��
typedef struct _DEVICE_CONTEXT
{
    WDFTIMER Timer;
    WDFQUEUE Queue;
}DEVICE_CONTEXT, *PDEVICE_CONTEXT;

//������������Ϣ�ṹ��
typedef struct _REQUEST_CONTEXT
{
    WDFMEMORY WDFMemory;
}REQUEST_CONTEXT, * PREQUEST_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext)            //ͨ�� GetDeviceContext �������ɻ�ȡ�豸������

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(REQUEST_CONTEXT, GetRequestContext)          //ͨ�� GetRequestContext �������ɻ�ȡ����������

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit);

#endif // !__DEVICE_H__



