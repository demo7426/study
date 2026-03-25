/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.25
描  述: 通道分离与合并
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
	std::vector<cv::Mat> vecMat;

	cv::Mat cSrcMat = cv::imread("R-C.png");
	if (cSrcMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return EXIT_FAILURE;
	}

	cv::split(cSrcMat, vecMat);

	cv::imshow("蓝色", vecMat[0]);
	cv::imshow("绿色", vecMat[1]);
	cv::imshow("红色", vecMat[2]);

	cv::Mat cDstMat;
	vecMat[0] = 0;
	cv::merge(vecMat, cDstMat);
	cv::imshow("合并", cDstMat);

	int nFromTo[] = { 0, 2, 1, 1, 2, 0 };

	cv::mixChannels(&cSrcMat, 1, &cDstMat, 1, nFromTo, 3);
	cv::imshow("通道混合", cDstMat);

	cv::waitKey(0);

	return EXIT_SUCCESS;
}


