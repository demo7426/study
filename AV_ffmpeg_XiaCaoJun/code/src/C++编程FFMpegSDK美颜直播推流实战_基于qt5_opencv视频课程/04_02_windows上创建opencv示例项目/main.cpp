/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.03
描  述: 创建opencv示例项目;
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.02.03
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

int main()
{
	cv::Mat image = cv::imread("lena.jpg");

	cv::namedWindow("img");
	cv::imshow("img", image);

	cv::waitKey(0);

	return 0;
}




