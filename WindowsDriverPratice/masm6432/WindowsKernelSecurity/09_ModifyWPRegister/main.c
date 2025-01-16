/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.16
��  ��: �޸�д�����Ĵ���;
��  ע: Ĭ��д����Ϊ1,������״̬;0--�ر�д����;1--����д����;
�޸ļ�¼:

  1.  ����: 2025.01.16
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾��
	  �汾:V0.0.1

*************************************************/

#include <ntddk.h>
#include <wdf.h>
#include <intrin.h>

//�ر�д����
KIRQL WPOff(VOID)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();		//Ӳ�����ȼ���ߵ� IRQL = DISPATCH_LEVEL���Ӷ����ε�ǰ�������ϵ�Ч����� IRQL ���жϡ�
	ULONG_PTR ulCr0  = __readcr0();

	//д�����Ĵ�������
#ifdef _X86_
	ulCr0 &= ~0x00010000;
#else
	ulCr0 &= ~0x0000000000010000;
#endif // _X86_

	_disable();									//�����ж�
	__writecr0(ulCr0);

	return tKIrqL;
}

//����д����
VOID WPOn(KIRQL _KIrqL)
{
	KIRQL tKIrqL = KeRaiseIrqlToDpcLevel();
	ULONG_PTR ulCr0 = __readcr0();

	ulCr0 |= 0x10000;							//д�����Ĵ�����1

	_enable();									//�����ж�
	__writecr0(ulCr0);

	KeLowerIrql(_KIrqL);
}

VOID Test01(VOID)
{
	const SIZE_T unBufSize = 1024;				//��������С
	PCHAR pchBuf00, pchBuf01;

	pchBuf00 = (PCHAR)ExAllocatePool(NonPagedPool, unBufSize);		//��Ϊ��Ӳ�����ȼ���ߵ� IRQL = DISPATCH_LEVEL�ˣ�����ʹ�÷�ҳ�ڴ棬����ϵͳ��������
	if (!pchBuf00)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return;
	}

	pchBuf01 = (PCHAR)ExAllocatePool(NonPagedPool, unBufSize);
	if (!pchBuf01)
	{
		KdPrint(("ExAllocatePool is err\n"));
		return;
	}

	RtlZeroMemory(pchBuf00, unBufSize);
	RtlCopyMemory(pchBuf00, "�Ƿ�ҳ�ڴ��е�һ���ַ�������", strlen("�Ƿ�ҳ�ڴ��е�һ���ַ�������"));

	RtlZeroMemory(pchBuf01, unBufSize);
	RtlCopyMemory(pchBuf01, pchBuf00, strlen(pchBuf00));		//���������ַ������ݿ���������Ƿ�ҳ�ڴ���

	KdPrint(("pchBuf00 = %s\n", pchBuf00));
	KdPrint(("pchBuf01 = %s\n", pchBuf01));

	ExFreePool(pchBuf00);
	ExFreePool(pchBuf01);

	pchBuf00 = NULL;
	pchBuf01 = NULL;
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

	KIRQL tKIrqL = WPOff();			//�ر�д�������������ߵ�ǰ��Ӳ�����ȼ�����������ʹ��hook����

	Test01();

	WPOn(tKIrqL);					//����д���������ҽ��͵�ǰ��Ӳ�����ȼ�

	return lNTStatus;
}


