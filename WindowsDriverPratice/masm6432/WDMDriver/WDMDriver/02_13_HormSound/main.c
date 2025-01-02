/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.01
��  ��: �������ȷ���
��  ע: �˿ڵ�ַ      ����
        0x40          ������0
        0x41          ������1
        0x42          ������2
        0x43          ���ƼĴ���
        0x61          ���ȿ���
�޸ļ�¼:

  1.  ����: 2025.01.01
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#include <ntddk.h>

VOID Sound_On(INT32 _Freq)
{
    USHORT B = 1193180 / _Freq;                             //ϵͳʱ�Ӿ���Ϊ1.1932MHz
    UCHAR uchTemp = READ_PORT_UCHAR((PUCHAR)0x61);

    uchTemp |= 3;
    WRITE_PORT_UCHAR((PUCHAR)0x61, uchTemp);                //ʹ�����
    WRITE_PORT_UCHAR((PUCHAR)0x43, 0xb6);                   //����״̬��

    WRITE_PORT_UCHAR((PUCHAR)0x42, B & 0xff);               //ϵͳ��Ƶ;��д�Ͱ�λ����д�߰�λ��ϵͳҪ��
    WRITE_PORT_UCHAR((PUCHAR)0x42, (B >> 8) & 0xff);
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
    KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
    DriverObject->DriverUnload = DriverUnload;

    KdPrint(("�������سɹ�\n"));

    Sound_On(2000);

    return STATUS_SUCCESS;
}

