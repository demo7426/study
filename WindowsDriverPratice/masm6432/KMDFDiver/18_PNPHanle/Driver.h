/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.0.1     �½�����: 2025.01.09
��  ��: Ϊ������������ģ���ȡinf�ļ�����ע�������Ӽ�ֵ����
��  ע:
�޸ļ�¼:

  1.  ����: 2025.01.9
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.0.1

*************************************************/

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <ntddk.h>
#include <wdf.h>

typedef struct _DRIVER_CONTEXT
{
    DWORD32 Num;            //����
    DWORD32 Boole;          //����
    WCHAR StrContent[64];    //�ַ�������
}DRIVER_CONTEXT, *PDRIVER_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DRIVER_CONTEXT, GetDriverContext)            //ͨ�� GetDriverContext �������ɻ�ȡ����������

#endif // !__DRIVER_H__


