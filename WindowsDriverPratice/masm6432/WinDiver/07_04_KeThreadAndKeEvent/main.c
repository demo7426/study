/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.11
��  ��: �ں���ָ���ĳ����´����̣߳�ʹ���¼������߳�ͬ��
��  ע:	PsCreateSystemThread--�����߳�
		ZwOpenProcess--�򿪽��̶���ľ���������öԴ˶���ķ���Ȩ��
		PsGetProcessImageFileName--��ȡ��Ӧ���߳�����

		KeInitializeEvent--��ʼ���¼�
		KeWaitForSingleObject--�ȴ��¼�
		KeSetEvent--���¼���������Ϊ���ź�״̬
�޸ļ�¼:

  1.  ����: 2024.12.11
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

PCHAR PsGetProcessImageFileName(IN PEPROCESS Process);			//TODO:���������ںδ���

VOID ThreadProc(_In_ PVOID StartContext)
{
	KdPrint(("���̸߳���������: %s\n", PsGetProcessImageFileName(PsGetCurrentProcess())));		

	PsTerminateSystemThread(0);		//�����֪�ں��̴߳����￪ʼ������
}

VOID ThreadEvent(_In_ PVOID StartContext)
{
	PRKEVENT phandEvent = (PRKEVENT)StartContext;

	KdPrint(("ThreadEvent enter.\n"));

	KeSetEvent(phandEvent, IO_NO_INCREMENT, FALSE);

	KdPrint(("ThreadEvent quit.\n"));

	PsTerminateSystemThread(0);		//�����֪�ں��̴߳����￪ʼ������
}

/// <summary>
/// �ں��̴߳�������
/// </summary>
/// <param name=""></param>
VOID KeThread_Test01(VOID)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;
	HANDLE handThread;
	HANDLE handProcess;
	OBJECT_ATTRIBUTES tObjAttr;
	CLIENT_ID tClient_ID;

	PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadProc, NULL);

	//����� CLIENT_ID ȫ�������ݽ��г�ʼ������
	tClient_ID.UniqueProcess = (HANDLE)284;			//������PID�����Լ��Ĳ���ϵͳ�����������ѡ��һ�����ڵĽ���
	tClient_ID.UniqueThread = (HANDLE)0;				
	InitializeObjectAttributes(&tObjAttr, NULL, OBJ_KERNEL_HANDLE, NULL, NULL);

	lNTStatus = ZwOpenProcess(&handProcess, PROCESS_ALL_ACCESS, &tObjAttr, &tClient_ID);					//�򿪽��̶���ľ���������öԴ˶���ķ���Ȩ��
	if (NT_SUCCESS(lNTStatus))
	{
		PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, handProcess, NULL, ThreadProc, NULL);
	}
	else
	{
		KdPrint(("ZwOpenProcess is err. 0x%x\n", lNTStatus));
	}
	KdPrint(("KeThread_Test01 is end.\n"));
}

/// <summary>
/// ʹ���¼����߳̽�������ͬ��
/// </summary>
/// <param name=""></param>
VOID KeEvent_Test02(VOID)
{
	KEVENT tKEvent;
	HANDLE handThread;

	KeInitializeEvent(&tKEvent, NotificationEvent, FALSE);

	PsCreateSystemThread(&handThread, THREAD_ALL_ACCESS, NULL, NULL, NULL, ThreadEvent, &tKEvent);

	KeWaitForSingleObject(&tKEvent, Executive, KernelMode, FALSE, NULL);

	KdPrint(("KeEvent_Test02 quit.\n"));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("�������سɹ�\n"));

	KeThread_Test01();
	KeEvent_Test02();

	return STATUS_SUCCESS;
}



