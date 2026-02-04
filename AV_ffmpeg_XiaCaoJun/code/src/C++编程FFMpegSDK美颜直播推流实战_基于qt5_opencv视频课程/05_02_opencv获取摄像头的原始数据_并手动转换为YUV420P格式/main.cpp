/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.03
描  述: opencv获取摄像头的原始数据，并手动转换为YUV420P格式
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.02.03
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavcodec/codec.h"
}

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib, "avutil.lib")

//打印错误信息
static void PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}

int main()
{
	std::string strSrcUrl = "rtsp://127.0.0.1:8554/test";
	const std::string strWinName = "video";

	cv::Mat cMat;
	cv::VideoCapture cVideoCapture;

	SwsContext* ptSwsContext = nullptr;

	AVFrame* ptAVFrame = av_frame_alloc();
	if (!ptAVFrame)
	{
		std::cout << "av_frame_alloc is err" << std::endl;
		return -2;
	}

	cv::namedWindow(strWinName);

	try
	{
		//if (!cVideoCapture.open(strSrcUrl))			//打开对应的流
		if (!cVideoCapture.open(0))						//打开对应的摄像头
		{
			throw std::exception("open is err");
		}
		int nSrcW = cVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		int nSrcH = cVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		
		uint8_t* uchInData[AV_NUM_DATA_POINTERS] = { 0 };
		int nInSize[AV_NUM_DATA_POINTERS] = { 0 };
		int nInHeight = 0;								//输入高度
		int nOutHeight = 0;								//输出高度

		ptSwsContext = sws_getCachedContext(ptSwsContext,
			nSrcW, nSrcH, AVPixelFormat::AV_PIX_FMT_BGR24,
			nSrcW, nSrcH, AVPixelFormat::AV_PIX_FMT_YUV420P,
			SWS_BILINEAR,	//选择支持变化的算法，双线性插值
			0, 0, 0			//过滤器参数
		);
		if (!ptSwsContext)						
		{
			throw std::exception("sws_getCachedContext is err");
		}

		while (1)
		{
			if (!cVideoCapture.grab())					//获取当前帧
				continue;

			//对当前帧进行解码操作
			//cMat的数据为解码后BGR24格式的原始数据，可以理解为AVFrame
			if (!cVideoCapture.retrieve(cMat))			
				continue;

			uchInData[0] = cMat.data;
			nInSize[0] = cMat.cols * cMat.elemSize();
			nInHeight = cMat.rows;

			//输出的AVFrame结构
			ptAVFrame->width = cMat.cols;
			ptAVFrame->height = cMat.rows;
			ptAVFrame->format = AVPixelFormat::AV_PIX_FMT_YUV420P;

			//分配空间
			int nRet = av_frame_get_buffer(ptAVFrame,
				32										//如果为0，则使用默认的32字节对齐
			);
			if (nRet)
			{
				av_frame_free(&ptAVFrame);
				ptAVFrame = nullptr;

				std::cout << "av_frame_get_buffer is err" << std::endl;
				PrintErr(nRet);
				return -2;
			}

			ptAVFrame->linesize[0] = cMat.cols;
			ptAVFrame->linesize[1] = cMat.cols / 4;
			ptAVFrame->linesize[2] = cMat.cols / 4;

			//BGR32位数据->YUV420P数据
			nOutHeight = sws_scale(ptSwsContext,
				uchInData,
				nInSize,
				0,							//用于多层图像，当前输入0忽略
				nInHeight,
				ptAVFrame->data,
				ptAVFrame->linesize
			);

			std::cout << "nOutHeight = " << nOutHeight << std::endl;

			av_frame_unref(ptAVFrame);

			cv::imshow(strWinName, cMat);
			cv::waitKey(1);
		}

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	if (ptAVFrame)
	{
		av_frame_free(&ptAVFrame);
		ptAVFrame = nullptr;
	}

	if (cVideoCapture.isOpened())
		cVideoCapture.release();

	if (ptSwsContext)
	{
		sws_freeContext(ptSwsContext);
		ptSwsContext = nullptr;
	}


	return 0;
}
