/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Motor.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.08
描  述: 直流电机驱动模块
备  注:  
修改记录: 

  1.  日期: 2024.12.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __Servo_H__
#define __Servo_H__

/// @brief 初始化
/// @param 无
/// @return 无
void Motor_Init(void);

/// @brief 设置当前速度
/// @param _Speed--速度;值:0~100
/// @return 无
void Servo_SetCurSpeed(int _Speed);

#endif
