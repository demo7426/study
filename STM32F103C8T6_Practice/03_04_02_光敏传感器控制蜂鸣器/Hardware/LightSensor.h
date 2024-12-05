/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	LightSensor.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: 光敏传感器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __LIGHTSENSOR_H__
#define __LIGHTSENSOR_H__

/// @brief 初始化
/// @param 无
/// @return 无
void LightSensor_Init(void);

/// @brief 获取当前光敏传感器的值
/// @param 无
/// @return 无
unsigned char LightSensor_GetDO(void);

#endif
