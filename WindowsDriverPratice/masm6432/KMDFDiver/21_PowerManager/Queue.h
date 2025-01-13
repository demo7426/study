/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Queue.h
��  ��:	Ǯ��      �汾: V0.0.2     �½�����: 2025.01.12
��  ��: �����ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

  2.  ����: 2025.01.12
      ����: Ǯ��
      ����:
          1) ��������IO���ƽ���ģʽ��
      �汾:V0.0.2

*************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <ntddk.h>
#include <wdf.h>

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_NUMCONVER_CODE	        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//����ת��
#define IO_READ_REGEDIT_NUM_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)			//��ȡע�������
#define IO_READ_REGEDIT_BOOLE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)			//��ȡע�����
#define IO_READ_REGEDIT_STRING_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)		//��ȡע����ַ���

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode);

VOID EVT_WDF_IO_QUEUE_IO_Canceled_On_Queue(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request);

/// <summary>
/// ���ڴ����ֶ����е�����
/// </summary>
/// <param name="Timer"></param>
VOID EVT_WDF_Timer(_In_ WDFTIMER Timer);

#endif // !__QUEUE_H__
