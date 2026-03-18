/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.18
描  述: 图像的读取和显示
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

int main()
{
	std::string strWinName = "show";

	cv::Mat cMat = cv::imread("./R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file not exist" << std::endl;
		return -1;
	}

	//WINDOW_FREERATIO--该图像会尽可能地扩展（没有比例限制）
	//cv::namedWindow(strWinName, cv::WindowFlags::WINDOW_FREERATIO);

	cv::imshow(strWinName, cMat);
	cv::waitKey(0);

	cv::destroyAllWindows();			//销毁所有的窗口，释放资源

	return 0;
}

