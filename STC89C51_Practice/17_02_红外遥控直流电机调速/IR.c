/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	IR.c
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

#include <REGX52.H>

#include "Int0.h"
#include "Timer0.h"
#include "LCD1602.h"

unsigned int g_unIR_Time = 0;
unsigned char g_uchIR_State = 0;

unsigned char g_uchIR_Data[4] = { 0 };
unsigned char g_uchIR_DataPos = 0;

unsigned char g_uchIR_DataFlag = 0;
unsigned char g_uchIR_RepeatFlag = 0;
unsigned char g_uchIR_Address = 0;
unsigned char g_uchIR_Command = 0;

void IR_Init(void)
{
	Timer0_Init();
	Int0_Init();
}
/**
  * @brief  红外遥控获取收到数据帧标志位
  * @param  无
  * @retval 是否收到数据帧，1为收到，0为未收到
  */
unsigned char IR_GetDataFlag(void)
{
	if(g_uchIR_DataFlag)
	{
		g_uchIR_DataFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取收到连发帧标志位
  * @param  无
  * @retval 是否收到连发帧，1为收到，0为未收到
  */
unsigned char IR_GetRepeatFlag(void)
{
	if(g_uchIR_RepeatFlag)
	{
		g_uchIR_RepeatFlag = 0;
		return 1;
	}
	return 0;
}

/**
  * @brief  红外遥控获取收到的地址数据
  * @param  无
  * @retval 收到的地址数据
  */
unsigned char IR_GetAddress(void)
{
	return g_uchIR_Address;
}

/**
  * @brief  红外遥控获取收到的命令数据
  * @param  无
  * @retval 收到的命令数据
  */
unsigned char IR_GetCommand(void)
{
	return g_uchIR_Command;
}

//红外中断函数模板
void Int0_Routine(void) interrupt 0
{
		if(g_uchIR_State == 0)
		{
			Timer0_SetCounter(0);
			Timer0_Run(1);
			g_uchIR_State = 1;
		}
		else if(g_uchIR_State == 1)
		{
			g_unIR_Time = Timer0_GetCounter();
			Timer0_SetCounter(0);
			
			if(g_unIR_Time > 12442 - 500 && g_unIR_Time < 12442 + 500)
			{
				g_uchIR_State = 2;
			}
			else if(g_unIR_Time > 10368 - 500 && g_unIR_Time < 10368 + 500)
			{
				g_uchIR_RepeatFlag = 1;
				Timer0_Run(0);
				g_uchIR_State = 0;
			}
			else 
			{
				g_uchIR_State = 1;
			}
		}
		else if(g_uchIR_State == 2)
		{
			P2 = 0;
			g_unIR_Time = Timer0_GetCounter();
			Timer0_SetCounter(0);
			
			if(g_unIR_Time > 1032 - 500 && g_unIR_Time < 1032 + 500)
			{
				g_uchIR_Data[g_uchIR_DataPos / 8] &= ~(0x01 << (g_uchIR_DataPos % 8));
				g_uchIR_DataPos++;
			}
			else if(g_unIR_Time > 2074 - 500 && g_unIR_Time < 2074 + 500)
			{
				g_uchIR_Data[g_uchIR_DataPos / 8] |= (0x01 << (g_uchIR_DataPos % 8));
				g_uchIR_DataPos++;
			}
			else 
			{
				g_uchIR_DataPos = 0;
				g_uchIR_State = 1;
			}
			
			if(g_uchIR_DataPos >= 32)			//解析数据结束
			{
				g_uchIR_DataPos = 0;
				if((g_uchIR_Data[0] == ~g_uchIR_Data[1]) && (g_uchIR_Data[2] == ~g_uchIR_Data[3]))
				{
					g_uchIR_Address = g_uchIR_Data[0];		//转存数据
					g_uchIR_Command = g_uchIR_Data[2];
					g_uchIR_DataFlag = 1;
				}
				
				Timer0_Run(0);
				g_uchIR_State = 0;
			}
		}
}





