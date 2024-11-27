/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	OneWire.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.28
描  述: 单总线模块
备  注:  
修改记录: 

  1.  日期: 2024.11.28
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __OneWire_H__
#define __OneWire_H__

/// @brief 单总线初始化
/// @param 无
/// @return 无
void OneWire_Init(void);

/// @brief 发送字节数据
/// @param _Byte--字节数据
/// @return 无
void OneWire_SendByte(unsigned char _Byte);

/// @brief 接收字节数据
/// @param 无
/// @return _Byte--字节数据
unsigned char OneWire_RecvByte(void);

#endif