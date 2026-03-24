/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.24
描  述: 键盘响应操作
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
	int nInputKey = 0;
	cv::Mat cMat = cv::imread("R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return EXIT_FAILURE;
	}

	cv::namedWindow("原图");

	cv::imshow("原图", cMat);
	
	std::cout << "Please input key ......" << std::endl;
	
	while (1)
	{
		nInputKey = cv::waitKey(200);

		if(nInputKey != -1)
			std::cout << "Input key is " << nInputKey << std::endl;
	}

	return EXIT_SUCCESS;
}

