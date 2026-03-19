/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.19
描  述: 图像对象的创建与赋值
备  注: 使用的是opencv4.12.0版本
			cv::Mat拷贝构造函数，数据地址指向的是同一处，类似于浅拷贝
			cv::Mat clone\copyTo函数，数据也会被重新复制一份，类似于深拷贝
修改记录:

  1.  日期: 2026.03.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	cv::Mat cMat = cv::Mat::zeros(cv::Size(400, 300), CV_8UC3);
	cMat = cv::Scalar(0, 0, 255);

	std::cout << "width = " << cMat.cols << ", height = " << cMat.rows << ", channels = " << cMat.channels() << std::endl;
	//std::cout << cMat << std::endl;		//可以打印出矩阵信息

	cv::Mat cMat01 = cMat.clone();			//等价于cMat.copyTo(cMat02); 深拷贝
	cMat01 = cv::Scalar(0, 255, 0);			//cv::Mat赋值操作
	cv::imshow("02", cMat);

	cv::Mat cMat02 = cMat;
	cMat02 = cv::Scalar(255, 0, 0);			//修改cMat、cMat01共有的数据
	cv::imshow("01", cMat);

	//cv::Mat赋值操作
	cv::Mat cMat03 = (cv::Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);

	cv::waitKey(0);

	cv::destroyAllWindows();

    return 0;
}


