/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.03
描  述: opencv播放rtsp海康摄像头和播放系统摄像头
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
	//std::string strSrcUrl = "rtmp://127.0.0.1:1935/live/test";
	std::string strSrcUrl = "rtsp://127.0.0.1:8554/test";
	std::string strWinName = "video";
	
	cv::VideoCapture cVideoCapture;
	cv::Mat cMat;

	cv::namedWindow(strWinName);

	//if (!cVideoCapture.open(strSrcUrl))			//打开对应的流
	if (!cVideoCapture.open(0))						//打开对应的摄像头
	{
		std::cout << "open is err" << std::endl;
		return -2;
	}

	while (1)
	{
		cVideoCapture.read(cMat);					//read读取出的数据为解码后BGR24格式的原始数据，可以理解为AVFrame

		cv::imshow(strWinName, cMat);
		cv::waitKey(40);
	}

	cVideoCapture.release();

	return 0;
}




