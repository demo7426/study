/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Queue.h
作  者:	钱锐      版本: V0.0.2     新建日期: 2025.01.12
描  述: 队列文件
备  注:
修改记录:

  1.  日期: 2025.01.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.0.1

  2.  日期: 2025.01.12
      作者: 钱锐
      内容:
          1) 新增其它IO控制交互模式；
      版本:V0.0.2

*************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <ntddk.h>
#include <wdf.h>

//Function 需要从 0x800 开始，前面的被内核系统占用
#define IO_NUMCONVER_CODE	        CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)			//数字转换
#define IO_READ_REGEDIT_NUM_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)			//读取注册表数字
#define IO_READ_REGEDIT_BOOLE_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_NEITHER, FILE_ANY_ACCESS)			//读取注册表布尔
#define IO_READ_REGEDIT_STRING_CODE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)		//读取注册表字符串

VOID EVT_WDF_IO_Queue_IO_Device_Control(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, _In_ size_t InputBufferLength, _In_ ULONG IoControlCode);

VOID EVT_WDF_IO_QUEUE_IO_Canceled_On_Queue(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request);

/// <summary>
/// 用于处理手动队列的请求
/// </summary>
/// <param name="Timer"></param>
VOID EVT_WDF_Timer(_In_ WDFTIMER Timer);

#endif // !__QUEUE_H__
