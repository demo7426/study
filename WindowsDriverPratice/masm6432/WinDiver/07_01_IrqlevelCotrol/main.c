/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.12.05
��  ��: ���ȼ���ȡ�����ã�������Ҳ��ı䵱ǰ�������ȼ�
��  ע:	1��	�ж��������ȼ�������32���ȼ�:
				HIGH_LEVEL--һ��Ϊ��Դģ��ʹ�õ����ȼ�
				......
				DISPATCH_LEVEL--�û������ȼ�
				APC_LEVEL--�û������ȼ�
				PASSIVE_LEVEL--�û�������ȼ����û���ĳ���һ�㶼���ڸò㼶��
			KeGetCurrentIrql--��ȡ��ǰ���̵����ȼ�
			KeRaiseIrql--������ǰ���̵����ȼ���ָ�������ȼ�
			KeLowerIrql--���͵�ǰ���̵����ȼ�

		2��	KeInitializeSpinLock--��ʼ��������
			KeAcquireSpinLock--��ȡ������
			KeAcquireSpinLock--�ͷ�������
�޸ļ�¼:

  1.  ����: 2024.12.05
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// ��ӡ��ǰ���̵����ȼ�
/// </summary>
/// <param name=""></param>
VOID PrintCurIrlLevel(VOID)
{
	switch (KeGetCurrentIrql())
	{
	case DISPATCH_LEVEL:
		KdPrint(("DISPATCH_LEVEL\n"));
		break;
	case APC_LEVEL:
		KdPrint(("APC_LEVEL\n"));
		break;
	case PASSIVE_LEVEL:
		KdPrint(("PASSIVE_LEVEL\n"));
		break;
	default:
		break;
	}
}

/// <summary>
/// ����������
/// </summary>
/// <param name=""></param>
VOID SpinLockTest01(VOID)
{
	KIRQL uchIrql;
	KSPIN_LOCK ulSpinLock;

	KdPrint(("����������:\n"));

	KeInitializeSpinLock(&ulSpinLock);
	PrintCurIrlLevel();

	KeAcquireSpinLock(&ulSpinLock, &uchIrql);			//��ȡ���������󣬻�����֮������ȼ�ֱ���ͷ������������Է�ֹ������ͬһʱ�̱��������
	PrintCurIrlLevel();

	KeReleaseSpinLock(&ulSpinLock, uchIrql);
	PrintCurIrlLevel();
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	KIRQL uchIrql;

	DriverObject->DriverUnload = DriverUnload;
	KdPrint(("�������سɹ�\n"));

	PrintCurIrlLevel();

	KeRaiseIrql(DISPATCH_LEVEL, &uchIrql);
	PrintCurIrlLevel();

	KeLowerIrql(uchIrql);
	PrintCurIrlLevel();

	SpinLockTest01();

	return STATUS_SUCCESS;
}