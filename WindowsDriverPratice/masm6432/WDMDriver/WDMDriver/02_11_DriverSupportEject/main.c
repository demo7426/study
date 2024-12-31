/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2024.12.31
��  ��: ����֧�ֵ����������豸��Դ����
��  ע:
�޸ļ�¼:

  1.  ����: 2024.12.31
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <initguid.h>
#include <stdlib.h>

DEFINE_GUID(INTERFACEGUID,
    0xA33317FD, 0xA262, 0x4E2E, 0xAB, 0x0F, 0x22, 0x8D, 0xC7, 0xDF, 0xF4, 0xAB);

typedef struct _DEVICE_EXTENSION_INFO
{
    PDEVICE_OBJECT pFDO;                            //�ϲ�ҵ������
    PDEVICE_OBJECT pPDO;                            //������������
    UNICODE_STRING SysbolicName;
}DEVICE_EXTENSION_INFO, * PDEVICE_EXTENSION_INFO;

//��ӡ��Ӧ��Ӳ����Դ��Ϣ
VOID PrintPhysicalResource(PCM_PARTIAL_RESOURCE_LIST _pCM_ParResList)
{
    for (size_t i = 0; i < _pCM_ParResList->Count; i++)
    {
        switch (_pCM_ParResList->PartialDescriptors[i].Type)
        {
        case CmResourceTypePort:
            KdPrint(("�˿�:��ʼ��ַ:0x%llx, ����:0x%x\n", _pCM_ParResList->PartialDescriptors[i].u.Port.Start.QuadPart,
                _pCM_ParResList->PartialDescriptors[i].u.Port.Length));
            break;
        case CmResourceTypeInterrupt:
#ifdef _X86_
            KdPrint(("�ж�:level:%u, Vector:%u, Affinity:%u\n", _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Level,
                _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Vector, _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Affinity));
#else
            KdPrint(("�ж�:level:%u, Vector:%u, Affinity:%llu\n", _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Level,
                _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Vector, _pCM_ParResList->PartialDescriptors[i].u.Interrupt.Affinity));
#endif // _X86_
            break;
        case CmResourceTypeMemory:
            KdPrint(("�ڴ�:��ʼ��ַ:0x%llx, ����:0x%x\n", _pCM_ParResList->PartialDescriptors[i].u.Memory.Start.QuadPart,
                _pCM_ParResList->PartialDescriptors[i].u.Memory.Length));
            break;
        case CmResourceTypeDma:
            KdPrint(("DMA:ͨ��:%u, �˿�:%u\n", _pCM_ParResList->PartialDescriptors[i].u.Dma.Channel,
                _pCM_ParResList->PartialDescriptors[i].u.Dma.Port));
            break;
        case CmResourceTypeDevicePrivate:
            KdPrint(("˽������:%u %u %u\n", _pCM_ParResList->PartialDescriptors[i].u.DevicePrivate.Data[0],
                _pCM_ParResList->PartialDescriptors[i].u.DevicePrivate.Data[1],
                _pCM_ParResList->PartialDescriptors[i].u.DevicePrivate.Data[2]));
            break;
        default:
            KdPrint(("Ӳ����Դ����Ч��Ϣ: %03d\n", _pCM_ParResList->PartialDescriptors[i].Type));
            break;
        }
    }
}

NTSTATUS IO_Completion_Rountine(_In_ PDEVICE_OBJECT DeviceObject, _In_ PIRP Irp, _In_reads_opt_(_Inexpressible_("varies")) PVOID Context)
{
    PKEVENT ptKEvent = (PKEVENT)Context;

    KeSetEvent(ptKEvent, IO_NO_INCREMENT, FALSE);

    return STATUS_MORE_PROCESSING_REQUIRED;
}

