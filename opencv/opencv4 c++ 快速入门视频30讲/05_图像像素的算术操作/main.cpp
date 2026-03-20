/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.20
描  述: 图像像素的读写操作
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	std::string strWinName = "原图";

	cv::Mat cMat = cv::imread("R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return -2;
	}

	cv::namedWindow(strWinName);
	cv::moveWindow(strWinName, 10, 10);
	cv::imshow(strWinName, cMat);

	//cv::Mat cMatProc = cMat / cv::Scalar(2, 2, 2);			//运算符操作只支持加减除，不支持乘法
	cv::Mat cMatProc;

	//cv::add(cMat, cv::Scalar(100, 100, 100), cMatProc);		//加法操作
	//cv::subtract(cMat, cv::Scalar(100, 100, 100), cMatProc);	//减法操作
	cv::multiply(cMat, cv::Scalar(2, 2, 2), cMatProc);			//乘法操作
	//cv::divide(cMat, cv::Scalar(2, 2, 2), cMatProc);			//除法操作

	cv::namedWindow("处理后的图");
	cv::moveWindow("处理后的图", 20 + cMatProc.cols, 10);
	cv::imshow("处理后的图", cMatProc);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
