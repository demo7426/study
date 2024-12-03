/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	IR.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.03
描  述: 红外波数据解析模块
备  注:  
修改记录: 

  1.  日期: 2024.12.03
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __IR_H__
#define __IR_H__

#define IR_POWER			0x45
#define IR_MODE				0x46
#define IR_MUTE				0x47
#define IR_START_STOP	0x44
#define IR_PREVIOUS		0x40
#define IR_NEXT				0x43
#define IR_EQ					0x07
#define IR_VOL_MINUS	0x15
#define IR_VOL_ADD		0x09
#define IR_0					0x16
#define IR_RPT				0x19
#define IR_USD				0x0D
#define IR_1					0x0C
#define IR_2					0x18
#define IR_3					0x5E
#define IR_4					0x08
#define IR_5					0x1C
#define IR_6					0x5A
#define IR_7					0x42
#define IR_8					0x52
#define IR_9					0x4A

void IR_Init(void);

/**
  * @brief  红外遥控获取收到数据帧标志位
  * @param  无
  * @retval 是否收到数据帧，1为收到，0为未收到
  */
unsigned char IR_GetDataFlag(void);
	
/**
  * @brief  红外遥控获取收到连发帧标志位
  * @param  无
  * @retval 是否收到连发帧，1为收到，0为未收到
  */
unsigned char IR_GetRepeatFlag(void);
	
/**
  * @brief  红外遥控获取收到的地址数据
  * @param  无
  * @retval 收到的地址数据
  */
unsigned char IR_GetAddress(void);

/**
  * @brief  红外遥控获取收到的命令数据
  * @param  无
  * @retval 收到的命令数据
  */
unsigned char IR_GetCommand(void);

#endif

