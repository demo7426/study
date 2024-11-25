/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.25
��  ��: �ں�ģʽ�µ��ַ�������
��  ע:	
�޸ļ�¼:

  1.  ����: 2024.11.25
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <ntddk.h>
#include <ntstrsafe.h>

/// <summary>
/// �ں��ַ�����ʼ������01
/// </summary>
/// <param name=""></param>
VOID Test01(VOID)
{
	UNICODE_STRING tUnicodeStr = { wcslen(L"unicode�ַ���") * 2, 1024, L"unicode�ַ���" };			//unicode�ַ���
	ANSI_STRING tAnsiStr = { strlen("ascll�ַ���"), 1024, "ascll�ַ���" };						//ascll�ַ���
	
	KdPrint(("%wZ\n", &tUnicodeStr));
	KdPrint(("%Z\n", &tAnsiStr));
}

/// <summary>
/// �ں��ַ�����ʼ��02
/// </summary>
/// <param name=""></param>
VOID Test02(VOID)
{
	UNICODE_STRING tSrcUnicodeStr;					//Դunicode�ַ���
	UNICODE_STRING tDesUnicodeStr;					//Ŀ��unicode�ַ���
	ANSI_STRING tSrcAnsiStr;						//Դascll�ַ���
	ANSI_STRING tDesAnsiStr;						//Ŀ��ascll�ַ���

	WCHAR wchBuf[1024] = { 0 };
	CHAR chBuf[1024] = { 0 };

	ULONG ulValue = 0;

	RtlInitUnicodeString(&tSrcUnicodeStr, L"unicode�ַ���");
	RtlInitAnsiString(&tSrcAnsiStr, "ascll�ַ���");

	KdPrint(("%wZ\n", &tSrcUnicodeStr));
	KdPrint(("%Z\n", &tSrcAnsiStr));

	//��ʼ��һ���յļ����ַ���
	RtlInitEmptyUnicodeString(&tDesUnicodeStr, wchBuf, sizeof(wchBuf));
	RtlInitEmptyAnsiString(&tDesAnsiStr, chBuf, sizeof(chBuf));

	//�ַ�������
	RtlCopyUnicodeString(&tDesUnicodeStr, &tSrcUnicodeStr);
	RtlCopyString(&tDesAnsiStr, &tSrcAnsiStr);

	KdPrint(("\n%wZ\n", &tSrcUnicodeStr));
	KdPrint(("%Z\n", &tSrcAnsiStr));

	//�ַ����Ƚ�
	if (!RtlCompareUnicodeString(&tDesUnicodeStr, &tSrcUnicodeStr, TRUE))
		KdPrint(("\ntDesUnicodeStrx=tSrcUnicodeStr\n"));

	if (!RtlCompareUnicodeString(&tDesAnsiStr, &tSrcAnsiStr, TRUE))
		KdPrint(("\nDesAnsiStr=tSrcAnsiStr\n"));

	//�ַ���ת��д
	RtlUpcaseUnicodeString(&tDesUnicodeStr, &tDesUnicodeStr, FALSE);
	RtlUpperString(&tDesAnsiStr, &tDesAnsiStr);

	KdPrint(("\n%wZ\n", &tDesUnicodeStr));
	KdPrint(("%Z\n", &tDesAnsiStr));

	//unicode�ַ�����������ֵ֮���ת��
	RtlInitUnicodeString(&tDesUnicodeStr, L"123");
	RtlUnicodeStringToInteger(&tDesUnicodeStr, 10, &ulValue);
	KdPrint(("\nulValue = %u\n", ulValue));

	RtlInitEmptyUnicodeString(&tDesUnicodeStr, wchBuf, sizeof(wchBuf));		//���UNICODE_STRING �ṹ̫С���޷����������ᵼ�²���ϵͳ����
	RtlIntegerToUnicodeString(456, 10, &tDesUnicodeStr);					
	KdPrint(("\n%wZ\n", &tDesUnicodeStr));

	//unicode�ַ�����ascll�ַ����໥ת��
	RtlInitUnicodeString(&tDesUnicodeStr, L"unicode�ַ���");
	RtlUnicodeStringToAnsiString(&tDesAnsiStr, &tDesUnicodeStr, TRUE);
	KdPrint(("\ntDesAnsiStr = %Z\n", &tDesAnsiStr));

	RtlInitAnsiString(&tDesAnsiStr, "ascll�ַ���");
	RtlAnsiStringToUnicodeString(&tDesUnicodeStr, &tDesAnsiStr, TRUE);
	KdPrint(("\ntDesUnicodeStr = %wZ\n", &tDesUnicodeStr));

	//��ʽ���ַ���
	RtlUnicodeStringPrintf(&tDesUnicodeStr, L"%d", 1);
	KdPrint(("\ntDesUnicodeStr = %wZ\n", &tDesUnicodeStr));
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

	Test01();

	KdPrint(("\n"));
	Test02();

	return lNTStatus;
}

