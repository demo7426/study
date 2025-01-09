/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Device.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.07
��  ��: �豸�ļ�
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <initguid.h>

#include "Device.h"
#include "Queue.h"

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

//����һ����ʱ��
NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device);

NTSTATUS EVT_WDF_Driver_Device_Add(_In_ WDFDRIVER Driver, _Inout_ PWDFDEVICE_INIT DeviceInit)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDFDEVICE tWDFDevice = { 0 };
    UNICODE_STRING tDevInterfaceName;
    WDF_IO_QUEUE_CONFIG tWDFIOQueueConfig = { 0 };
    WDFQUEUE tWDFQueue = { 0 };

    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    PDEVICE_CONTEXT ptDevContext = NULL;            //�����Ķ���

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DEVICE_CONTEXT);  //���������Ķ���Ĵ�������
    tWDFObjAttr.SynchronizationScope = WdfSynchronizationScopeDevice;       //����Ϊͬ����Χ������ɣ���֤��ʱ���ܹ���ʱ����Ӧ�ò��request����

    lNTStatus = WdfDeviceCreate(&DeviceInit, &tWDFObjAttr, &tWDFDevice);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�豸����ʧ��\n"));
        return lNTStatus;
    }

    //��ȡ�����Ķ��󣬲��Ҵ�����ʱ��
    ptDevContext = GetDeviceContext(tWDFDevice);
    lNTStatus = MyCreateTimer(&ptDevContext->Timer, tWDFDevice);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("��ʱ������ʧ��\n"));
        return lNTStatus;
    }

    //����ʹ��WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE������ʼ��������ᵼ��Ӧ�ò�IO����ʧ��
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&tWDFIOQueueConfig, WdfIoQueueDispatchSequential);
    tWDFIOQueueConfig.EvtIoDeviceControl = EVT_WDF_IO_Queue_IO_Device_Control;

    lNTStatus = WdfIoQueueCreate(tWDFDevice, &tWDFIOQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &tWDFQueue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("���д���ʧ��\n"));
        return lNTStatus;
    }

    //�����ֶ�������ɶ���
    WDF_IO_QUEUE_CONFIG_INIT(&tWDFIOQueueConfig, WdfIoQueueDispatchManual);
    tWDFIOQueueConfig.EvtIoCanceledOnQueue = EVT_WDF_IO_QUEUE_IO_Canceled_On_Queue;     //��ϸ����ʱ������ο�MSDN�ĵ�

    lNTStatus = WdfIoQueueCreate(tWDFDevice, &tWDFIOQueueConfig, WDF_NO_OBJECT_ATTRIBUTES, &ptDevContext->Queue);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�ֶ����д���ʧ��\n"));
        return lNTStatus;
    }

    lNTStatus = WdfDeviceCreateDeviceInterface(tWDFDevice, &INTERFACEGUID, NULL);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�豸�ӿ��ļ�����ʧ��\n"));
        return lNTStatus;
    }

    KdPrint(("�豸�ӿ��ļ������ɹ�\n"));

    return lNTStatus;
}

NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_TIMER_CONFIG tWDF_Timer_Config = { 0 };     //��ʱ�����ö���
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };      //WDF��������

    WDF_TIMER_CONFIG_INIT(&tWDF_Timer_Config, EVT_WDF_Timer);   //���ö�ʱ���Ķ�ʱ�ص�����
    
    WDF_OBJECT_ATTRIBUTES_INIT(&tWDFObjAttr);
    tWDFObjAttr.ParentObject = _Device;             //����ʱ���ҵ���Ӧ���豸��

    lNTStatus = WdfTimerCreate(&tWDF_Timer_Config, &tWDFObjAttr, _pTimer);

    return lNTStatus;
}



