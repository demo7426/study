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
	std::string strDesUrl = "rtsp://127.0.0.1:8554/output";			//输出url

	cv::Mat cMat;
	cv::VideoCapture cVideoCapture;

	SwsContext* ptSwsContext = nullptr;

	AVFrame* ptAVFrame = av_frame_alloc();
	if (!ptAVFrame)
	{
		std::cout << "av_frame_alloc is err" << std::endl;
		return -2;
	}

	AVPacket* ptAVPacket = av_packet_alloc();
	if (!ptAVPacket)
	{
		std::cerr << "av_packet_alloc is err" << std::endl;
		return -2;
	}

	AVCodec* ptAVCodec = nullptr;
	AVCodecContext* ptAVCodecContext = nullptr;

	int64_t llPts = 0;

	AVFormatContext* ptAVFormatContext = nullptr;

	cv::namedWindow(strWinName);

	try
	{
		if (!cVideoCapture.open(strSrcUrl))										//打开对应的流
			//if (!cVideoCapture.open(0))										//打开对应的摄像头
		{
			throw std::exception("open is err");
		}

		ptAVCodec = avcodec_find_encoder(AV_CODEC_ID_H264);			//查找编码器
		if (!ptAVCodec)
		{
			throw std::exception("avcodec_find_encoder is err");
		}

		ptAVCodecContext = avcodec_alloc_context3(ptAVCodec);		//分配编码器上下文
		if (!ptAVCodecContext)
		{
			throw std::exception("avcodec_alloc_context3 is err");
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

		ptAVCodecContext->width = nSrcW;
		ptAVCodecContext->height = nSrcH;
		ptAVCodecContext->time_base = { 1, nSrcFps };
		ptAVCodecContext->pix_fmt = AVPixelFormat::AV_PIX_FMT_YUV420P;

		ptAVCodecContext->bit_rate = 1000000;	// 码率：1Mbps（可根据需求调整）
		ptAVCodecContext->gop_size = 10;		// 每10帧一个I帧
		ptAVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;	//GLOBAL_HEADER 是为了让编码参数（SPS/PPS）脱离帧流，放入封装头部，以适配非裸流封装格式
		ptAVCodecContext->max_b_frames = 1;		// B帧数量
		ptAVCodecContext->qmin = 18;			// 最小量化值
		ptAVCodecContext->qmax = 40;			// 最大量化值

		ptAVCodecContext->thread_count = std::thread::hardware_concurrency();

		nRtn = avcodec_open2(ptAVCodecContext, nullptr, nullptr);
		if (nRtn)
		{
			throw std::exception("avcodec_open2 is err");
		}

		nRtn = avformat_alloc_output_context2(&ptAVFormatContext, nullptr, "rtsp", strDesUrl.data());
		if (nRtn)
		{
			throw std::exception("avformat_alloc_output_context2 is err");
		}

		AVStream* ptAVStream = avformat_new_stream(ptAVFormatContext, nullptr);
		if (!ptAVStream)
		{
			throw std::exception("avformat_new_stream is err");
		}

		//复制配置信息
		avcodec_parameters_from_context(ptAVStream->codecpar, ptAVCodecContext);
		// ptAVStream->time_base = ptAVFormatContext_In->streams[i]->time_base;								//时间基数与原视频一致

		// 移除废弃的ptAVStream->codec->codec_tag = 0; 新版无需操作codec成员
		ptAVStream->codecpar->codec_tag = 0;

		//打印输出封装信息
		av_dump_format(ptAVFormatContext, 0, strDesUrl.data(), 1);

		AVDictionary* opt = nullptr;

		// 强制使用 TCP 推流（推荐）
		av_dict_set(&opt, "rtsp_transport", "tcp", 0);

		// 最大延迟
		av_dict_set(&opt, "max_delay", "500000", 0);

		//写入文件头
		nRtn = avformat_write_header(ptAVFormatContext, &opt);
		av_dict_free(&opt);
		if (nRtn < 0)
		{
			throw std::exception("avformat_write_header is err");
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

			ptAVFrame->pts = llPts++;
			if (avcodec_send_frame(ptAVCodecContext, ptAVFrame))		//发送未压缩数据到线程中压缩
			{
				av_frame_unref(ptAVFrame);
				continue;
			}

			nRtn = avcodec_receive_packet(ptAVCodecContext, ptAVPacket);
			if (nRtn == AVERROR(EAGAIN) || nRtn == AVERROR_EOF)
			{
				av_frame_unref(ptAVFrame);
				continue;
			}

			std::cout << ptAVPacket->size << " ";

			ptAVPacket->pts = av_rescale_q_rnd(ptAVPacket->pts, ptAVCodecContext->time_base, ptAVStream->time_base,
				(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
			ptAVPacket->dts = av_rescale_q_rnd(ptAVPacket->dts, ptAVCodecContext->time_base, ptAVStream->time_base,
				(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
			ptAVPacket->duration = av_rescale_q_rnd(ptAVPacket->duration, ptAVCodecContext->time_base, ptAVStream->time_base,
				(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
			ptAVPacket->pos = -1;				//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

			//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
			nRtn = av_interleaved_write_frame(ptAVFormatContext, ptAVPacket);
			if (nRtn != 0)
			{
				std::cout << "# ";
				continue;
			}

			//av_packet_unref(ptAVPacket);

			av_frame_unref(ptAVFrame);

			cv::imshow(strWinName, cMat);
			cv::waitKey(1);
		}

		//写入文件尾（必须执行，否则输出文件损坏无法播放）
		av_write_trailer(ptAVFormatContext);

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	if (ptAVPacket)
	{
		av_packet_free(&ptAVPacket);
		ptAVPacket = nullptr;
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

	if (ptAVCodecContext)
	{
		avcodec_close(ptAVCodecContext);

		avcodec_free_context(&ptAVCodecContext);
		ptAVCodecContext = nullptr;
	}
	
	if (ptAVFormatContext)
	{
		avformat_free_context(ptAVFormatContext);
		ptAVFormatContext = nullptr;
	}

	return 0;
}
