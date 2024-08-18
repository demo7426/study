/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	bsp_beep.c
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
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"


int Bsp_BeepInit(void)
{
    //设置IO多路复用
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);

    //设置GPIO电气属性
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0x10b0);

    //设置GPIO为输出模式
    GPIO5->GDIR |= (1<<1);

    GPIO5->DR |= (1<<1);

    return 0;
}


int Bsp_Beep_SetStatus(const int _Status)
{
    switch (_Status)
    {
    case 0:
        GPIO5->DR |= (1<<1);
        break;
    case 1:
        GPIO5->DR &= ~(1<<1);
        break;
    default:
        return -1;
        break;
    }

    return 0;
}

