/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Servo.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.08
描  述: 舵机驱动模块
备  注:  
修改记录: 

  1.  日期: 2024.12.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "Servo.h"
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}

void Servo_SetAngle(float _Angle)
{
	PWM_SetCompare2(_Angle / 180 * 2000 + 500);			//SG90 舵机为180°C舵机
}

