/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	PWM.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.08
描  述: PWM模块
备  注:  
修改记录: 

  1.  日期: 2024.12.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __PWM_H__
#define __PWM_H__

/// @brief 初始化
/// @param 无
/// @return 无
void PWM_Init(void);

/// @brief 设置占空比中高低电平的比较值
/// @param _Compare--0~100
/// @return 无
void PWM_SetCompare3(unsigned int _Compare);

#endif
