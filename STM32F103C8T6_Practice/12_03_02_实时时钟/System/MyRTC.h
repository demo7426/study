/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyRTC.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.01
描  述: STM32开发板内部实时时钟
备  注:  
修改记录: 

  1.  日期: 2025.01.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MYRTC_H__
#define __MYRTC_H__

/// @brief 初始化
/// @param 无
/// @return 无
void MyRTC_Init(void);

/// @brief 获取当前时间
/// @param 无
/// @return 无
void MyRTC_GetTime(void);

extern uint16_t g_usCurTime[];

#endif
