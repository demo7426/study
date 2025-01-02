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

#ifdef _X86_
UCHAR In_8(IN PUCHAR _pPort)
{
    UCHAR uchRet = 0;

    __asm
    {
        mov edx, _pPort         //写入端口
        mov eax, 0              //清零
        in al, dx               //读取端口数据到8位的al
        mov uchRet, al
        nop
        nop
    }

    return uchRet;
}

USHORT In_16(IN PUSHORT _pPort)
{
    USHORT usRet = 0;

    __asm
    {
        mov edx, _pPort         //写入端口
        mov eax, 0              //清零
        in ax, dx               //读取端口数据到16位的ax
        mov usRet, ax
        nop
        nop
    }

    return usRet;
}

ULONG In_32(IN PULONG _pPort)
{
    ULONG unRet = 0;

    __asm
    {
        mov edx, _pPort         //写入端口
        mov eax, 0              //清零
        in eax, dx              //读取端口数据到32位的eax
        mov unRet, eax
        nop
        nop
    }

    return unRet;
}

VOID Out_8(IN PUCHAR _pPort, IN UCHAR _Value)
{
    __asm
    {
        mov edx, _pPort         //写入端口
        mov al, _Value
        out dx, al
        nop
        nop
    }
}

VOID Out_16(IN PUSHORT _pPort, IN USHORT _Value)
{
    __asm
    {
        mov edx, _pPort         //写入端口
        mov ax, _Value
        out dx, ax
        nop
        nop
    }
}

VOID Out_32(IN PULONG _pPort, IN PULONG _Value)
{
    __asm
    {
        mov edx, _pPort         //写入端口
        mov eax, _Value
        out dx, eax
        nop
        nop
    }
}
#endif // _X86_


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("驱动卸载成功\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("驱动加载成功\n"));

#ifdef _X86_
    KdPrint(("0x%x", In_8((PUCHAR)0x43)));
#else
    KdPrint(("0x%x", READ_PORT_UCHAR((PUCHAR)0x43)));
#endif // DEBUG

    return STATUS_SUCCESS;
}

