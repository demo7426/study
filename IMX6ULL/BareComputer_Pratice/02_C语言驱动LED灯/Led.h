/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	Led.h
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.05.24
描  述: 实现对Led灯的控制
备  注:
修改记录:

  1.  日期: 2024.05.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V1.0.0

*************************************************/

#ifndef _LED_H
#define _LED_H

/*使能所有外设时钟*/
#define CCM_CCGR0           *((volatile unsigned int*)0x020c4068)
#define CCM_CCGR1           *((volatile unsigned int*)0x020c406c)
#define CCM_CCGR2           *((volatile unsigned int*)0x020c4070)
#define CCM_CCGR3           *((volatile unsigned int*)0x020c4074)
#define CCM_CCGR4           *((volatile unsigned int*)0x020c4078)
#define CCM_CCGR5           *((volatile unsigned int*)0x020c407c)
#define CCM_CCGR6           *((volatile unsigned int*)0x020c4080)

/*IOMUX相关寄存器地址*/
#define SW_MUX_GPIO1_IO03   *((volatile unsigned int*)0x020e0068)
#define SW_PAD_GPIO1_IO03   *((volatile unsigned int*)0x020e02f4)

/*GPIO1相关寄存器地址*/
#define GPIO1_DR            *((volatile unsigned int*)0x0209c000)
#define GPIO1_GRIR          *((volatile unsigned int*)0x0209c004)
#define GPIO1_PSR           *((volatile unsigned int*)0x0209c008)
#define GPIO1_ICR1          *((volatile unsigned int*)0x0209c00c)
#define GPIO1_ICR2          *((volatile unsigned int*)0x0209c010)
#define GPIO1_IMR           *((volatile unsigned int*)0x0209c014)
#define GPIO1_ISR           *((volatile unsigned int*)0x0209c018)
#define GPIO1_EDGE_SEL      *((volatile unsigned int*)0x0209c01c)

#endif // !_LED_H


