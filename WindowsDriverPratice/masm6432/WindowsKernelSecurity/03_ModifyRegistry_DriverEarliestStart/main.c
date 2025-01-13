/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.13
��  ��: ͨ���޸�ע���ķ�ʽ��ʵ����������������
��  ע: ���Է���:
        1�����뽫.sys�ļ������� C:\Windows\System32\drivers Ŀ¼��
        2����ʹ�� KmdManager��exe��������ʱ����ʹ�� System32\drivers\03_ModifyRegistry_DriverEarliestStart.sys ����
        3��HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\services\03_ModifyRegistry_DriverEarliestStart �½�Start��ֵ�޸�Ϊ 1��2�����һ���µ�Group����ֵΪSystem Reserved
        4��TODO:Start�������Ϊ0���޷�������������ؽ��м��أ����о�
�޸ļ�¼:

  1.  ����: 2025.01.13
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/


#include <ntddk.h>
//#include <wdf.h>

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

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    NTSTATUS lNTStatus = STATUS_SUCCESS;
    HANDLE hThread = { 0 };

    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("�������سɹ�\n"));

    PsCreateSystemThread(&hThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, Print_Routine, NULL);

    return lNTStatus;
}

