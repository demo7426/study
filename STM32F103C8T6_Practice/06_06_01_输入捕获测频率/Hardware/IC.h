/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	IC.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.13
描  述: 输入捕获频率、占空比模块
备  注:  
修改记录: 

  1.  日期: 2024.12.13
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __IC_H__
#define __IC_H__

/// @brief 初始化
/// @param 无
/// @return 无
void IC_Init(void);

/// @brief 获取当前输入的频率
/// @param 无
/// @return 输入的频率
unsigned int IC_GetFreq(void);

#endif
