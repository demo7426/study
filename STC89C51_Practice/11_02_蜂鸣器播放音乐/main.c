/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.23
描  述: 实现蜂鸣器播放音乐
备  注:  
修改记录: 

  1.  日期: 2024.11.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <REGX52.H>

#include "Timer0.h"
#include "Delay.h"

#define Buzzer_IO P2_5
#define CYCLE_LEN 125				//设置4分音符的周期时长

unsigned int code g_unFreqTable[] = {
		63914,63871,63968,64053,64139,64215,64290,64359,64425,64488,64546,64602,
		64654,64703,64750,64794,64836,64875,64912,64947,64980,65011,65041,65069,
		65094,65119,65143,65165,65185,65205,65224,65241,65258,65273,65288,65302
};

unsigned int code g_unMusic[] = {
	12, 4,
	12, 4,
	19, 4,
	21, 4,
	21, 4,
	19, 4+4,
	17, 4,
	17, 4,
	16, 4,
	16, 4,
	14, 4,
	14, 4,
	12, 4+4
};

unsigned int g_unFreqIndex = 0;
unsigned int g_unMusicIndex = 0;

int main(void)
{
	Timer0_Init();
	
	while(1)
	{
		g_unFreqIndex = g_unMusic[g_unMusicIndex];
		g_unMusicIndex++;
		Delay(CYCLE_LEN * g_unMusic[g_unMusicIndex]);	
		g_unMusicIndex++;	
		
		TR0 = 0;
		Delay(5);	
		TR0 = 1;		
		
		g_unMusicIndex %= 26;			//保证循环播放音乐，防止内存溢出访问到非法内存
	}
	
	return 0;
}

//定时器0的中断函数模板
void Timer0_Rountime(void) interrupt 1
{
	TL0 = g_unFreqTable[g_unFreqIndex] % 256;		//设置定时初值
	TH0 = g_unFreqTable[g_unFreqIndex] / 256;		//设置定时初值
	
	Buzzer_IO = !Buzzer_IO;
}
