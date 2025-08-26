/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.26
描  述: 实现一个对MP4格式其内部视频数据的解封装、渲染
备  注: 
修改记录:

  1.  日期: 2025.08.26
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xdecode.h"
#include "xvideo_view.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
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
	const char* pchURL = "1.mp4";						//媒体文件
	AVFormatContext* ptAVFormatContext = nullptr;
	AVPacket tAVPacket = { 0 };
	AVStream* ptAVStream_Video = nullptr;				//视频流
	AVStream* ptAVStream_Audio = nullptr;				//音频流

	CXDeCode cXDeCode;

	CXVideo_View* pcXVideo_View = nullptr;
	CXVideo_View::Format eFmt = CXVideo_View::Format::YUV420P;

	AVFrame* ptAVFrame = av_frame_alloc();

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	nRtn = avformat_open_input(
		&ptAVFormatContext, 
		pchURL,
		nullptr,		//封装器格式;nullptr--自动探测，根据后缀名或者文件头判定其格式
		nullptr			//参数设置，rtsp才需要设置
	);
	PrintErr(nRtn);

	//获取媒体格式信息 无头部格式
	nRtn = avformat_find_stream_info(ptAVFormatContext, nullptr);
	PrintErr(nRtn);

	//打印封装信息
	av_dump_format(
		ptAVFormatContext, 
		0, 
		pchURL, 
		0		//上下文时输入还是输出;0--输入;1--输出
	);

	for (int i = 0; i < ptAVFormatContext->nb_streams; i++)
	{
		if (ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			ptAVStream_Video = ptAVFormatContext->streams[i];

			std::cout << "------视频------" << std::endl;
			std::cout <<"	width：" << ptAVStream_Video->codecpar->width << std::endl;
			std::cout <<"	height：" << ptAVStream_Video->codecpar->height << std::endl;
		}
		else if (ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			ptAVStream_Audio = ptAVFormatContext->streams[i];

			std::cout << "------音频------" << std::endl;
			std::cout << "	sample_rate：" << ptAVStream_Audio->codecpar->sample_rate << std::endl;
		}
	}

	if (ptAVStream_Video)
	{
		AVCodecID eVideoID = ptAVStream_Video->codecpar->codec_id;								//视频编码器ID
		AVCodecParameters* ptAVCodecParameters = ptAVStream_Video->codecpar;					//视频编码参数

		//视频解码初始化，因为后续解码是直接发送的AVPacket数据，在此处只能使用cpu解码
		cXDeCode.Create_AVCodecContext(eVideoID, false);										
		nRtn = avcodec_parameters_to_context(cXDeCode.GetAVCodecContext(), ptAVCodecParameters);		//解封装的视频编码参数，传递给解码上下文
		if (nRtn < 0) 
		{
			PrintErr(nRtn);
			return EXIT_FAILURE;
		}

		nRtn = cXDeCode.Open();
		if (nRtn < 0)
		{
			PrintErr(nRtn);
			return EXIT_FAILURE;
		}
	}

	pcXVideo_View = CXVideo_View::Create();

	bool bInitFlag = false;

	while (1)
	{
		nRtn = av_read_frame(ptAVFormatContext, &tAVPacket);
		if (nRtn < 0) 
		{
			PrintErr(nRtn);
			break; // 读取结束或出错时退出
		}
		
		if (ptAVStream_Video && tAVPacket.stream_index == ptAVStream_Video->index)
		{
			if (!cXDeCode.Send_AVPacket(&tAVPacket))
				continue;

			if (!cXDeCode.Recv_AVFrame(ptAVFrame))
				continue;

			//std::cout << ptAVFrame->pts << " ";

			if (!bInitFlag)
			{
				switch (ptAVFrame->format)
				{
				case AVPixelFormat::AV_PIX_FMT_RGBA:
					eFmt = CXVideo_View::Format::RGBA;
					break;
				case AVPixelFormat::AV_PIX_FMT_ARGB:
					eFmt = CXVideo_View::Format::ARGB;
					break;
				case AVPixelFormat::AV_PIX_FMT_YUV420P:
					eFmt = CXVideo_View::Format::YUV420P;
					break;
				case AVPixelFormat::AV_PIX_FMT_NV12:
					eFmt = CXVideo_View::Format::NV12;
					break;
				default:
					break;
				}

				pcXVideo_View->Init(ptAVFrame->width, ptAVFrame->height, eFmt, nullptr);
				bInitFlag = true;
			}

			pcXVideo_View->DrawFrame(ptAVFrame);
			nFrameCounter++;

			av_frame_unref(ptAVFrame);
		}

		/*if (ptAVStream_Video && tAVPacket.stream_index == ptAVStream_Video->index)
			std::cout << "视频：";
		else if (ptAVStream_Audio && tAVPacket.stream_index == ptAVStream_Audio->index)
			std::cout << "音频：";

		std::cout << tAVPacket.pts << ", " << tAVPacket.dts << ", " << tAVPacket.size << std::endl;*/

		av_packet_unref(&tAVPacket);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	

		cEnd_TimePoint = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cEnd_TimePoint - cStart_TimePoint).count() >= 1000)
		{
			std::cout << "每秒帧数：" << nFrameCounter << std::endl;

			nFrameCounter = 0;
			cStart_TimePoint = cEnd_TimePoint;
		}
	}

	avformat_close_input(&ptAVFormatContext);

	av_frame_free(&ptAVFrame);

	return EXIT_SUCCESS;
}

