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

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode)
{


    WdfRequestComplete(Request, STATUS_SUCCESS);
}

