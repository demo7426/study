/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Queue.c
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

#include "Queue.h"
#include "Device.h"
#include "Driver.h"

//��ȡע�������
VOID IOReadRegeditNum(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

//��ȡע�����
VOID IOReadRegeditBoole(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

//��ȡע����ַ���
VOID IOReadRegeditString(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

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
    case IO_READ_REGEDIT_NUM_CODE:      //��������ʽ��������
        IOReadRegeditNum(Request, OutputBufferLength, InputBufferLength);
        break;
    case IO_READ_REGEDIT_BOOLE_CODE:    //������ʽ��������
        IOReadRegeditBoole(Request, OutputBufferLength, InputBufferLength);
        break;
    case IO_READ_REGEDIT_STRING_CODE:   //ֱ�ӷ�ʽ��������
        IOReadRegeditString(Request, OutputBufferLength, InputBufferLength);
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
            KdPrint(("��ȡ�������������\n"));
            WdfRequestCompleteWithInformation(tWDFRequest, STATUS_INVALID_PARAMETER, 0);
        }

        RtlCopyMemory(pchOutBuf, &pchNum[(chInNum - '0') * 2], 2);

        WdfRequestCompleteWithInformation(tWDFRequest, STATUS_SUCCESS, unOutBufLen);
    }
}

VOID IOReadRegeditNum(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PCHAR pchInBuf = NULL;                                      //���뻺����
    size_t unInBufLen = 0;                                      //���뻺��������
    PCHAR pchOutBuf = NULL;                                     //���������
    size_t unOutBufLen = 0;                                     //�������������

    WDFDEVICE tWDFDevice = { 0 };
    WDFDRIVER tWDFDriver = { 0 };   
    PDRIVER_CONTEXT ptDriverContext = NULL;                     //����������չ

    tWDFDevice = WdfIoQueueGetDevice(WdfRequestGetIoQueue(Request));
    tWDFDriver = WdfDeviceGetDriver(tWDFDevice);

    ptDriverContext = GetDriverContext(tWDFDriver);

    lNTStatus = WdfRequestRetrieveOutputBuffer(Request, 4, &pchOutBuf, &unOutBufLen);          //��ȡ���������
    if (!NT_SUCCESS(lNTStatus) || unOutBufLen < 4)
    {
        KdPrint(("��ȡ�������������\n"));
        WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
        return;
    }

    RtlCopyMemory(pchOutBuf, &ptDriverContext->Num, sizeof ptDriverContext->Num);

    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, sizeof ptDriverContext->Num);
}

VOID IOReadRegeditBoole(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDRIVER_CONTEXT ptDriverContext = NULL;
    PREQUEST_CONTEXT ptRequestContext = NULL;
    WDFDRIVER tWDFDriver = { 0 };
    WDFDEVICE tWDFDevice = { 0 };
    PVOID pvOutBuf = NULL;          //���������
    size_t unOutLen = 0;            //�������������

    tWDFDevice = WdfIoQueueGetDevice(WdfRequestGetIoQueue(Request));
    tWDFDriver = WdfDeviceGetDriver(tWDFDevice);
    ptDriverContext = GetDriverContext(tWDFDriver);

    ptRequestContext = GetRequestContext(Request);
    if (OutputBufferLength >= sizeof(ULONG))
    {
        pvOutBuf = WdfMemoryGetBuffer(ptRequestContext->WDFMemory, &unOutLen);
        if (!pvOutBuf)
        {
            WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
            return;
        }

        *(PULONG)pvOutBuf = ptDriverContext->Boole;
        WdfRequestComplete(Request, STATUS_SUCCESS);
    }
    else
    {
        WdfRequestComplete(Request, STATUS_INVALID_PARAMETER);
    }
}

VOID IOReadRegeditString(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PCHAR pchInBuf = NULL;                                      //���뻺����
    size_t unInBufLen = 0;                                      //���뻺��������
    PCHAR pchOutBuf = NULL;                                     //���������
    size_t unOutBufLen = 0;                                     //�������������

    WDFDEVICE tWDFDevice = { 0 };
    WDFDRIVER tWDFDriver = { 0 };
    PDRIVER_CONTEXT ptDriverContext = NULL;                     //����������չ
    size_t unMinRequiredSize = 0;

    tWDFDevice = WdfIoQueueGetDevice(WdfRequestGetIoQueue(Request));
    tWDFDriver = WdfDeviceGetDriver(tWDFDevice);

    ptDriverContext = GetDriverContext(tWDFDriver);

    unMinRequiredSize = wcslen(ptDriverContext->StrContent) * sizeof(WCHAR);

    lNTStatus = WdfRequestRetrieveOutputBuffer(Request, unMinRequiredSize, &pchOutBuf, &unOutBufLen);          //��ȡ���������
    if (!NT_SUCCESS(lNTStatus) || unOutBufLen < unMinRequiredSize)
    {
        KdPrint(("��ȡ�������������\n"));
        WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
        return;
    }

    RtlCopyMemory(pchOutBuf, ptDriverContext->StrContent, unMinRequiredSize);

    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, unMinRequiredSize);
}