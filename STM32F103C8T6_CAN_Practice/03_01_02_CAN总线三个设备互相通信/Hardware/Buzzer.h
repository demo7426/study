/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Buzzer.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: 蜂鸣器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __BUZZER_H__
#define __BUZZER_H__

/// @brief 初始化
/// @param 无
/// @return 无
void Buzzer_Init(void);

/// @brief 蜂鸣器响
/// @param 无
/// @return 无
void Buzzer_On(void);

/// @brief 蜂鸣器灭
/// @param 无
/// @return 无
void Buzzer_Off(void);

#endif
