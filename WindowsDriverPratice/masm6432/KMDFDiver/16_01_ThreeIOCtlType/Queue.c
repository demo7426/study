/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Queue.c
作  者:	钱锐      版本: V0.0.2     新建日期: 2025.01.12
描  述: 队列文件
备  注:
修改记录:

  1.  日期: 2025.01.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

  2.  日期: 2025.01.12
      作者: 钱锐
      内容:
          1) 新增其它IO控制交互模式；
      版本:V0.0.2

*************************************************/

#include "Queue.h"
#include "Device.h"
#include "Driver.h"

//读取注册表数字
VOID IOReadRegeditNum(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

//读取注册表布尔
VOID IOReadRegeditBoole(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

//读取注册表字符串
VOID IOReadRegeditString(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength);

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    switch (IoControlCode)
    {
    case IO_NUMCONVER_CODE:
    {   
        PDEVICE_CONTEXT ptDeviceContext = NULL;

        if (InputBufferLength < 1 || OutputBufferLength < 2)        //防止内存越界
        {
            KdPrint(("输入或输出缓冲区长度不足\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;  
        }

        //获取手动队列对象，并将请求添加到手动队列
        ptDeviceContext = GetDeviceContext(WdfIoQueueGetDevice(Queue));
        lNTStatus = WdfRequestForwardToIoQueue(Request, ptDeviceContext->Queue);
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("将请求添加到手动队列失败\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_UNSUCCESSFUL, 0);
        }

        //启动定时器
        WdfTimerStart(ptDeviceContext->Timer, WDF_REL_TIMEOUT_IN_SEC(3));
    }
    break;
    case IO_READ_REGEDIT_NUM_CODE:      //缓冲区方式交互数据
        IOReadRegeditNum(Request, OutputBufferLength, InputBufferLength);
        break;
    case IO_READ_REGEDIT_BOOLE_CODE:    //其它方式交互数据
        IOReadRegeditBoole(Request, OutputBufferLength, InputBufferLength);
        break;
    case IO_READ_REGEDIT_STRING_CODE:   //直接方式交互数据
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

    //取消请求
    WdfRequestCompleteWithInformation(Request, STATUS_CANCELLED, 0);

    //关停定时器
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

    {//手动完成请求
        PCHAR pchInBuf = NULL;                                      //输入缓冲区
        size_t unInBufLen = 0;                                      //输入缓冲区长度
        PCHAR pchOutBuf = NULL;                                     //输出缓冲区
        size_t unOutBufLen = 0;                                     //输出缓冲区长度
        const CHAR* pchNum = "零壹贰叁肆伍陆柒捌玖";
        CHAR chInNum = 0;

        lNTStatus = WdfRequestRetrieveInputBuffer(tWDFRequest, 1, &pchInBuf, &unInBufLen);              //获取输入缓冲区
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("获取输入缓冲区错误\n"));
            WdfRequestCompleteWithInformation(tWDFRequest, STATUS_INVALID_PARAMETER, 0);
        }

        chInNum = *pchInBuf;

        lNTStatus = WdfRequestRetrieveOutputBuffer(tWDFRequest, 2, &pchOutBuf, &unOutBufLen);          //获取输出缓冲区
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("获取输出缓冲区错误\n"));
            WdfRequestCompleteWithInformation(tWDFRequest, STATUS_INVALID_PARAMETER, 0);
        }

        RtlCopyMemory(pchOutBuf, &pchNum[(chInNum - '0') * 2], 2);

        WdfRequestCompleteWithInformation(tWDFRequest, STATUS_SUCCESS, unOutBufLen);
    }
}

VOID IOReadRegeditNum(_In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PCHAR pchInBuf = NULL;                                      //输入缓冲区
    size_t unInBufLen = 0;                                      //输入缓冲区长度
    PCHAR pchOutBuf = NULL;                                     //输出缓冲区
    size_t unOutBufLen = 0;                                     //输出缓冲区长度

    WDFDEVICE tWDFDevice = { 0 };
    WDFDRIVER tWDFDriver = { 0 };   
    PDRIVER_CONTEXT ptDriverContext = NULL;                     //驱动对象扩展

    tWDFDevice = WdfIoQueueGetDevice(WdfRequestGetIoQueue(Request));
    tWDFDriver = WdfDeviceGetDriver(tWDFDevice);

    ptDriverContext = GetDriverContext(tWDFDriver);

    lNTStatus = WdfRequestRetrieveOutputBuffer(Request, 4, &pchOutBuf, &unOutBufLen);          //获取输出缓冲区
    if (!NT_SUCCESS(lNTStatus) || unOutBufLen < 4)
    {
        KdPrint(("获取输出缓冲区错误\n"));
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
    PVOID pvOutBuf = NULL;          //输出缓冲区
    size_t unOutLen = 0;            //输出缓冲区长度

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
    PCHAR pchInBuf = NULL;                                      //输入缓冲区
    size_t unInBufLen = 0;                                      //输入缓冲区长度
    PCHAR pchOutBuf = NULL;                                     //输出缓冲区
    size_t unOutBufLen = 0;                                     //输出缓冲区长度

    WDFDEVICE tWDFDevice = { 0 };
    WDFDRIVER tWDFDriver = { 0 };
    PDRIVER_CONTEXT ptDriverContext = NULL;                     //驱动对象扩展
    size_t unMinRequiredSize = 0;

    tWDFDevice = WdfIoQueueGetDevice(WdfRequestGetIoQueue(Request));
    tWDFDriver = WdfDeviceGetDriver(tWDFDevice);

    ptDriverContext = GetDriverContext(tWDFDriver);

    unMinRequiredSize = wcslen(ptDriverContext->StrContent) * sizeof(WCHAR);

    lNTStatus = WdfRequestRetrieveOutputBuffer(Request, unMinRequiredSize, &pchOutBuf, &unOutBufLen);          //获取输出缓冲区
    if (!NT_SUCCESS(lNTStatus) || unOutBufLen < unMinRequiredSize)
    {
        KdPrint(("获取输出缓冲区错误\n"));
        WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
        return;
    }

    RtlCopyMemory(pchOutBuf, ptDriverContext->StrContent, unMinRequiredSize);

    WdfRequestCompleteWithInformation(Request, STATUS_SUCCESS, unMinRequiredSize);
}