/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Key.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.06
描  述: Key独立按键模块
备  注:  
修改记录: 

  1.  日期: 2024.12.06
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __KEY_H__
#define __KEY_H__

/// @brief KEY模块初始化
/// @param 无
/// @return 无
void Key_Init(void);

/// @brief 获取当前的按下的独立按键
/// @param 无
/// @return 独立按键;1--按键01;2--按键02
unsigned char Key__GetCurKey(void);

#endif
