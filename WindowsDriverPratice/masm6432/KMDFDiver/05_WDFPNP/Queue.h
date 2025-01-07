/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Queue.h
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.07
��  ��: �����ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <ntddk.h>
#include <wdf.h>

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode);

#endif // !__QUEUE_H__
