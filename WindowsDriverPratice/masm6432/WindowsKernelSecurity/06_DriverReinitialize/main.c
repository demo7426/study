/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.15
��  ��: ���������³�ʼ��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.01.15
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/


#include <ntddk.h>
#include <wdf.h>

VOID Print_Routine(_In_ PVOID _pContext)
{
    LARGE_INTEGER tTimeout = RtlConvertLongToLargeInteger(-10 * 1000 * 500);            //�ӳ�ʱ��Ϊ500ms
    UINT32 unCounter = 0;                                                               //����

    while (TRUE)
    {
        KdPrint(("Print_Routine is runnig, unCounter = %u\n", unCounter++));

        KeDelayExecutionThread(KernelMode, FALSE, &tTimeout);
    }

}

//���������³�ʼ������
VOID Driver_Reinitialize(_In_ struct _DRIVER_OBJECT* DriverObject, _In_opt_ PVOID Context, _In_ ULONG Count)
{
    HANDLE hThread = { 0 };

    PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, Print_Routine, NULL);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;

    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("�������سɹ�\n"));

    //IoRegisterBootDriverReinitialization(DriverObject, Driver_Reinitialize, NULL);    //��������win7_sp1_x86����ϵͳ������Ч��������������³�ʼ������
    IoRegisterDriverReinitialization(DriverObject, Driver_Reinitialize, NULL);

    return lNTStatus;
}

