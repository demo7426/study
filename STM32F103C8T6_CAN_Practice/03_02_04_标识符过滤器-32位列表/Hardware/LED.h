/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LED.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: LED灯显示控制
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __LED_H__
#define __LED_H_

/// @brief LED模块初始化
/// @param 无
/// @return 无
void LED_Init(void);

/// @brief LED 01亮
/// @param 无
/// @return 无
void LED_On_01(void);

/// @brief LED 01灭
/// @param 无
/// @return 无
void LED_Off_01(void);

/// @brief LED 01反转
/// @param 无
/// @return 无
void LED_Turn_01(void);

/// @brief LED 02亮
/// @param 无
/// @return 无
void LED_On_02(void);

/// @brief LED 02灭
/// @param 无
/// @return 无
void LED_Off_02(void);

/// @brief LED 02反转
/// @param 无
/// @return 无
void LED_Turn_02(void);

#endif
