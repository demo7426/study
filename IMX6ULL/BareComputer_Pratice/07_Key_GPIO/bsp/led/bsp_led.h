/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_led.h
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.08.11
描  述: 实现bsp led灯文件
备  注:
修改记录:

  1.  日期: 2024.08.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0      

*************************************************/

#ifndef __BSP_LED_H_
#define __BSP_LED_H_

/// @brief led初始化
/// @param  
/// @return 
int Bsp_LedInit(void);

/// @brief led亮
/// @param  
/// @return 
int Bsp_LedOn(void);

/// @brief led灭
/// @param  
/// @return 
int Bsp_LedOff(void);

/// @brief 切换led灯的状态
/// @param _Status led灯的状态;0--灭;1--亮;
/// @return 
int Bsp_LedSwitchStatus(const int _Status);

#endif