//�ȵ�Ӳ������ִ�����
NTSTATUS ForwardAndWait(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;
    KEVENT tKEvent;

    KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);
    IoCopyCurrentIrpStackLocationToNext(Irp);
    IoSetCompletionRoutine(Irp, IO_Completion_Rountine, &tKEvent, TRUE, TRUE, TRUE);

    lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);

    KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);

    return lNTStatus;
}

NTSTATUS PNP_Default(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;

    IoSkipCurrentIrpStackLocation(Irp);
    lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);

    return lNTStatus;
}

NTSTATUS PNP_RemoveDevice(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;

    IoSkipCurrentIrpStackLocation(Irp);
    lNTStatus = IoCallDriver(ptDevExtenInfo->pPDO, Irp);
    IoDetachDevice(ptDevExtenInfo->pPDO);

    IoDeleteDevice(ptDevExtenInfo->pFDO);
    IoSetDeviceInterfaceState(&ptDevExtenInfo->SysbolicName, FALSE);

    return lNTStatus;
}

NTSTATUS PNP_Start_Device(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PIO_STACK_LOCATION ptIOStack = NULL;
    PCM_PARTIAL_RESOURCE_LIST ptCM_ParResList_Raw = NULL;           //Ӳ��ԭʼ��Ϣ
    PCM_PARTIAL_RESOURCE_LIST ptCM_ParResList_translate = NULL;     //Ӳ����������Ϣ

    lNTStatus = ForwardAndWait(DeviceObject, Irp);                  //��ȡӲ�����ߵ���Ϣ�����ҽ���
    if (!NT_SUCCESS(lNTStatus))
    {
        Irp->IoStatus.Status = lNTStatus;
        Irp->IoStatus.Information = 0;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
        return lNTStatus;
    }

    ptIOStack = IoGetCurrentIrpStackLocation(Irp);
    ptCM_ParResList_Raw = &ptIOStack->Parameters.StartDevice.AllocatedResources->List[0].PartialResourceList;
    if (ptCM_ParResList_Raw)
    {
        KdPrint(("ԭʼ������Ϣ:\n"));
        PrintPhysicalResource(ptCM_ParResList_Raw);
    }

    ptCM_ParResList_translate = &ptIOStack->Parameters.StartDevice.AllocatedResourcesTranslated->List[0].PartialResourceList;
    if (ptCM_ParResList_translate)
    {
        KdPrint(("�����������Ϣ:\n"));
        PrintPhysicalResource(ptCM_ParResList_translate);
    }

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS PNP_Query_Capabilities(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PIO_STACK_LOCATION ptIOStack = NULL;
    PCM_PARTIAL_RESOURCE_LIST ptCM_ParResList_Raw = NULL;           //Ӳ��ԭʼ��Ϣ
    PCM_PARTIAL_RESOURCE_LIST ptCM_ParResList_translate = NULL;     //Ӳ����������Ϣ
    PDEVICE_CAPABILITIES ptDevCapabilities = NULL;

    lNTStatus = ForwardAndWait(DeviceObject, Irp);                  //��ȡӲ�����ߵ���Ϣ�����ҽ���
    if (!NT_SUCCESS(lNTStatus))
    {
        Irp->IoStatus.Status = lNTStatus;
        Irp->IoStatus.Information = 0;
        IoCompleteRequest(Irp, IO_NO_INCREMENT);
        return lNTStatus;
    }

    ptIOStack = IoGetCurrentIrpStackLocation(Irp);
    ptDevCapabilities = ptIOStack->Parameters.DeviceCapabilities.Capabilities;
    for (size_t i = PowerSystemWorking; i < PowerSystemMaximum; i++)
    {
        KdPrint(("�޸�ǰ��Դ״̬: %u, %d\n", i, ptDevCapabilities->DeviceState[i]));
    }

    ptDevCapabilities->DeviceState[PowerSystemWorking] = PowerDeviceD0;
    ptDevCapabilities->DeviceState[PowerSystemSleeping1] = PowerDeviceD3;
    ptDevCapabilities->DeviceState[PowerSystemSleeping2] = PowerDeviceD3;
    ptDevCapabilities->DeviceState[PowerSystemSleeping3] = PowerDeviceD3;
    ptDevCapabilities->DeviceState[PowerSystemHibernate] = PowerDeviceD3;
    ptDevCapabilities->DeviceState[PowerSystemShutdown] = PowerDeviceD3;

    ptDevCapabilities->Removable = TRUE;            //֧�ֿ��ֶ���������

    for (size_t i = PowerSystemWorking; i < PowerSystemMaximum; i++)
    {
        KdPrint(("�޸ĺ��Դ״̬: %u, %d\n", i, ptDevCapabilities->DeviceState[i]));
    }

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS Driver_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    Irp->IoStatus.Information = 0;
    Irp->IoStatus.Status = lNTStatus;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return lNTStatus;
}

NTSTATUS Driver_PNP_Dispatch(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION ptIOStack = IoGetCurrentIrpStackLocation(Irp);

    //PNP��������
    static char* pchMinorFuncName[] = {
        "IRP_MN_START_DEVICE                     ",
        "IRP_MN_QUERY_REMOVE_DEVICE              ",
        "IRP_MN_REMOVE_DEVICE                    ",
        "IRP_MN_CANCEL_REMOVE_DEVICE             ",
        "IRP_MN_STOP_DEVICE                      ",
        "IRP_MN_QUERY_STOP_DEVICE                ",
        "IRP_MN_CANCEL_STOP_DEVICE               ",
        "IRP_MN_QUERY_DEVICE_RELATIONS           ",
        "IRP_MN_QUERY_INTERFACE                  ",
        "IRP_MN_QUERY_CAPABILITIES               ",
        "IRP_MN_QUERY_RESOURCES                  ",
        "IRP_MN_QUERY_RESOURCE_REQUIREMENTS      ",
        "IRP_MN_QUERY_DEVICE_TEXT                ",
        "IRP_MN_FILTER_RESOURCE_REQUIREMENTS     ",
        "",
        "IRP_MN_READ_CONFIG                      ",
        "IRP_MN_WRITE_CONFIG                     ",
        "IRP_MN_EJECT                            ",
        "IRP_MN_SET_LOCK                         ",
        "IRP_MN_QUERY_ID                         ",
        "IRP_MN_QUERY_PNP_DEVICE_STATE           ",
        "IRP_MN_QUERY_BUS_INFORMATION            ",
        "IRP_MN_DEVICE_USAGE_NOTIFICATION        ",
        "IRP_MN_SURPRISE_REMOVAL                 "
    };

    static NTSTATUS(*PNP_Handle[])(_In_ struct _DEVICE_OBJECT* DeviceObject, _Inout_ struct _IRP* Irp) = {
        PNP_Default,                            // "IRP_MN_START_DEVICE                     "
        PNP_Default,                            // "IRP_MN_QUERY_REMOVE_DEVICE              "
        PNP_RemoveDevice,                       // "IRP_MN_REMOVE_DEVICE                    "
        PNP_Default,                            // "IRP_MN_CANCEL_REMOVE_DEVICE             "
        PNP_Default,                            // "IRP_MN_STOP_DEVICE                      "
        PNP_Default,                            // "IRP_MN_QUERY_STOP_DEVICE                "
        PNP_Default,                            // "IRP_MN_CANCEL_STOP_DEVICE               "
        PNP_Default,                            // "IRP_MN_QUERY_DEVICE_RELATIONS           "
        PNP_Default,                            // "IRP_MN_QUERY_INTERFACE                  "
        PNP_Query_Capabilities,                 // "IRP_MN_QUERY_CAPABILITIES               "
        PNP_Default,                            // "IRP_MN_QUERY_RESOURCES                  "
        PNP_Default,                            // "IRP_MN_QUERY_RESOURCE_REQUIREMENTS      "
        PNP_Default,                            // "IRP_MN_QUERY_DEVICE_TEXT                "
        PNP_Default,                            // "IRP_MN_FILTER_RESOURCE_REQUIREMENTS     "
        PNP_Default,                            // "",
        PNP_Default,                            // "IRP_MN_READ_CONFIG                      "
        PNP_Default,                            // "IRP_MN_WRITE_CONFIG                     "
        PNP_Default,                            // "IRP_MN_EJECT                            "
        PNP_Default,                            // "IRP_MN_SET_LOCK                         "
        PNP_Default,                            // "IRP_MN_QUERY_ID                         "
        PNP_Default,                            // "IRP_MN_QUERY_PNP_DEVICE_STATE           "
        PNP_Default,                            // "IRP_MN_QUERY_BUS_INFORMATION            "
        PNP_Default,                            // "IRP_MN_DEVICE_USAGE_NOTIFICATION        "
        PNP_Default                             // "IRP_MN_SURPRISE_REMOVAL                 "
    };

    if (ptIOStack->MinorFunction >= _countof(pchMinorFuncName))
        lNTStatus = PNP_Default(DeviceObject, Irp);                                 //����������������ķ���ֵ������ᵼ��ϵͳ����
    else
    {
        KdPrint(("%s\n", pchMinorFuncName[ptIOStack->MinorFunction]));
        lNTStatus = PNP_Handle[ptIOStack->MinorFunction](DeviceObject, Irp);        //����������������ķ���ֵ������ᵼ��ϵͳ����
    }

    return lNTStatus;
}

NTSTATUS Driver_AddDevice(_In_ struct _DRIVER_OBJECT* DriverObject, _In_ struct _DEVICE_OBJECT* PhysicalDeviceObject)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    UNICODE_STRING tDevName = RTL_CONSTANT_STRING(L"\\Device\\HelloWDM");
    UNICODE_STRING tSysbolicName = RTL_CONSTANT_STRING(L"\\??\\HelloWDM");
    PDEVICE_OBJECT ptDevObj = NULL;
    PDEVICE_EXTENSION_INFO ptDevExtenInfo = NULL;

    lNTStatus = IoCreateDevice(DriverObject, sizeof(DEVICE_EXTENSION_INFO), NULL, FILE_DEVICE_UNKNOWN, FILE_AUTOGENERATED_DEVICE_NAME, FALSE, &ptDevObj);
    if (!NT_SUCCESS(lNTStatus))
    {
        KdPrint(("�����豸�ļ�ʧ��\n"));
        return lNTStatus;
    }

    ptDevExtenInfo = ptDevObj->DeviceExtension;
    ptDevExtenInfo->pFDO = ptDevObj;
    ptDevExtenInfo->pPDO = IoAttachDeviceToDeviceStack(ptDevObj, PhysicalDeviceObject);
    if (ptDevExtenInfo->pPDO == NULL)
    {
        IoDeleteDevice(ptDevObj);
        return STATUS_UNSUCCESSFUL;
    }

    //�����豸�ӿڣ��������ӣ�
    IoRegisterDeviceInterface(ptDevExtenInfo->pPDO, &INTERFACEGUID, NULL, &ptDevExtenInfo->SysbolicName);
    KdPrint(("%wZ\n", &ptDevExtenInfo->SysbolicName));
    IoSetDeviceInterfaceState(&ptDevExtenInfo->SysbolicName, TRUE);

    ptDevObj->Flags |= DO_BUFFERED_IO | DO_POWER_PAGABLE;
    ptDevObj->Flags &= ~DO_DEVICE_INITIALIZING;

    return lNTStatus;
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    for (size_t i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
    {
        DriverObject->MajorFunction[i] = Driver_Dispatch;
    }

    DriverObject->MajorFunction[IRP_MJ_PNP] = Driver_PNP_Dispatch;
    DriverObject->DriverExtension->AddDevice = Driver_AddDevice;

    KdPrint(("�������سɹ�\n"));

    return lNTStatus;
}




