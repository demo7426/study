/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Device.c
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

#include <initguid.h>

#include "Device.h"
#include "Queue.h"

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

//创建一个定时器
NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device);

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDFDEVICE tWDFDevice = { 0 };
    UNICODE_STRING tDevInterfaceName;
    WDF_IO_QUEUE_CONFIG tWDFIOQueueConfig = { 0 };
    WDFQUEUE tWDFQueue = { 0 };

    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    PDEVICE_CONTEXT ptDevContext = NULL;            //上下文对象

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DEVICE_CONTEXT);  //增加上下文对象的创建属性
    tWDFObjAttr.SynchronizationScope = WdfSynchronizationScopeDevice;       //设置为同步范围进行完成，保证定时器能够及时结束应用层的request请求

    lNTStatus = WdfDeviceCreate(&DeviceInit, &tWDFObjAttr, &tWDFDevice);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备创建失败\n"));
        return lNTStatus;
    }

    //获取上下文对象，并且创建定时器
    ptDevContext = GetDeviceContext(tWDFDevice);
    lNTStatus = MyCreateTimer(&ptDevContext->Timer, tWDFDevice);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("定时器创建失败\n"));
        return lNTStatus;
    }

    //必须使用WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE函数初始化，否则会导致应用层IO调用失败
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&tWDFIOQueueConfig, WdfIoQueueDispatchSequential);
    tWDFIOQueueConfig.EvtIoDeviceControl = EVT_WDF_IO_Queue_IO_Device_Control;

    lNTStatus = WdfIoQueueCreate(tWDFDevice, &tWDFIOQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &tWDFQueue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("队列创建失败\n"));
        return lNTStatus;
    }

    //创建手动请求完成队列
    WDF_IO_QUEUE_CONFIG_INIT(&tWDFIOQueueConfig, WdfIoQueueDispatchManual);
    tWDFIOQueueConfig.EvtIoCanceledOnQueue = EVT_WDF_IO_QUEUE_IO_Canceled_On_Queue;     //详细调用时机，请参考MSDN文档

    lNTStatus = WdfIoQueueCreate(tWDFDevice, &tWDFIOQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &ptDevContext->Queue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("手动队列创建失败\n"));
        return lNTStatus;
    }

    lNTStatus = WdfDeviceCreateDeviceInterface(tWDFDevice, &INTERFACEGUID, NULL);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备接口文件创建失败\n"));
        return lNTStatus;
    }

    KdPrint(("设备接口文件创建成功\n"));

    return lNTStatus;
}

NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_TIMER_CONFIG tWDF_Timer_Config = { 0 };     //定时器配置对象
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };      //WDF对象属性

    WDF_TIMER_CONFIG_INIT(&tWDF_Timer_Config, EVT_WDF_Timer);   //设置定时器的定时回调函数
    
    WDF_OBJECT_ATTRIBUTES_INIT(&tWDFObjAttr);
    tWDFObjAttr.ParentObject = _Device;             //将定时器挂到对应的设备上

    lNTStatus = WdfTimerCreate(&tWDF_Timer_Config, &tWDFObjAttr, _pTimer);

    return lNTStatus;
}



