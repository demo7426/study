/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名: clk_wiz.h
作    者: 钱锐      版本: V0.1.0     新建日期: 2026.04.01
描    述: 实现时钟配置
备    注:
修改记录:

  1. 日期: 2026.04.01
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#ifndef CLK_WIZ_H_
#define CLK_WIZ_H_

/// <summary>
/// 时钟配置
/// </summary>
/// <param name="_ClkDevID">时钟设备ID</param>
/// <param name="_Freq">时钟频率;单位:MHz</param>
/// <returns>-2--执行失败;-1--参数错误;0--执行成功</returns>
int Clk_Wiz_Config(int _ClkDevID, double _Freq);


#endif


