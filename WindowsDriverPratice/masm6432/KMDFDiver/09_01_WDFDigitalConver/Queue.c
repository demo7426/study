/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Queue.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.07
描  述: 队列文件
备  注:
修改记录:

  1.  日期: 2025.01.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include "Queue.h"

//Function 需要从 0x800 开始，前面的被内核系统占用
#define IO_NUMCONVER_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//数字转换

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    switch (IoControlCode)
    {
    case IO_NUMCONVER_CODE:
    {   
        PCHAR pchInBuf = NULL;                                      //输入缓冲区
        size_t unInBufLen = 0;                                      //输入缓冲区长度
        PCHAR pchOutBuf = NULL;                                     //输出缓冲区
        size_t unOutBufLen = 0;                                     //输出缓冲区长度
        const CHAR* pchNum = "零壹贰叁肆伍陆柒捌玖";
        CHAR chInNum = 0;

        if (InputBufferLength < 1 || OutputBufferLength < 2)        //防止内存越界
        {
            KdPrint(("输入或输出缓冲区长度不足\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;  
        }

        lNTStatus = WdfRequestRetrieveInputBuffer(Request, InputBufferLength, &pchInBuf, &unInBufLen);              //获取输入缓冲区
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("获取输入缓冲区错误\n"));
            WdfRequestCompleteWithInformation(Request, STATUS_INVALID_PARAMETER, 0);
            break;
        }

        chInNum = *pchInBuf;

        lNTStatus = WdfRequestRetrieveOutputBuffer(Request, OutputBufferLength, &pchOutBuf, &unOutBufLen);          //获取输出缓冲区
        if (!NT_SUCCESS(lNTStatus))
        {
            KdPrint(("获取出缓冲区错误\n"));
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

