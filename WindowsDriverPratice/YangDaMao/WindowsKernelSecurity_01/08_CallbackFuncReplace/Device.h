/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Device.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.02.19
描  述: 封装一些简易处理
备  注:
修改记录:

  1.  日期: 2024.02.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/


#ifndef __MYFUNCTION_H__
#define __MYFUNCTION_H__

#include <ntddkbd.h>

//键盘功能设备对象的回调函数模板
typedef VOID(*KeyBoardCallbackFunc_Type)(PDEVICE_OBJECT _pDevObj, PKEYBOARD_INPUT_DATA _pStartData, PKEYBOARD_INPUT_DATA _pEndData, PULONG _pNum);

//设备扩展
typedef struct _DEVICEEXTENSION
{
	PDEVICE_OBJECT pPDO;			//物理设备对象
	PDEVICE_OBJECT pNextDevice;		//功能设备对象

	IO_REMOVE_LOCK IORemoveLock;
	CHAR IORemoveLock_Tag[8];
}DEVICEEXTENSION, * PDEVICEEXTENSION;

typedef struct _DEVICE_CALLBACKFUNC_INFO
{
	LIST_ENTRY List_Entry;	
	PVOID CallbackFuncStartAddr;	//回调函数的起始地址		
}DEVICE_CALLBACKFUNC_INFO, * PDEVICE_CALLBACKFUNC_INFO;

/// <summary>
/// 根据设备对象名称获取其设备对象指针的引用（后续未使用设备对象指针后，需要手动解除对设备对象指针的引用）
/// </summary>
/// <param name="_pDevicePath">设备路径</param>
/// <returns>设备对象指针的引用</returns>
PDEVICE_OBJECT GetDeviceObjectByName(IN PCWSTR _pDevicePath);

/// <summary>
/// 根据驱动对象名称获取其驱动对象指针的引用（后续未使用驱动对象指针后，需要手动解除对驱动对象指针的引用）
/// </summary>
/// <param name="_pDriverPath">驱动路径</param>
/// <returns>设备对象指针的引用</returns>
PDRIVER_OBJECT GetDriverObjectByName(IN PCWSTR _pDriverPath);

/// <summary>
/// 创建一个新设备并且附加到对应的物理设备对象上
/// </summary>
/// <param name="_pDriverObject">驱动对象</param>
/// <param name="_pPDO">物理设备对象</param>
/// <returns></returns>
PDEVICE_OBJECT CreateNewDeviceAndAttachedToPDO(IN PDRIVER_OBJECT _pDriverObject, IN PDEVICE_OBJECT _pPDO);

/// <summary>
/// 根据 _pClassDriverPath 的驱动对象指针获取 _pMinDriverPath 的设备扩展内部的回调函数信息
/// </summary>
/// <param name="_pClassDriverPath">上层键盘功能过滤对象路径</param>
/// <param name="_pMinDriverPath">功能过滤对象路径</param>
/// <param name="_pResCallbackFunc_List_Entry">功能过滤对象回调函数信息</param>
/// <returns></returns>
NTSTATUS GetKeyBoardCallbackFunc(PWCHAR _pClassDriverPath, PWCHAR _pMinDriverPath, PLIST_ENTRY _pResCallbackFunc_List_Entry);

/// <summary>
/// 查找 _pFindedDevObj 扩展属性内部满足 _pSrcDevObj 的回调函数的起始地址
/// </summary>
/// <param name="_pSrcDevObj">源设备对象</param>
/// <param name="_SrcDrvStart">源驱动对象的起始地址</param>
/// <param name="_SrcDrvEnd">源驱动对象的结束地址</param>
/// <param name="_pFindedDevObj">被查找的设备对象</param>
/// <param name="_ppCallFuncStartAddr">回调函数的起始地址</param>
/// <returns></returns>
NTSTATUS FindCallbackFunc_StartAddr(PDEVICE_OBJECT _pSrcDevObj, ULONG64 _SrcDrvStart, ULONG64 _SrcDrvEnd, PDEVICE_OBJECT _pFindedDevObj, KeyBoardCallbackFunc_Type* _ppCallFuncStartAddr);

//关闭写保护
KIRQL WPOff(VOID);

//开启写保护
VOID WPOn(KIRQL _KIrqL);

#endif // !__MYFUNCTION_H__

