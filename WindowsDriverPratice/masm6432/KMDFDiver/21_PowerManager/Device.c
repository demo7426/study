/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Device.c
��  ��:	Ǯ��      �汾: V0.0.3     �½�����: 2025.01.07
��  ��: �豸�ļ�
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

  3.  ����: 2025.01.13
      ����: Ǯ��
      ����:
          1) ������Դ����
      �汾:V0.0.3

*************************************************/

#include <initguid.h>

#include "Device.h"
#include "Queue.h"

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

//����һ����ʱ��
NTSTATUS MyCreateTimer(IN WDFTIMER* _pTimer, IN WDFDEVICE _Device);

//�ڸú���ץȡ������IO����ģʽ�µ��û����̿ռ䣬���ҽ��ý��̿ռ�����
VOID EVT_WDF_IO_IN_Caller_Context(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request);

//PNPӲ������ʱ�Ļص�����
NTSTATUS EVT_WDF_Device_Prepare_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesRaw, _In_ WDFCMRESLIST ResourcesTranslated);

//PNPӲ��ж�ػص�����
NTSTATUS EVT_WDF_Device_Relase_Handware(_In_ WDFDEVICE Device, _In_ WDFCMRESLIST ResourcesTranslated);

//��Դ�������
NTSTATUS EvtDeviceD0Entry(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState);

//��Դ�˳�����
NTSTATUS EvtDeviceD0Exit(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE TargetState);

//ʹ���ж�
NTSTATUS EvtDeviceD0EntryPostInterruptsEnabled(_In_ WDFDEVICE Device, _In_ WDF_POWER_DEVICE_STATE PreviousState);

//ȡ��ʹ���ж�
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
    PDEVICE_CONTEXT ptDevContext = NULL;            //�����Ķ���

    WDF_PNPPOWER_EVENT_CALLBACKS tWDFPNPPowerCallBacks = { 0 };

    WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS tWDFDevPowerPolicyIdleSettings = { 0 };       //��Դ����

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, DEVICE_CONTEXT);  //���������Ķ���Ĵ�������
    tWDFObjAttr.SynchronizationScope = WdfSynchronizationScopeDevice;       //����Ϊͬ����Χ������ɣ���֤��ʱ���ܹ���ʱ����Ӧ�ò��request����

    //PNP����
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
   
    WdfDeviceInitSetIoInCallerContextCallback(DeviceInit, EVT_WDF_IO_IN_Caller_Context);   //IO������������������Ϣ֮ǰ���� EVT_WDF_IO_IN_Caller_Context ����
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

    //IdleCannotWakeFromS0 ��ʾ�޷��ӵ͹���ģʽֱ�ӻ��ѣ�����ͨ��ϵͳ������������������������ѣ���������Ӧ�ⲿ���ڲ��Ļ����¼���
    WDF_DEVICE_POWER_POLICY_IDLE_SETTINGS_INIT(&tWDFDevPowerPolicyIdleSettings, IdleCannotWakeFromS0);  
    tWDFDevPowerPolicyIdleSettings.IdleTimeout = 10 * 1000;                             //����û�л�Ծʱ����ʱ֮����仯Ϊ����״̬����λΪ:ms

    WdfDeviceAssignS0IdleSettings(tWDFDevice, &tWDFDevPowerPolicyIdleSettings);         //���õ�Դ����

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

VOID EVT_WDF_IO_IN_Caller_Context(_In_ WDFDEVICE Device, _In_ WDFREQUEST Request)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    WDF_REQUEST_PARAMETERS tWDFRequsetParam = { 0 };
    PVOID pvOutputBuf = NULL;
    size_t unOutputBufLen = 0;
    WDF_OBJECT_ATTRIBUTES tWDFObjAttr = { 0 };
    PREQUEST_CONTEXT ptRequestContext = NULL;

    WDF_REQUEST_PARAMETERS_INIT(&tWDFRequsetParam);             //�����ʼ��������ᵼ�³�������
    
    WdfRequestGetParameters(Request, &tWDFRequsetParam);

    //����� IO IO_READ_REGEDIT_BOOLE_CODE���Ƶ����
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

    //�������������ʽIO���ƴ���Ļ�������Ϣ
    lNTStatus = WdfRequestRetrieveUnsafeUserOutputBuffer(Request, 0, &pvOutputBuf, &unOutputBufLen);
    if (!NT_SUCCESS(lNTStatus) || !pvOutputBuf || unOutputBufLen < 1)
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    //Ϊ������������Ŀռ�
    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&tWDFObjAttr, REQUEST_CONTEXT);
    lNTStatus = WdfObjectAllocateContext(Request, &tWDFObjAttr, &ptRequestContext);
    if (!NT_SUCCESS(lNTStatus))
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    //��֤ I/O ������û�ģʽ�������Ƿ��д��Ȼ�������������������ڴ�ҳ���Ա����������ջ�е������������д�뻺������
    lNTStatus = WdfRequestProbeAndLockUserBufferForWrite(Request, pvOutputBuf, unOutputBufLen, &ptRequestContext->WDFMemory);
    if (!NT_SUCCESS(lNTStatus))
    {
        WdfRequestComplete(Request, lNTStatus);
        return;
    }

    lNTStatus = WdfDeviceEnqueueRequest(Device, Request);       //�� Request ������� Device ����
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










