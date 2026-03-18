/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sfilter.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.18
描  述: 实现过滤器类
备  注:
修改记录:

  1.  日期: 2026.03.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "sfilter.h"
//#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int CSBilateralFilter::Filter(cv::Mat* _pSrcMat, cv::Mat* _pDesMat)
{
	if (!_pSrcMat || !_pDesMat)
	{
		std::cout << __func__ << ", parameter is err." <<std::endl;
		return - 2;
	}

	cv::bilateralFilter(*_pSrcMat, *_pDesMat, m_nDia, m_nDia * 2, m_nDia / 2);

	return 0;
}

int CSBilateralFilter::SetValue(int _Value)
{
	m_nDia = _Value;

	return 0;
}
