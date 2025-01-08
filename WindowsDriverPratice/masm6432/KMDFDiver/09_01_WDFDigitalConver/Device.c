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

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDFDEVICE tWDFDevice = { 0 };
    UNICODE_STRING tDevInterfaceName;
    WDF_IO_QUEUE_CONFIG tWDFIOQueueConfig = { 0 };
    WDFQUEUE tWDFQueue = { 0 };

    lNTStatus = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &tWDFDevice);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备创建失败\n"));
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

    lNTStatus = WdfDeviceCreateDeviceInterface(tWDFDevice, &INTERFACEGUID, NULL);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("设备接口文件创建失败\n"));
        return lNTStatus;
    }

    KdPrint(("设备接口文件创建成功\n"));

    return lNTStatus;
}

