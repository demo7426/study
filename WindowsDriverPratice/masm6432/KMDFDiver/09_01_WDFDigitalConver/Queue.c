/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Queue.c
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

#include "Queue.h"

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_NUMCONVER_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//����ת��

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    switch (IoControlCode)
    {
    case IO_NUMCONVER_CODE:
    {   
        PCHAR pchInBuf = NULL;                                      //���뻺����
        size_t unInBufLen = 0;                                      //���뻺��������
        PCHAR pchOutBuf = NULL;                                     //���������
        size_t unOutBufLen = 0;                                     //�������������
        const CHAR* pchNum = "��Ҽ��������½��ƾ�";
        CHAR chInNum = 0;

        if (InputBufferLength < 1 || OutputBufferLength < 2)        //��ֹ�ڴ�Խ��
        {
            KdPrint(("�����������������Ȳ���\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;  
        }

        lNTStatus = WdfRequestRetrieveInputBuffer(Request, InputBufferLength, &pchInBuf, &unInBufLen);              //��ȡ���뻺����
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("��ȡ���뻺��������\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;
        }

        chInNum = *pchInBuf;

        lNTStatus = WdfRequestRetrieveOutputBuffer(Request, OutputBufferLength, &pchOutBuf, &unOutBufLen);          //��ȡ���������
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("��ȡ������������\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;
        }

        RtlCopyMemory(pchOutBuf, &pchNum[(chInNum - '0') * 2], 2);

        WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, unOutBufLen);
    }
    break;
    default:
        WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
        break;
    }
}

