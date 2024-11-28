/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	OneWire.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.29
描  述: 单总线模块
备  注: 在单总线操作时，需要关闭中断，防止中断影响到单总线的时序 
修改记录: 

  1.  日期: 2024.11.29
      作者: 钱锐
          1) 此为模板第一个版本;
      内容:
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