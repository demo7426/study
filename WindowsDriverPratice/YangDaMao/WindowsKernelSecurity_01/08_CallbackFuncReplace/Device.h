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

#include <ntddkbd.h>

//���̹����豸����Ļص�����ģ��
typedef VOID(*KeyBoardCallbackFunc_Type)(PDEVICE_OBJECT _pDevObj, PKEYBOARD_INPUT_DATA _pStartData, PKEYBOARD_INPUT_DATA _pEndData, PULONG _pNum);

//�豸��չ
typedef struct _DEVICEEXTENSION
{
	PDEVICE_OBJECT pPDO;			//�����豸����
	PDEVICE_OBJECT pNextDevice;		//�����豸����

	IO_REMOVE_LOCK IORemoveLock;
	CHAR IORemoveLock_Tag[8];
}DEVICEEXTENSION, * PDEVICEEXTENSION;

typedef struct _DEVICE_CALLBACKFUNC_INFO
{
	LIST_ENTRY List_Entry;	
	PVOID CallbackFuncStartAddr;	//�ص���������ʼ��ַ		
}DEVICE_CALLBACKFUNC_INFO, * PDEVICE_CALLBACKFUNC_INFO;

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

/// <summary>
/// ���� _pClassDriverPath ����������ָ���ȡ _pMinDriverPath ���豸��չ�ڲ��Ļص�������Ϣ
/// </summary>
/// <param name="_pClassDriverPath">�ϲ���̹��ܹ��˶���·��</param>
/// <param name="_pMinDriverPath">���ܹ��˶���·��</param>
/// <param name="_pResCallbackFunc_List_Entry">���ܹ��˶���ص�������Ϣ</param>
/// <returns></returns>
NTSTATUS GetKeyBoardCallbackFunc(PWCHAR _pClassDriverPath, PWCHAR _pMinDriverPath, PLIST_ENTRY _pResCallbackFunc_List_Entry);

/// <summary>
/// ���� _pFindedDevObj ��չ�����ڲ����� _pSrcDevObj �Ļص���������ʼ��ַ
/// </summary>
/// <param name="_pSrcDevObj">Դ�豸����</param>
/// <param name="_SrcDrvStart">Դ�����������ʼ��ַ</param>
/// <param name="_SrcDrvEnd">Դ��������Ľ�����ַ</param>
/// <param name="_pFindedDevObj">�����ҵ��豸����</param>
/// <param name="_ppCallFuncStartAddr">�ص���������ʼ��ַ</param>
/// <returns></returns>
NTSTATUS FindCallbackFunc_StartAddr(PDEVICE_OBJECT _pSrcDevObj, ULONG64 _SrcDrvStart, ULONG64 _SrcDrvEnd, PDEVICE_OBJECT _pFindedDevObj, KeyBoardCallbackFunc_Type* _ppCallFuncStartAddr);

//�ر�д����
KIRQL WPOff(VOID);

//����д����
VOID WPOn(KIRQL _KIrqL);

#endif // !__MYFUNCTION_H__

