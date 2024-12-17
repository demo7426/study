/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	AD.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.12.17
描  述: AD模数转换
备  注:  
修改记录: 

  1.  日期: 2024.12.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#ifndef __AD_H__
#define __AD_H__

/// @brief 初始化
/// @param 无
/// @return 无
void AD_Init(void);

/// @brief 获取模拟量转换后的值
///	@param  _ADC_Channel: the ADC channel to configure. 
///	  This parameter can be one of the following values:
///	    @arg ADC_Channel_0: ADC Channel0 selected
///	    @arg ADC_Channel_1: ADC Channel1 selected
///	    @arg ADC_Channel_2: ADC Channel2 selected
///	    @arg ADC_Channel_3: ADC Channel3 selected
///	    @arg ADC_Channel_4: ADC Channel4 selected
///	    @arg ADC_Channel_5: ADC Channel5 selected
///	    @arg ADC_Channel_6: ADC Channel6 selected
///	    @arg ADC_Channel_7: ADC Channel7 selected
///	    @arg ADC_Channel_8: ADC Channel8 selected
///	    @arg ADC_Channel_9: ADC Channel9 selected
///	    @arg ADC_Channel_10: ADC Channel10 selected
///	    @arg ADC_Channel_11: ADC Channel11 selected
///	    @arg ADC_Channel_12: ADC Channel12 selected
///	    @arg ADC_Channel_13: ADC Channel13 selected
///	    @arg ADC_Channel_14: ADC Channel14 selected
///	    @arg ADC_Channel_15: ADC Channel15 selected
///	    @arg ADC_Channel_16: ADC Channel16 selected
///	    @arg ADC_Channel_17: ADC Channel17 selected
/// @return 模拟量转换后的值
unsigned short AD_GetValue(unsigned short _ADC_Channel);

#endif
