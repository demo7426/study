/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.03
描  述: 遍历修改连续的Mat图像空间
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
	cv::Mat mat(1080, 1980, CV_8UC3);			//CV_8UC3对应的是BGR32位

	//返回矩阵元素的字节数该方法返回矩阵元素的字节数。例如，如果矩阵类型为 CV16SC3 ，则该方法返回 3 * sizeof(短整型) 或 6 。
	int nEs = mat.elemSize();					//矩阵元素的字节数
	int nSize = mat.rows * mat.cols * nEs;		//像素点数量

	for (size_t i = 0; i < nSize; i += 3)		//必须是连续空间才可以如下操作
	{
		mat.data[i] = 255;		//B
		mat.data[i + 1] = 0;	//G
		mat.data[i + 2] = 0;	//R
	}

	cv::namedWindow("mat");
	cv::imshow("mat", mat);

	cv::waitKey(0);

	return 0;
}




