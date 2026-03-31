/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.31
描  述: 随机数与随机颜色
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

	int nWidth = 300;			//宽度
	int nHeight = 400;			//高度

	cv::RNG cRng;

	cv::Mat cMat = cv::Mat::zeros(cv::Size(nWidth, nHeight), CV_8UC3);
	int nInputKey = 0;			//输入的按键值

	while (1)
	{
		nInputKey = cv::waitKey(100);
		if (nInputKey == 27)				//esc键退出
		{
			break;
		}

		int x1 = cRng.uniform(0, nWidth);
		int y1 = cRng.uniform(0, nHeight);
		int x2 = cRng.uniform(0, nWidth);
		int y2 = cRng.uniform(0, nHeight);
		int r = cRng.uniform(0, 255);
		int g = cRng.uniform(0, 255);
		int b = cRng.uniform(0, 255);

		cv::line(cMat, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(b, g, r), 1, cv::LINE_AA, 0);
		cv::imshow("随机绘制演示", cMat);

	}

	cv::destroyAllWindows();

	return EXIT_SUCCESS;
}


