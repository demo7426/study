/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.11
描  述: opencv获取摄像头的原始数据，并手动转换为YUV420P格式，重新编码后，推流
备  注: 使用的是opencv4.12.0版本
修改记录:

  1.  日期: 2026.02.11
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavcodec/codec.h"
}

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "sencode.h"
#include "smux.h"

#pragma comment(lib, "avformat.lib")
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
	int nRtn = 0;
	//std::string strSrcUrl = "rtsp://admin:level@12@10.0.0.170:554/Stream";
	std::string strSrcUrl = "D:/BaiduNetdiskDownload/mksz279-2022年经典再升级-FFmpeg5.0核心技术精讲，打造音视频播放器【完结】/{1}--第1章学习指南【课程提供200+问题与答案库】/[1.1]--1-2FFmpeg5.0-课程导学【瑞客论坛 www.ruike1.com】.mp4";
	const std::string strWinName = "video";
	//std::string strDesUrl = "rtsp://127.0.0.1:8554/output";				//输出url
	std::string strDesUrl = "rtmp://127.0.0.1:1935/live/test";;			//输出url

	cv::Mat cMat;
	cv::VideoCapture cVideoCapture;

	SwsContext* ptSwsContext = nullptr;

	AVFrame* ptAVFrame = av_frame_alloc();
	if (!ptAVFrame)
	{
		std::cout << "av_frame_alloc is err" << std::endl;
		return -2;
	}

	AVPacket* ptAVPacket = nullptr;

	CSEncode cSEncode;
	CSMux cSMux;

	cv::namedWindow(strWinName);

	try
	{
		if (!cVideoCapture.open(strSrcUrl))										//打开对应的流
			//if (!cVideoCapture.open(0))										//打开对应的摄像头
		{
			throw std::exception("open is err");
		}

		if (cSEncode.Init(CSEncode::SAVCodecID::H264))
		{
			throw std::exception("CSEncode init is err");
		}

		int nSrcW = cVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		int nSrcH = cVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		int nSrcFps = cVideoCapture.get(cv::CAP_PROP_FPS);

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

		if (cSEncode.Open(nSrcW, nSrcH, nSrcFps, CSEncode::SAVPixelFormat::YUV420P))
		{
			throw std::exception("CSEncode Open is err");
		}

		if (cSMux.Init(strDesUrl.data(), cSEncode.GetAVCodecContext()))
		{
			throw std::exception("CSMux init is err");
		}
		
		if (cSMux.Write_Header())
		{
			throw std::exception("CSMux Write_Header is err");
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

			//BGR32位数据->YUV420P数据
			nOutHeight = sws_scale(ptSwsContext,
				uchInData,
				nInSize,
				0,							//用于多层图像，当前输入0忽略
				nInHeight,
				ptAVFrame->data,
				ptAVFrame->linesize
			);

			ptAVPacket = cSEncode.SendFrame(ptAVFrame);
			if (!ptAVPacket)		//发送未压缩数据到线程中压缩
			{
				av_frame_unref(ptAVFrame);
				continue;
			}

			std::cout << ptAVPacket->size << " ";

			cSMux.Write_Packet(ptAVPacket);

			if (ptAVPacket)
			{
				av_packet_free(&ptAVPacket);
				ptAVPacket = nullptr;
			}

			av_frame_unref(ptAVFrame);

			cv::imshow(strWinName, cMat);
			cv::waitKey(1);
		}

		auto vecAVPacket = cSEncode.RecvAll_AVPacketData();			//接收残留的所有数据
		for (auto it : vecAVPacket)
		{
			std::cout << it->size << " ";

			cSMux.Write_Packet(it);

			if (it)
			{
				av_packet_free(&it);
				it = nullptr;
			}
		}

		cSEncode.Close();
		cSMux.Close();
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
