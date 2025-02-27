/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.26
描  述: 替换键盘功能设备对象FDO的回调函数（在功能设备对象FDO上面还有一个过滤设备对象）
备  注: win7 amd64位系统测试未通过，杨大毛老师的源码也无法正常获取到键盘功能设备对象FDO的回调函数的起始地址
修改记录:

  1.  日期: 2024.02.26
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <wdm.h>

#include "Device.h"

static KeyBoardCallbackFunc_Type g_pfOldKeyBoardCallbackFunc = NULL;		//原来的键盘回调函数的值
static LIST_ENTRY g_tListEntry = { 0 };

/// <summary>
/// 新的键盘回调函数
/// </summary>
/// <param name="_pDevObj"></param>
/// <param name="_pStartData">键盘输入起始地址</param>
/// <param name="_pEndData">键盘输入结束地址的下一个地址，内存排布类似于c++的vector容器</param>
/// <param name="_pNum"></param>
static VOID New_KeyBoardCallbackFunc(PDEVICE_OBJECT _pDevObj, PKEYBOARD_INPUT_DATA _pStartData, PKEYBOARD_INPUT_DATA _pEndData, PULONG _pNum)
{
	PKEYBOARD_INPUT_DATA ptKeyBoard_InputData = _pStartData;

	//_pStartData~_pEndData均是键盘输入的数据
	while ((ULONG64)ptKeyBoard_InputData < (ULONG64)_pEndData)
	{
		if (ptKeyBoard_InputData->Flags & KEY_BREAK)
			KdPrint(("Key = 0x%x is up\n", ptKeyBoard_InputData->MakeCode));
		else
			KdPrint(("Key = 0x%x is down\n", ptKeyBoard_InputData->MakeCode));

		ptKeyBoard_InputData++;
	}
	
	if (g_pfOldKeyBoardCallbackFunc)
		g_pfOldKeyBoardCallbackFunc(_pDevObj, _pStartData, _pEndData, _pNum);		//保证用户态键盘按键输入可以正常使用
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
		InterlockedExchange64((LONG64*)(ptDev_Callback_Info->CallbackFuncStartAddr), (LONG64)g_pfOldKeyBoardCallbackFunc);		//使用原子操作替换掉原来设备扩展内部的回调函数

		ExFreePool(ptDev_Callback_Info);
		ptRecvListEntry = RemoveHeadList(&g_tListEntry);
	}

	KdPrint(("驱动卸载成功\n"));
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

	//获取所有回调函数的起始地址
	//GetKeyBoardCallbackFunc(L"\\Driver\\kbdclass", L"\\Driver\\kbdhid", &tListEntry);			//正常物理机的 usb 键盘输入，功能驱动则是 \\Driver\\kbdhid
	GetKeyBoardCallbackFunc(L"\\Driver\\kbdclass", L"\\Driver\\i8042prt", &tListEntry);			//虚拟机内部模拟的是圆头键盘输入，功能驱动则是 \\Driver\\i8042prt

	//替换所有的回调函数，并将其原始的回调函数保存下来
	ptRecvListEntry = RemoveHeadList(&tListEntry);
	if (!ptRecvListEntry)
	{
		KdPrint(("获取键盘回调函数失败\n"));
		return lNTStatus;
	}

	ptDev_Callback_Info = CONTAINING_RECORD(ptRecvListEntry, DEVICE_CALLBACKFUNC_INFO, List_Entry);
	
	g_pfOldKeyBoardCallbackFunc = *(KeyBoardCallbackFunc_Type*)(ptDev_Callback_Info->CallbackFuncStartAddr);

	while (!IsListEmpty(&tListEntry))
	{
		InterlockedExchange64((LONG64*)(ptDev_Callback_Info->CallbackFuncStartAddr), (LONG64)New_KeyBoardCallbackFunc);		//使用原子操作替换掉原来设备扩展内部的回调函数

		InsertHeadList(&g_tListEntry, &ptDev_Callback_Info->List_Entry);		//保存替换后键盘回调函数起始地址等信息

		ptRecvListEntry = RemoveHeadList(&tListEntry);
	}

	KdPrint(("驱动加载成功\n"));

	return lNTStatus;
}


