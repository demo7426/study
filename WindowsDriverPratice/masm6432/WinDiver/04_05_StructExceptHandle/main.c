/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.16
��  ��: �ṹ���쳣����
��  ע: 1�������쳣:
			__try{
			}
			__except (EXCEPTION_EXECUTE_HANDLER){
			}
		2��֧��ִ��ָ������������
			__try{
			}
			__finally{
			}
		3����⡢�׳��쳣
			ProbeForRead(pchBuf, 1, 4);						//����Ӧ�ڴ������Ƿ�ɶ������ɶ����׳��쳣
			ProbeForWrite(pchBuf, 1, 4);					//����Ӧ�ڴ������Ƿ��д������д���׳��쳣
			ExRaiseStatus(STATUS_ACCESS_VIOLATION);			//�׳�ָ���쳣
			ExRaiseAccessViolation();						//�׳��ڴ����������쳣
			ExRaiseDatatypeMisalignment();					//�׳��ֽ�δ������쳣
�޸ļ�¼:

  1.  ����: 2024.11.16
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// �����׳����쳣
/// </summary>
/// <param name=""></param>
VOID TryExcept(VOID)
{
	PCHAR pchBuf = 0x80000000;
	__try
	{
		//*pchBuf = 1;
		//ProbeForRead(pchBuf, 1, 4);					//����Ӧ�ڴ������Ƿ�ɶ������ɶ����׳��쳣
		//ProbeForWrite(pchBuf, 1, 4);					//����Ӧ�ڴ������Ƿ��д������д���׳��쳣
		//ExRaiseStatus(STATUS_ACCESS_VIOLATION);		//�׳�ָ���쳣
		//ExRaiseAccessViolation();						//�׳��ڴ����������쳣
		ExRaiseDatatypeMisalignment();					//�׳��ֽ�δ������쳣
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint(("%d\n", GetExceptionCode()));
	}
}

/// <summary>
/// ֧��ִ��ָ������������
/// </summary>
/// <param name=""></param>
VOID TryFinnal(VOID)
{
	PCHAR pchBuf = NULL;
	__try
	{
		KdPrint(("__try\n"));
		__leave;
	}
	__finally
	{
		KdPrint(("__finally\n"));
		return;
	}

	KdPrint(("TryFinnal is end\n"));
}

VOID DiverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("����ж�سɹ�\n"));
}


NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{

	DriverObject->DriverUnload = DiverUnload;

	TryExcept();

	KdPrint(("\n"));
	TryFinnal();

	KdPrint(("�������سɹ�\n"));
	return STATUS_SUCCESS;
}

