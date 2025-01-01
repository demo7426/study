/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	MyRTC.c
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.01.01
描  述: STM32开发板内部RCC实时时钟
备  注:  
修改记录: 

  1.  日期: 2025.01.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <time.h>

#include "stm32f10x.h"                  // Device header

#include "MyRTC.h"

uint16_t g_usCurTime[] = { 2025, 1, 1, 18, 49, 50 };		//当前时间

//设置当前时间
static void SetTime(void);

void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);		//使能PWR时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);		//使能BKP时钟
		
	PWR_BackupAccessCmd(ENABLE);							//使能对BKP和RTC的访问	
	
	RCC_LSEConfig(RCC_LSE_ON);								//使能外部LSE时钟输入
	while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);		//等待外部LSE时钟输入配置完成
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);					//配置RTC的外部时钟输入为LSE
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForSynchro();									//等待外部LSE时钟输入启动完成
	RTC_WaitForLastTask();
	
	RTC_SetPrescaler(32768 - 1);							//对LSE时钟进行32768分频，为1Hz
	RTC_WaitForLastTask();									//等待写入操作完成
	
	SetTime();
//	RTC_SetCounter(1672588795);
//	RTC_WaitForLastTask();
}

static void SetTime(void)
{
	time_t unCurTime;
	struct tm tCurTimeDate;
	
	tCurTimeDate.tm_year = g_usCurTime[0] - 1900;
	tCurTimeDate.tm_mon = g_usCurTime[1] - 1;
	tCurTimeDate.tm_mday = g_usCurTime[2];
	tCurTimeDate.tm_hour = g_usCurTime[3];
	tCurTimeDate.tm_min = g_usCurTime[4];
	tCurTimeDate.tm_sec = g_usCurTime[5];
	
	unCurTime = mktime(&tCurTimeDate) - 8 * 60 * 60;		//将北京时间转换为格林尼治时钟
	
	RTC_SetCounter(unCurTime);
	RTC_WaitForLastTask();
}

void MyRTC_GetTime(void)
{
	time_t unCurTime;
	struct tm tCurTimeDate;
	
	unCurTime = RTC_GetCounter() + 8 * 60 * 60;				//将格林尼治时钟转换为北京时间
	
	tCurTimeDate = *localtime(&unCurTime);
	
	g_usCurTime[0] = tCurTimeDate.tm_year + 1900;
	g_usCurTime[1] = tCurTimeDate.tm_mon + 1;
	g_usCurTime[2] = tCurTimeDate.tm_mday;
	g_usCurTime[3] = tCurTimeDate.tm_hour;
	g_usCurTime[4] = tCurTimeDate.tm_min;
	g_usCurTime[5] = tCurTimeDate.tm_sec;
}
