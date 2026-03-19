/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.18
描  述: 图像色彩空间转换
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int main()
{
	std::string strWinName = "原图";
	std::string strWinNameGray = "灰度图";
	std::string strWinNameHSV = "色调-饱和度-亮度图";

	cv::Mat cMat = cv::imread("./R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file not exist" << std::endl;
		return -1;
	}

	cv::Mat cMatGray;			//gray图像
	cv::Mat cMatHSV;			//hsv图像

	cv::cvtColor(cMat, cMatHSV, cv::ColorConversionCodes::COLOR_BGR2HSV);
	cv::cvtColor(cMat, cMatGray, cv::ColorConversionCodes::COLOR_BGR2GRAY);

	cv::namedWindow(strWinName);
	cv::namedWindow(strWinNameGray);
	cv::namedWindow(strWinNameHSV);

	//移动窗口
	cv::moveWindow(strWinName, 0, 20);
	cv::moveWindow(strWinNameGray, 10 + cMat.cols, 20);
	cv::moveWindow(strWinNameHSV, 10 + cMat.cols + 10 + cMatGray.cols, 20);

	std::cout << 10 + cMat.cols << ", " << 10 + cMat.cols + 10 + cMatGray.cols;
	cv::imshow(strWinName, cMat);
	cv::imshow(strWinNameGray, cMatGray);
	cv::imshow(strWinNameHSV, cMatHSV);

	cv::imwrite("./灰度图.png", cMatGray);
	cv::imwrite("./色调-饱和度-亮度图.png", cMatHSV);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}

