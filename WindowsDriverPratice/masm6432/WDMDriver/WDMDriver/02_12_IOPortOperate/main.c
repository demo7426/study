/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.01
��  ��: IO�˿ڲ���
��  ע: edx--�˿ڵ�ַ
        al��ax��eax--�˿ڶ�ȡ���������ݴ�λ��
�޸ļ�¼:

  1.  ����: 2025.01.01
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>

#ifdef _X86_
UCHAR In_8(IN PUCHAR _pPort)
{
    UCHAR uchRet = 0;

    __asm
    {
        mov edx, _pPort         //д��˿�
        mov eax, 0              //����
        in al, dx               //��ȡ�˿����ݵ�8λ��al
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
        mov edx, _pPort         //д��˿�
        mov eax, 0              //����
        in ax, dx               //��ȡ�˿����ݵ�16λ��ax
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
        mov edx, _pPort         //д��˿�
        mov eax, 0              //����
        in eax, dx              //��ȡ�˿����ݵ�32λ��eax
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
        mov edx, _pPort         //д��˿�
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
        mov edx, _pPort         //д��˿�
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
        mov edx, _pPort         //д��˿�
        mov eax, _Value
        out dx, eax
        nop
        nop
    }
}
#endif // _X86_


VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("�������سɹ�\n"));

#ifdef _X86_
    KdPrint(("0x%x", In_8((PUCHAR)0x43)));
#else
    KdPrint(("0x%x", READ_PORT_UCHAR((PUCHAR)0x43)));
#endif // DEBUG

    return STATUS_SUCCESS;
}

