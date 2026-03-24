/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.23
描  述: 滚动条操作演示
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.23
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

std::string g_strWinName = "原图";

/// <summary>
/// 设置亮度回调函数
/// </summary>
/// <param name="pos"></param>
/// <param name="userdata"></param>
static void MyTrackbarCallback_Light(int pos, void* userdata)
{
	if (!userdata)
	{
		std::cout << __func__ << ", input parameter is err." << std::endl;
		return;
	}

	cv::Mat* pcMat = (cv::Mat*)userdata;

	cv::Mat cMatProc;

	cv::add(*pcMat, cv::Scalar(pos, pos, pos), cMatProc);

	cv::imshow(g_strWinName, cMatProc);
}
/// <summary>
/// 设置对比度回调函数
/// </summary>
/// <param name="pos"></param>
/// <param name="userdata"></param>
static void MyTrackbarCallback_Contrast(int pos, void* userdata)
{
	if (!userdata)
	{
		std::cout << __func__ << ", input parameter is err." << std::endl;
		return;
	}

	cv::Mat* pcMat = (cv::Mat*)userdata;

	cv::Mat cMatProc;

	cv::addWeighted(*pcMat, pos / 50.0, cv::Scalar(0, 0, 0), 0, 0, cMatProc);

	cv::imshow(g_strWinName, cMatProc);
}

int main(int argc, char* argv[])
{
	std::string strTrackBarName_Light = "亮度调节";
	std::string strTrackBarName_Contrast = "对比度调节";
	int nLight = 10;										//亮度
	int nContrast = 50;										//对比度

	cv::Mat cMat = cv::imread("R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file is not exist." << std::endl;
		return EXIT_FAILURE;
	}

	cv::namedWindow(g_strWinName);

	cv::createTrackbar(strTrackBarName_Light, g_strWinName, &nLight, 100, MyTrackbarCallback_Light, &cMat);
	cv::createTrackbar(strTrackBarName_Contrast, g_strWinName, &nContrast, 100, MyTrackbarCallback_Contrast, &cMat);

	cv::imshow(g_strWinName, cMat);
	cv::waitKey(0);

	return EXIT_SUCCESS;
}


