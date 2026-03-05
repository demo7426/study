/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.05
描  述: opencv双边滤波磨皮算法调用并测试性能
备  注:
修改记录:

  1.  日期: 2026.03.05
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/
#include <iostream>
#include <chrono>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

int main()
{
	std::string strWinName = "R-C";						//数据处理前的窗口名称
	std::string strWinName_Process = "R-C_process";		//数据处理后的窗口名称

	cv::Mat cMat;
	cv::Mat cMat_Process;

	int nDiameter = 18;									//图像处理时的滤波直径

	cMat = cv::imread("./R-C.png");
	if (cMat.empty())
	{
		std::cout << "file is not exist" << std::endl;
		return -2;
	}

	cv::namedWindow(strWinName);
	cv::moveWindow(strWinName, 100, 100);
	
	cv::namedWindow(strWinName_Process);
	cv::moveWindow(strWinName_Process, 200 + cMat.cols, 100);

	while (1)
	{
		std::chrono::steady_clock::time_point cStart = std::chrono::steady_clock::now();

		cv::bilateralFilter(cMat, cMat_Process, nDiameter, nDiameter * 2, nDiameter / 2);

		std::chrono::steady_clock::time_point cEnd = std::chrono::steady_clock::now();
		std::chrono::steady_clock::duration cElapsed = cEnd - cStart;
		long long llElapsed_Microseconds = std::chrono::duration_cast<std::chrono::microseconds>(cElapsed).count();
		std::cout << "滤波直径 = " << nDiameter << ", 滤波消耗的时间 = " << llElapsed_Microseconds / 1000.0 << " ms" << std::endl;

		cv::imshow(strWinName, cMat);
		cv::imshow(strWinName_Process, cMat_Process);

		auto nInputKey = cv::waitKey(0);			//注意鼠标光标必须先选中窗口，opencv框架才可以接收到按键输入
		if (nInputKey == 'q')
			nDiameter += 1;
		else if (nInputKey == 'w')
			nDiameter -= 1;
		else{}
	}

	return 0;
}
