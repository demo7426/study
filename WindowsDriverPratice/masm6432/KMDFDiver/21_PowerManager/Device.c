/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Device.c
作  者:	钱锐      版本: V0.0.3     新建日期: 2025.01.07
描  述: 设备文件
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

  3.  日期: 2025.01.13
      作者: 钱锐
      内容:
          1) 新增电源管理；
      版本:V0.0.3

*************************************************/

#include <initguid.h>

#include "Device.h"
#include "Queue.h"

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

//创建一个定时器
NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device);

//在该函数抓取到其它IO控制模式下的用户进程空间，并且将该进程空间锁定
VOID EVT_WDF_IO_IN_Caller_Context(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request);

//PNP硬件加载时的回调函数
NTSTATUS EVT_WDF_Device_Prepare_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesRaw, _In_ WDFCMRESLIST ResourcesTranslated);

//PNP硬件卸载回调函数
NTSTATUS EVT_WDF_Device_Relase_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesTranslated);

//电源进入管理
NTSTATUS EvtDeviceD0Entry(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState);

//电源退出管理
NTSTATUS EvtDeviceD0Exit(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE TargetState);

//使能中断
NTSTATUS EvtDeviceD0EntryPostInterruptsEnabled(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState);

//取消使能中断
NTSTATUS EvtDeviceD0ExitPreInterruptsDisabled(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE TargetState);

NTSTATUS EvtDeviceSelfManagedIoInit(_In_ WDFDEVICE Device);

NTSTATUS EvtDeviceSelfManagedIoRestart(_In_ WDFDEVICE Device);

NTSTATUS EvtDeviceSelfManagedIoSuspend(_In_ WDFDEVICE Device);

NTSTATUS EvtDeviceSelfManagedIoFlush(_In_ WDFDEVICE Device);

NTSTATUS EvtDeviceSelfManagedIoCleanup(_In_ WDFDEVICE Device);

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDFDEVICE tWDFDevice = { 0 };
    UNICODE_STRING tDevInterfaceName;
    WDF_IO_QUEUE_CONFIG tWDFIOQueueConfig = { 0 };
    WDFQUEUE tWDFQueue = { 0 };

    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    PDEVICE_CONTEXT ptDevContext = NULL;            //上下文对象

    WDF_PNPPOWER_EVENT_CALLBACKS tWDFPNPPowerCallBacks = { 0 };

    WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS tWDFDevPowerPolicyIdleSettings = { 0 };       //电源策略

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DEVICE_CONTEXT);  //增加上下文对象的创建属性
    tWDFObjAttr.SynchronizationScope = WdfSynchronizationScopeDevice;       //设置为同步范围进行完成，保证定时器能够及时结束应用层的request请求

    //PNP处理
    WDF_PNPPOWER_EVENT_CALLBACKS_INIT(&tWDFPNPPowerCallBacks);

    //PNP hardware
    tWDFPNPPowerCallBacks.EvtDevicePrepareHardware = EVT_WDF_Device_Prepare_Handware;
    tWDFPNPPowerCallBacks.EvtDeviceReleaseHardware = EVT_WDF_Device_Relase_Handware;
    
    //PNP power
    tWDFPNPPowerCallBacks.EvtDeviceD0Entry = EvtDeviceD0Entry;
    tWDFPNPPowerCallBacks.EvtDeviceD0Exit = EvtDeviceD0Exit;
    tWDFPNPPowerCallBacks.EvtDeviceD0EntryPostInterruptsEnabled = EvtDeviceD0EntryPostInterruptsEnabled;
    tWDFPNPPowerCallBacks.EvtDeviceD0ExitPreInterruptsDisabled = EvtDeviceD0ExitPreInterruptsDisabled;
    
    //PNP self manager io
    tWDFPNPPowerCallBacks.EvtDeviceSelfManagedIoInit = EvtDeviceSelfManagedIoInit;
    tWDFPNPPowerCallBacks.EvtDeviceSelfManagedIoRestart = EvtDeviceSelfManagedIoRestart;
    tWDFPNPPowerCallBacks.EvtDeviceSelfManagedIoSuspend = EvtDeviceSelfManagedIoSuspend;
    tWDFPNPPowerCallBacks.EvtDeviceSelfManagedIoFlush = EvtDeviceSelfManagedIoFlush;
    tWDFPNPPowerCallBacks.EvtDeviceSelfManagedIoCleanup = EvtDeviceSelfManagedIoCleanup;
    
    WdfDeviceInitSetPnpPowerEventCallbacks(DeviceInit, &tWDFPNPPowerCallBacks);
   
    WdfDeviceInitSetIoInCallerContextCallback(DeviceInit, EVT_WDF_IO_IN_Caller_Context);   //IO管理器传递上下文信息之前调用 EVT_WDF_IO_IN_Caller_Context 函数
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

    //IdleCannotWakeFromS0 表示无法从低功耗模式直接唤醒，仅能通过系统或驱动程序的主动操作被唤醒，而不能响应外部或内部的唤醒事件。
    WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS_INIT(&tWDFDevPowerPolicyIdleSettings, IdleCannotWakeFromS0);  
    tWDFDevPowerPolicyIdleSettings.IdleTimeout = 10 * 1000;                             //驱动没有活跃时，超时之后则变化为空闲状态；单位为:ms

    WdfDeviceAssignS0IdleSettings(tWDFDevice, &tWDFDevPowerPolicyIdleSettings);         //设置电源策略

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

