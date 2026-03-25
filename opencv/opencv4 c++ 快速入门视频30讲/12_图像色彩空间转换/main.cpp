/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.25
描  述: 图像色彩空间转换
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.25
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <vector>

#include "opencv2/opencv.hpp"

int main()
{
	cv::Mat cSrcMat;
	cv::Mat cHsvMat;
	cv::Mat cMask;

	cSrcMat = cv::imread("R-C-Green.png");
	if (cSrcMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return EXIT_FAILURE;
	}

	cv::imshow("原图", cSrcMat);

	cv::cvtColor(cSrcMat, cHsvMat, cv::ColorConversionCodes::COLOR_BGR2HSV);
	
	cv::inRange(cHsvMat, cv::Scalar(35, 43, 46), cv::Scalar(77, 255, 255), cMask);
	cv::bitwise_not(cMask, cMask);

	cv::imshow("轮廓提取", cMask);

	cv::Mat cRedBack = cv::Mat::zeros(cSrcMat.size(), cSrcMat.type());
	cRedBack = cv::Scalar(40, 40, 200);

	cSrcMat.copyTo(cRedBack, cMask);

	cv::imshow("roi区域提取", cRedBack);

	cv::waitKey(0);

	return EXIT_SUCCESS;
}


