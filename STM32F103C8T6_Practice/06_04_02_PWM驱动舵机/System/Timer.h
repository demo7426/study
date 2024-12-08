/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Timer.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 定时器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __TIMER_H__
#define __TIMER_H__

/// @brief 初始化
/// @param 无
/// @return 无
void Timer_Init(void);

/// @brief 获取当前计数器值
/// @param 无
/// @return 当前计数器值
unsigned int Timer_GetCounter(void);

#endif
