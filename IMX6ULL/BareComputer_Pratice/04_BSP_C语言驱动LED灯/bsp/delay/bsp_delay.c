/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_delay.c
作  者:	钱锐      版本: V1.1.0     新建日期: 2024.08.11
描  述: 实现bsp延时文件
备  注:
修改记录:

  1.  日期: 2024.08.11
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0      

*************************************************/

#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
#include "bsp_delay.h"

/// @brief 延时函数
/// @param _Millsecond--延时时间:单位为ms
void Bsp_Delay(volatile unsigned int _Millsecond)
{
    if(_Millsecond == 0)            
        return;

    int nFreq = 0x7ff;              //根据cpu主频计算出的延时参数
    while (_Millsecond--)
    {
        while(nFreq--){};
        nFreq = 0x7ff;
    }
}



