/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyI2C.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.26
描  述: I2C协议模块
备  注:  
修改记录: 

  1.  日期: 2024.12.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __MYI2C_H__
#define __MYI2C_H__

/// @brief I2C协议初始化
/// @param 无
/// @return 无
void MyI2C_Init(void);

/// @brief I2C协议起始
/// @param 无
/// @return 无
void MyI2C_Start(void);

/// @brief I2C协议终止
/// @param 无
/// @return 无
void MyI2C_Stop(void);

/// @brief I2C协议发送一个字节
/// @param _Byte--待发送数据
/// @return 无
void MyI2C_SendByte(uint8_t _Byte);

/// @brief I2C协议接收一个字节
/// @param 无
/// @return 接收数据
uint8_t MyI2C_RecvByte(void);

/// @brief I2C协议发送应答
/// @param _Ack--发送的应答;0--应答;1--非应答;
/// @return 无
void MyI2C_SendAck(uint8_t _Ack);

/// @brief I2C协议接收应答
/// @param 无
/// @return 接收得应答
uint8_t MyI2C_RecvAck(void);

#endif
