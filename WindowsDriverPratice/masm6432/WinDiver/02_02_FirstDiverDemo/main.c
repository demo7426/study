/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.12
��  ��: ʵ��һ��windows ������demo
��  ע:
		1�����������ķ���
		ֱ�����ɼ���

		2�����������ķ���
		ʹ�ù���ԱȨ�޴�cmd�նˣ�ʹ��
			sc create �����Զ������� binpath= ·�� type= kernel
			net start �����Զ�������								//��������
			net stop �����Զ�������								//ж������
			sc delete �����Զ�������								//ɾ������
�޸ļ�¼:

  1.  ����: 2024.11.12
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

void Unload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("Good bye Driver\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	KdPrint(("Hello Driver\n"));

	DriverObject->DriverUnload = Unload;

	return STATUS_SUCCESS;
}
