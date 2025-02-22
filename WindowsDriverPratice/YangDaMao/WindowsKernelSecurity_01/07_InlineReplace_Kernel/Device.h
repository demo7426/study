/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	Device.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.19
��  ��: ��װһЩ���״���
��  ע:
�޸ļ�¼:

  1.  ����: 2024.02.19
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/


#ifndef __MYFUNCTION_H__
#define __MYFUNCTION_H__

//�豸��չ
typedef struct _DEVICEEXTENSION
{
	PDEVICE_OBJECT pPDO;	//�����豸����
	PDEVICE_OBJECT pNextDevice;	//�����豸����

	IO_REMOVE_LOCK IORemoveLock;
	CHAR IORemoveLock_Tag[8];
}DEVICEEXTENSION, *PDEVICEEXTENSION;

/// <summary>
/// �����豸�������ƻ�ȡ���豸����ָ������ã�����δʹ���豸����ָ�����Ҫ�ֶ�������豸����ָ������ã�
/// </summary>
/// <param name="_pDevicePath">�豸·��</param>
/// <returns>�豸����ָ�������</returns>
PDEVICE_OBJECT GetDeviceObjectByName(IN PCWSTR _pDevicePath);

/// <summary>
/// ���������������ƻ�ȡ����������ָ������ã�����δʹ����������ָ�����Ҫ�ֶ��������������ָ������ã�
/// </summary>
/// <param name="_pDriverPath">����·��</param>
/// <returns>�豸����ָ�������</returns>
PDRIVER_OBJECT GetDriverObjectByName(IN PCWSTR _pDriverPath);

/// <summary>
/// ����һ�����豸���Ҹ��ӵ���Ӧ�������豸������
/// </summary>
/// <param name="_pDriverObject">��������</param>
/// <param name="_pPDO">�����豸����</param>
/// <returns></returns>
PDEVICE_OBJECT CreateNewDeviceAndAttachedToPDO(IN PDRIVER_OBJECT _pDriverObject, IN PDEVICE_OBJECT _pPDO);

//�ر�д����
KIRQL WPOff(VOID);

//����д����
VOID WPOn(KIRQL _KIrqL);

#endif // !__MYFUNCTION_H__

