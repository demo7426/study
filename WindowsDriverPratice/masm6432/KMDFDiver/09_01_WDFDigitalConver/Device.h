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

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit);

#endif // !__DEVICE_H__



