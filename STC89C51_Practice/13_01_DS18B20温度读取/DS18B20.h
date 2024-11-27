/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	DS18B20.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.28
描  述: 温度读取模块
备  注:  
修改记录: 

  1.  日期: 2024.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __DS18B20_H__
#define __DS18B20_H__

/// @brief 温度数据转换
/// @param 无
/// @return 无
void DS18B20_Convert(void);

/// @brief 获取当前温度，调用此函数需要先调用 DS18B20_Convert 函数刷新DS18B20内部数据
/// @param _Byte--字节数据
/// @return 无
float DS18B20_GetCurTemp(void);

#endif