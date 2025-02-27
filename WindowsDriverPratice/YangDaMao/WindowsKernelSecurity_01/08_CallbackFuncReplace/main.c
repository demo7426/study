/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.02.26
��  ��: �滻���̹����豸����FDO�Ļص��������ڹ����豸����FDO���滹��һ�������豸����
��  ע: win7 amd64λϵͳ����δͨ�������ë��ʦ��Դ��Ҳ�޷�������ȡ�����̹����豸����FDO�Ļص���������ʼ��ַ
�޸ļ�¼:

  1.  ����: 2024.02.26
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"

static KeyBoardCallbackFunc_Type g_pfOldKeyBoardCallbackFunc = NULL;		//ԭ���ļ��̻ص�������ֵ
static LIST_ENTRY g_tListEntry = { 0 };

/// <summary>
/// �µļ��̻ص�����
/// </summary>
/// <param name="_pDevObj"></param>
/// <param name="_pStartData">����������ʼ��ַ</param>
/// <param name="_pEndData">�������������ַ����һ����ַ���ڴ��Ų�������c++��vector����</param>
/// <param name="_pNum"></param>
static VOID New_KeyBoardCallbackFunc(PDEVICE_OBJECT _pDevObj, PKEYBOARD_INPUT_DATA _pStartData, PKEYBOARD_INPUT_DATA _pEndData, PULONG _pNum)
{
	PKEYBOARD_INPUT_DATA ptKeyBoard_InputData = _pStartData;

	//_pStartData~_pEndData���Ǽ������������
	while ((ULONG64)ptKeyBoard_InputData < (ULONG64)_pEndData)
	{
		if (ptKeyBoard_InputData->Flags & KEY_BREAK)
			KdPrint(("Key = 0x%x is up\n", ptKeyBoard_InputData->MakeCode));
		else
			KdPrint(("Key = 0x%x is down\n", ptKeyBoard_InputData->MakeCode));

		ptKeyBoard_InputData++;
	}
	
	if (g_pfOldKeyBoardCallbackFunc)
		g_pfOldKeyBoardCallbackFunc(_pDevObj, _pStartData, _pEndData, _pNum);		//��֤�û�̬���̰��������������ʹ��
}

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PLIST_ENTRY ptRecvListEntry = NULL;
	PDEVICE_CALLBACKFUNC_INFO ptDev_Callback_Info;

	if (!IsListEmpty(&g_tListEntry))
	{
		return;
	}

	ptRecvListEntry = RemoveHeadList(&g_tListEntry);
	
	ptDev_Callback_Info = CONTAINING_RECORD(ptRecvListEntry, DEVICE_CALLBACKFUNC_INFO, List_Entry);

	while (!IsListEmpty(&g_tListEntry))
	{
		InterlockedExchange64((LONG64*)(ptDev_Callback_Info->CallbackFuncStartAddr), (LONG64)g_pfOldKeyBoardCallbackFunc);		//ʹ��ԭ�Ӳ����滻��ԭ���豸��չ�ڲ��Ļص�����

		ExFreePool(ptDev_Callback_Info);
		ptRecvListEntry = RemoveHeadList(&g_tListEntry);
	}

	KdPrint(("����ж�سɹ�\n"));
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	NTSTATUS lNTStatus = STATUS_SUCCESS;
	LIST_ENTRY tListEntry = { 0 };
	PLIST_ENTRY ptRecvListEntry = NULL;
	PDEVICE_CALLBACKFUNC_INFO ptDev_Callback_Info;

	InitializeListHead(&tListEntry);
	InitializeListHead(&g_tListEntry);

	//��ȡ���лص���������ʼ��ַ
	//GetKeyBoardCallbackFunc(L"\\Driver\\kbdclass", L"\\Driver\\kbdhid", &tListEntry);			//����������� usb �������룬������������ \\Driver\\kbdhid
	GetKeyBoardCallbackFunc(L"\\Driver\\kbdclass", L"\\Driver\\i8042prt", &tListEntry);			//������ڲ�ģ�����Բͷ�������룬������������ \\Driver\\i8042prt

	//�滻���еĻص�������������ԭʼ�Ļص�������������
	ptRecvListEntry = RemoveHeadList(&tListEntry);
	if (!ptRecvListEntry)
	{
		KdPrint(("��ȡ���̻ص�����ʧ��\n"));
		return lNTStatus;
	}

	ptDev_Callback_Info = CONTAINING_RECORD(ptRecvListEntry, DEVICE_CALLBACKFUNC_INFO, List_Entry);
	
	g_pfOldKeyBoardCallbackFunc = *(KeyBoardCallbackFunc_Type*)(ptDev_Callback_Info->CallbackFuncStartAddr);

	while (!IsListEmpty(&tListEntry))
	{
		InterlockedExchange64((LONG64*)(ptDev_Callback_Info->CallbackFuncStartAddr), (LONG64)New_KeyBoardCallbackFunc);		//ʹ��ԭ�Ӳ����滻��ԭ���豸��չ�ڲ��Ļص�����

		InsertHeadList(&g_tListEntry, &ptDev_Callback_Info->List_Entry);		//�����滻����̻ص�������ʼ��ַ����Ϣ

		ptRecvListEntry = RemoveHeadList(&tListEntry);
	}

	KdPrint(("�������سɹ�\n"));

	return lNTStatus;
}


