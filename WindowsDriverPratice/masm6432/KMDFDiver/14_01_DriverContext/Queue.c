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
#include "Device.h"

//Function ��Ҫ�� 0x800 ��ʼ��ǰ��ı��ں�ϵͳռ��
#define IO_NUMCONVER_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//����ת��

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    switch (IoControlCode)
    {
    case IO_NUMCONVER_CODE:
    {   
        PDEVICE_CONTEXT ptDeviceContext = NULL;

        if (InputBufferLength < 1 || OutputBufferLength < 2)        //��ֹ�ڴ�Խ��
        {
            KdPrint(("�����������������Ȳ���\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;  
        }

        //��ȡ�ֶ����ж��󣬲���������ӵ��ֶ�����
        ptDeviceContext = GetDeviceContext(WdfIoQueueGetDevice(Queue));
        lNTStatus = WdfRequestForwardToIoQueue(Request, ptDeviceContext->Queue);
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("��������ӵ��ֶ�����ʧ��\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_UNSUCCESSFUL, 0);
        }

        //������ʱ��
        WdfTimerStart(ptDeviceContext->Timer, WDF_REL_TIMEOUT_IN_SEC(3));
    }
    break;
    default:
        WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
        break;
    }
}

VOID EVT_WDF_IO_QUEUE_IO_Canceled_On_Queue(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request)
{
    WDFDEVICE tWDFDevice = WdfIoQueueGetDevice(Queue);
    PDEVICE_CONTEXT ptDeviceContext = GetDeviceContext(tWDFDevice);

    //ȡ������
    WdfRequestCompleteWithInformation(Request, STATUS_CANCELLED, 0);

    //��ͣ��ʱ��
    WdfTimerStop(ptDeviceContext->Timer, FALSE);
}

VOID EVT_WDF_Timer(_In_ WDFTIMER Timer)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDFDEVICE tWDFDevice = { 0 };
    PDEVICE_CONTEXT ptDeviceContext = NULL;
    WDFREQUEST tWDFRequest = { 0 };

    tWDFDevice = WdfTimerGetParentObject(Timer);
    ptDeviceContext = GetDeviceContext(tWDFDevice);

    lNTStatus = WdfIoQueueRetrieveNextRequest(ptDeviceContext->Queue, &tWDFRequest);
    if (!NT_SUCCESS(tWDFRequest))
        return;

    {//�ֶ��������
        PCHAR pchInBuf = NULL;                                      //���뻺����
        size_t unInBufLen = 0;                                      //���뻺��������
        PCHAR pchOutBuf = NULL;                                     //���������
        size_t unOutBufLen = 0;                                     //�������������
        const CHAR* pchNum = "��Ҽ��������½��ƾ�";
        CHAR chInNum = 0;

        lNTStatus = WdfRequestRetrieveInputBuffer(tWDFRequest, 1, &pchInBuf, &unInBufLen);              //��ȡ���뻺����
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("��ȡ���뻺��������\n"));
            WdfRequestCompleteWithInformation(tWDFRequest, STATUS_INVALID_PARAMETER, 0);
        }

        chInNum = *pchInBuf;

        lNTStatus = WdfRequestRetrieveOutputBuffer(tWDFRequest, 2, &pchOutBuf, &unOutBufLen);          //��ȡ���������
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("��ȡ������������\n"));
            WdfRequestCompleteWithInformation(tWDFRequest, STATUS_INVALID_PARAMETER, 0);
        }

        RtlCopyMemory(pchOutBuf, &pchNum[(chInNum - '0') * 2], 2);

        WdfRequestCompleteWithInformation(tWDFRequest, STATUS_SUCCESS, unOutBufLen);
    }
}

