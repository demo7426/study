/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Timer0.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.12
描  述: 定时器0模块
备  注:  
修改记录: 

  1.  日期: 2024.11.12
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/
#ifndef __TIMER0_H__
#define __TIMER0_H__

/// @brief 初始化Timer0
/// @param 无
/// @return 无
void Timer0_Init(void);

/// @brief 设置定时器的起始值
/// @param _Counter--起始值
/// @return 无
void Timer0_SetCounter(unsigned int _Counter);

/// @brief 获取定时器的当前值
/// @param 无
/// @return 定时器的当前值
unsigned int Timer0_GetCounter(void);

/// @brief 启动定时器
/// @param 0--停止计时;1--开始计时
/// @return 无
void Timer0_Run(unsigned char _Flag);

#endif

