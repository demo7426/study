/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_beep.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.18
描  述: 蜂鸣器功能实现文件
备  注:
修改记录:

  1.  日期: 2024.08.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef __BSP_BEEP_H_
#define __BSP_BEEP_H_

/// @brief 蜂鸣器初始化
/// @param  
/// @return -2--函数执行失败;-1--输入参数错误;0--函数执行成功
int Bsp_BeepInit(void);

/// @brief 设置蜂鸣器状态
/// @param _Status 0--关闭；1--开启
/// @return -2--函数执行失败;-1--输入参数错误;0--函数执行成功
int Bsp_Beep_SetStatus(const int _Status);

#endif


