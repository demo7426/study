/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Device.h
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.07
描  述: 设备文件
备  注:
修改记录:

  1.  日期: 2025.01.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <ntddk.h>
#include <wdf.h>

//设备上下文信息结构体
typedef struct _DEVICE_CONTEXT
{
    WDFTIMER Timer;
    WDFQUEUE Queue;
}DEVICE_CONTEXT, *PDEVICE_CONTEXT;

//请求上下文信息结构体
typedef struct _REQUEST_CONTEXT
{
    WDFMEMORY WDFMemory;
}REQUEST_CONTEXT, * PREQUEST_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext)            //通过 GetDeviceContext 函数即可获取设备上下文

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(REQUEST_CONTEXT, GetRequestContext)          //通过 GetRequestContext 函数即可获取请求上下文

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit);

#endif // !__DEVICE_H__



