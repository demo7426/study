/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.20
描  述: 图像像素的读写操作
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.03.20
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "opencv2/opencv.hpp"

int main()
{
	std::string strWinName = "原图";

	cv::Mat cMat = cv::imread("R-C.png");
	if (cMat.empty())
	{
		std::cout << __func__ << ", file is not exist" << std::endl;
		return -2;
	}

	cv::namedWindow(strWinName);
	cv::moveWindow(strWinName, 10, 10);
	cv::imshow(strWinName, cMat);

	int nWidth = cMat.cols;
	int nHeight = cMat.rows;
	int nChannels = cMat.channels();

	//使用右值进行像素读写
	for (size_t row = 0; row < nHeight; row++)
	{
		for (size_t col = 0; col < nWidth; col++)
		{
			if (nChannels == 1)				//灰度图像
			{
				uchar uchPix = cMat.at<uchar>(row, col);
				cMat.at<uchar>(row, col) = 255 - uchPix;
			}
			else if (nChannels == 3)		//彩色图像
			{
				cv::Vec3b vecBGR = cMat.at<cv::Vec3b>(row, col);
				cMat.at<cv::Vec3b>(row, col)[0] = 255 - vecBGR[0];
				cMat.at<cv::Vec3b>(row, col)[1] = 255 - vecBGR[1];
				cMat.at<cv::Vec3b>(row, col)[2] = 255 - vecBGR[2];
			}
		}
	}

	cv::namedWindow("右值处理后的图");
	cv::moveWindow("右值处理后的图", 20 + cMat.cols, 10);
	cv::imshow("右值处理后的图", cMat);
	
	//使用内存进行像素读写
	for (size_t row = 0; row < nHeight; row++)
	{
		uchar* puchCurRow = cMat.ptr<uchar>(row);

		for (size_t col = 0; col < nWidth; col++)
		{
			if (nChannels == 1)				//灰度图像
			{
				uchar uchPix = *puchCurRow;
				*puchCurRow++ = 255 - uchPix;
			}
			else if (nChannels == 3)		//彩色图像
			{
				*puchCurRow++ = 255 - *puchCurRow;
				*puchCurRow++ = 255 - *puchCurRow;
				*puchCurRow++ = 255 - *puchCurRow;
			}
		}
	}

	cv::namedWindow("内存处理后的图");
	cv::moveWindow("内存处理后的图", 30 + cMat.cols * 2, 10);
	cv::imshow("内存处理后的图", cMat);

	cv::waitKey(0);

	cv::destroyAllWindows();

	return 0;
}
