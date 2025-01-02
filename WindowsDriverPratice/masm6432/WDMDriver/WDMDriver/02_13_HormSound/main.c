/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.0.1     新建日期: 2025.01.01
描  述: IO端口操作
备  注: edx--端口地址
        al、ax、eax--端口读取出的数据暂存位置
修改记录:

  1.  日期: 2025.01.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

*************************************************/

#include <ntddk.h>

VOID Sound_On(INT32 _Freq)
{
    USHORT B = 1193180 / _Freq;
    UCHAR uchTemp = READ_PORT_UCHAR((PUCHAR)0x61);

    uchTemp |= 3;
    WRITE_PORT_UCHAR((PUCHAR)0x61, uchTemp);
    WRITE_PORT_UCHAR((PUCHAR)0x43, 0xb6);

    WRITE_PORT_UCHAR((PUCHAR)0x42, B & 0xff);
    WRITE_PORT_UCHAR((PUCHAR)0x43, (B >> 8) & 0xff);
}

VOID Sound_Off(VOID)
{
    UCHAR uchTemp = READ_PORT_UCHAR((PUCHAR)0x61);

    uchTemp &= 0xfc;
    WRITE_PORT_UCHAR((PUCHAR)0x61, uchTemp);
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    Sound_Off();
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("驱动加载成功\n"));

    Sound_On(2000);

    return STATUS_SUCCESS;
}

