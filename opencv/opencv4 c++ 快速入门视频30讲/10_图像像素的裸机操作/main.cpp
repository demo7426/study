/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.24
描  述: 图像像素的逻辑操作
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	cv::Mat cMat_00 = cv::Mat::zeros(cv::Size(256, 256), CV_8UC3);
	cv::Mat cMat_01 = cv::Mat::zeros(cv::Size(256, 256), CV_8UC3);

	cv::rectangle(cMat_00, cv::Rect(100, 100, 80, 80), cv::Scalar(255, 255, 0), -1,cv::LineTypes::LINE_8, 0);
	cv::rectangle(cMat_01, cv::Rect(150, 150, 80, 80), cv::Scalar(0, 255, 255), -1,cv::LineTypes::LINE_8, 0);

	cv::imshow("00", cMat_00);
	cv::imshow("01", cMat_01);

	cv::Mat cMatDst;

	cv::bitwise_and(cMat_00, cMat_01, cMatDst);
	cv::imshow("像素位与操作", cMatDst);
	
	cv::bitwise_or(cMat_00, cMat_01, cMatDst);
	cv::imshow("像素位或操作", cMatDst);

	cv::bitwise_xor(cMat_00, cMat_01, cMatDst);
	cv::imshow("像素位异或操作", cMatDst);
	
	cv::bitwise_not(cMat_00, cMatDst);
	cv::imshow("像素位非操作", cMatDst);

	cv::waitKey(0);
    return EXIT_SUCCESS;
}

