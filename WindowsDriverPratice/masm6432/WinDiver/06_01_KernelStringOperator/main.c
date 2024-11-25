/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.25
描  述: 内核模式下的字符串操作
备  注:	
修改记录:

  1.  日期: 2024.11.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <ntddk.h>
#include <ntstrsafe.h>

/// <summary>
/// 内核字符串初始化操作01
/// </summary>
/// <param name=""></param>
VOID Test01(VOID)
{
	UNICODE_STRING tUnicodeStr = { wcslen(L"unicode字符串") * 2, 1024, L"unicode字符串" };			//unicode字符串
	ANSI_STRING tAnsiStr = { strlen("ascll字符串"), 1024, "ascll字符串" };						//ascll字符串
	
	KdPrint(("%wZ\n", &tUnicodeStr));
	KdPrint(("%Z\n", &tAnsiStr));
}

/// <summary>
/// 内核字符串初始化02
/// </summary>
/// <param name=""></param>
VOID Test02(VOID)
{
	UNICODE_STRING tSrcUnicodeStr;					//源unicode字符串
	UNICODE_STRING tDesUnicodeStr;					//目的unicode字符串
	ANSI_STRING tSrcAnsiStr;						//源ascll字符串
	ANSI_STRING tDesAnsiStr;						//目的ascll字符串

	WCHAR wchBuf[1024] = { 0 };
	CHAR chBuf[1024] = { 0 };

	ULONG ulValue = 0;

	RtlInitUnicodeString(&tSrcUnicodeStr, L"unicode字符串");
	RtlInitAnsiString(&tSrcAnsiStr, "ascll字符串");

	KdPrint(("%wZ\n", &tSrcUnicodeStr));
	KdPrint(("%Z\n", &tSrcAnsiStr));

	//初始化一个空的计数字符串
	RtlInitEmptyUnicodeString(&tDesUnicodeStr, wchBuf, sizeof(wchBuf));
	RtlInitEmptyAnsiString(&tDesAnsiStr, chBuf, sizeof(chBuf));

	//字符串拷贝
	RtlCopyUnicodeString(&tDesUnicodeStr, &tSrcUnicodeStr);
	RtlCopyString(&tDesAnsiStr, &tSrcAnsiStr);

	KdPrint(("\n%wZ\n", &tSrcUnicodeStr));
	KdPrint(("%Z\n", &tSrcAnsiStr));

	//字符串比较
	if (!RtlCompareUnicodeString(&tDesUnicodeStr, &tSrcUnicodeStr, TRUE))
		KdPrint(("\ntDesUnicodeStrx=tSrcUnicodeStr\n"));

	if (!RtlCompareUnicodeString(&tDesAnsiStr, &tSrcAnsiStr, TRUE))
		KdPrint(("\nDesAnsiStr=tSrcAnsiStr\n"));

	//字符串转大写
	RtlUpcaseUnicodeString(&tDesUnicodeStr, &tDesUnicodeStr, FALSE);
	RtlUpperString(&tDesAnsiStr, &tDesAnsiStr);

	KdPrint(("\n%wZ\n", &tDesUnicodeStr));
	KdPrint(("%Z\n", &tDesAnsiStr));

	//unicode字符串与整型数值之间的转换
	RtlInitUnicodeString(&tDesUnicodeStr, L"123");
	RtlUnicodeStringToInteger(&tDesUnicodeStr, 10, &ulValue);
	KdPrint(("\nulValue = %u\n", ulValue));

	RtlInitEmptyUnicodeString(&tDesUnicodeStr, wchBuf, sizeof(wchBuf));		//如果UNICODE_STRING 结构太小，无法保存结果，会导致操作系统崩溃
	RtlIntegerToUnicodeString(456, 10, &tDesUnicodeStr);					
	KdPrint(("\n%wZ\n", &tDesUnicodeStr));

	//unicode字符串与ascll字符串相互转换
	RtlInitUnicodeString(&tDesUnicodeStr, L"unicode字符串");
	RtlUnicodeStringToAnsiString(&tDesAnsiStr, &tDesUnicodeStr, TRUE);
	KdPrint(("\ntDesAnsiStr = %Z\n", &tDesAnsiStr));

	RtlInitAnsiString(&tDesAnsiStr, "ascll字符串");
	RtlAnsiStringToUnicodeString(&tDesUnicodeStr, &tDesAnsiStr, TRUE);
	KdPrint(("\ntDesUnicodeStr = %wZ\n", &tDesUnicodeStr));

	//格式化字符串
	RtlUnicodeStringPrintf(&tDesUnicodeStr, L"%d", 1);
	KdPrint(("\ntDesUnicodeStr = %wZ\n", &tDesUnicodeStr));
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	NTSTATUS lNTStatus = STATUS_SUCCESS;


	DriverObject->DriverUnload = DriverUnload;

	KdPrint(("驱动加载成功\n"));

	Test01();

	KdPrint(("\n"));
	Test02();

	return lNTStatus;
}

