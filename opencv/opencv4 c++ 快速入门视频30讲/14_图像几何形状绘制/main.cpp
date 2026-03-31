/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.31
描  述: 图像几何形状绘制
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.31
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	// 只显示错误及以上级别的日志，屏蔽 INFO
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_WARNING);

	cv::Mat cSrcMat = cv::imread("R-C.png");
	if (cSrcMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return EXIT_FAILURE;
	}

	cv::Mat cMat = cv::Mat::zeros(cSrcMat.size(), cSrcMat.type());
	cv::Mat cDstMat;

	cv::rectangle(cMat, cv::Rect(100, 100, 250, 300), cv::Scalar(0, 0, 255), -1, 8, 0);					//绘制矩形
	cv::circle(cMat, cv::Point(350, 400), 15, cv::Scalar(255, 0, 0), -1, 8, 0);							//绘制圆形
	cv::line(cMat, cv::Point(100, 100), cv::Point(350, 400), cv::Scalar(0, 255, 0), 4, cv::LINE_AA, 0);	//绘制线段

	//绘制椭圆
	cv::RotatedRect cRotatedRect;
	cRotatedRect.center = cv::Point2f(200, 200);
	cRotatedRect.size = cv::Size2f(100, 200);
	cRotatedRect.angle = 90.0;

	cv::ellipse(cMat, cRotatedRect, cv::Scalar(0, 255, 255), 2, cv::LINE_AA);

	cv::addWeighted(cSrcMat, 0.7, cMat, 0.3, 0, cDstMat);

	cv::imshow("合并后", cDstMat);
	cv::waitKey(0);

	cv::destroyAllWindows();

	return EXIT_SUCCESS;
}


