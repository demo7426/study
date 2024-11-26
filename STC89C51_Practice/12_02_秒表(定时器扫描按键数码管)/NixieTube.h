/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	NixieTube.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.11
描  述: 数码管显示模块
备  注:  
修改记录: 

  1.  日期: 2024.11.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __NIXIETUBE_H__
#define __NIXIETUBE_H__

//数码管显示子函数
void SetNixieTube(unsigned char _NixieNo, unsigned char _Num);

/// @brief 循环刷新数码管
/// @param 无
/// @return 无
void NixieTubeLoop(void);

#endif