VOID EVT_WDF_IO_IN_Caller_Context(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_REQUEST_PARAMETERS tWDFRequsetParam = { 0 };
    PVOID pvOutputBuf = NULL;
    size_t unOutputBufLen = 0;
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    PREQUEST_CONTEXT ptRequestContext = NULL;

    WDF_REQUEST_PARAMETERS_INIT(&tWDFRequsetParam);             //必须初始化，否则会导致程序蓝屏
    
    WdfRequestGetParameters(Request, &tWDFRequsetParam);

    //处理非 IO IO_READ_REGEDIT_BOOLE_CODE控制的情况
    if (!(tWDFRequsetParam.Type == WdfRequestTypeDeviceControl && tWDFRequsetParam.Parameters.DeviceIoControl.IoControlCode == IO_READ_REGEDIT_BOOLE_CODE))
    {
        lNTStatus = WdfDeviceEnqueueRequest(Device, Request);
        if (!NT_SUCCESS(lNTStatus))
        {
            WdfRequestComplete(Request, lNTStatus);
            return;
        }
        return;
    }

    //检索输出其他方式IO控制传入的缓冲区信息
    lNTStatus = WdfRequestRetrieveUnsafeUserOutputBuffer(Request, 0, &pvOutputBuf, &unOutputBufLen);
    if (!NT_SUCCESS(lNTStatus) || !pvOutputBuf || unOutputBufLen < 1)
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    //为请求分配上下文空间
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, REQUEST_CONTEXT);
    lNTStatus = WdfObjectAllocateContext(Request, &tWDFObjAttr, &ptRequestContext);
    if (!NT_SUCCESS(lNTStatus))
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    //验证 I/O 请求的用户模式缓冲区是否可写，然后锁定缓冲区的物理内存页，以便驱动程序堆栈中的驱动程序可以写入缓冲区。
    lNTStatus = WdfRequestProbeAndLockUserBufferForWrite(Request, pvOutputBuf, unOutputBufLen, &ptRequestContext->WDFMemory);
    if (!NT_SUCCESS(lNTStatus))
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    lNTStatus = WdfDeviceEnqueueRequest(Device, Request);       //将 Request 请求加入 Device 队列
    if (!NT_SUCCESS(lNTStatus))
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    return;
}

NTSTATUS EVT_WDF_Device_Prepare_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesRaw, _In_ WDFCMRESLIST ResourcesTranslated)
{
    KdPrint(("EVT_WDF_Device_Prepare_Handware is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EVT_WDF_Device_Relase_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesTranslated)
{
    KdPrint(("EVT_WDF_Device_Relase_Handware is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0Entry(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState)
{
    static const char* pchPowerStateNames[] = {
        "WdfPowerDeviceInvalid                ",
        "WdfPowerDeviceD0                     ",
        "WdfPowerDeviceD1                     ",
        "WdfPowerDeviceD2                     ",
        "WdfPowerDeviceD3                     ",
        "WdfPowerDeviceD3Final                ",
        "WdfPowerDevicePrepareForHibernation  ",
        "WdfPowerDeviceMaximum                "
    };

    KdPrint(("EVT_WDF_DEVICE_D0_ENTRY is enter, previous power state:%s\n", pchPowerStateNames[PreviousState]));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0Exit(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE TargetState)
{
    static const char* pchPowerStateNames[] = {
    "WdfPowerDeviceInvalid                ",
    "WdfPowerDeviceD0                     ",
    "WdfPowerDeviceD1                     ",
    "WdfPowerDeviceD2                     ",
    "WdfPowerDeviceD3                     ",
    "WdfPowerDeviceD3Final                ",
    "WdfPowerDevicePrepareForHibernation  ",
    "WdfPowerDeviceMaximum                "
    };

    KdPrint(("EvtDeviceD0Exit is enter, target power state:%s\n", pchPowerStateNames[TargetState]));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0EntryPostInterruptsEnabled(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState)
{
    KdPrint(("EvtDeviceD0EntryPostInterruptsEnabled is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceD0ExitPreInterruptsDisabled(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE TargetState)
{
    KdPrint(("EvtDeviceD0ExitPreInterruptsDisabled is enter.\n"));

    return STATUS_SUCCESS;
}


NTSTATUS EvtDeviceSelfManagedIoInit(_In_ WDFDEVICE Device)
{
    KdPrint(("EvtDeviceSelfManagedIoInit is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceSelfManagedIoRestart(_In_ WDFDEVICE Device)
{
    KdPrint(("EvtDeviceSelfManagedIoRestart is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceSelfManagedIoSuspend(_In_ WDFDEVICE Device)
{
    KdPrint(("EvtDeviceSelfManagedIoSuspend is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceSelfManagedIoFlush(_In_ WDFDEVICE Device)
{
    KdPrint(("EvtDeviceSelfManagedIoFlush is enter.\n"));

    return STATUS_SUCCESS;
}

NTSTATUS EvtDeviceSelfManagedIoCleanup(_In_ WDFDEVICE Device)
{
    KdPrint(("EvtDeviceSelfManagedIoCleanup is enter.\n"));

    return STATUS_SUCCESS;
}










