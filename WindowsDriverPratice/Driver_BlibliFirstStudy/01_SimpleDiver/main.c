/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.10.17
��  ��:	ʵ��һ������׵� �汾windows10 �汾��22H2 ��������
��  ע:
�޸ļ�¼:

  1.  ����: 2024.10.17
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾��
      �汾:V0.1.0

*************************************************/

#include <ntddk.h>

/// <summary>
/// ����ж�ػص�����
/// </summary>
/// <param name="driver">�ں˷ַ�������Ķ���</param>
/// <returns></returns>
NTSTATUS DriverUnload(PDRIVER_OBJECT driver)
{
    UNREFERENCED_PARAMETER(driver);

    DbgPrint("%s is entry.\n", __FUNCDNAME__);
    return STATUS_SUCCESS;
}

/// <summary>
/// ������ں���
/// </summary>
/// <param name="driver">�ں˷ַ�������Ķ���</param>
/// <param name="res_path">�ַ�����Ϣ</param>
/// <returns></returns>
NTSTATUS DriverEntry(PDRIVER_OBJECT driver, PUNICODE_STRING res_path)
{
    UNREFERENCED_PARAMETER(res_path);

    driver->DriverUnload = DriverUnload;

    DbgPrint("%s is entry.\n", __FUNCDNAME__);

    return STATUS_SUCCESS;
}


