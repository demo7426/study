/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	CountSensor.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.07
描  述: 对射式红外传感器模块
备  注:  
修改记录: 

  1.  日期: 2024.12.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __COUNTSENSOR_H__
#define __COUNTSENSOR_H__

/// @brief 初始化
/// @param 无
/// @return 无
void CountSensor_Init(void);

/// @brief 获取内部计数
/// @param 无
/// @return 对射式红外传感器被触发次数
unsigned int CountSensor_GetCurCount(void);

#endif
