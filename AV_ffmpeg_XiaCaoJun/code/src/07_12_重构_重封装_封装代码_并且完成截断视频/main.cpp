/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.27
描  述: 实现一个对MP4格式数据，重封装剪切中间10秒视频并重新计算pts_dts
备  注:
修改记录:

  1.  日期: 2025.08.27
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
#include "xdemux.h"
#include "xmux.h"

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
	AVPacket tAVPacket = { 0 };

	CXDeCode cXDeCode;			//解码对象
	CXDemux cXDemux;			//解封装对象
	CXMux cXMux;				//封装对象

	CXVideo_View* pcXVideo_View = nullptr;
	CXVideo_View::Format eFmt = CXVideo_View::Format::YUV420P;

	AVFrame* ptAVFrame = av_frame_alloc();

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	bool bInitFlag = false;

	if (cXDemux.Create_AVFormatContext(pchURL))
	{
		return EXIT_FAILURE;
	}

	if (cXDemux.GetAVStream_Video())
	{
		AVCodecID eVideoID = cXDemux.GetAVStream_Video()->codecpar->codec_id;							//视频编码器ID
		AVCodecParameters* ptAVCodecParameters = cXDemux.GetAVStream_Video()->codecpar;					//视频编码参数

		//视频解码初始化，因为后续解码是直接发送的AVPacket数据，在此处只能使用cpu解码
		cXDeCode.Create_AVCodecContext(eVideoID, false);
		
		cXDeCode.Set_AVCodecParameters(ptAVCodecParameters);
		
		nRtn = cXDeCode.Open();
		if (nRtn < 0)
		{
			PrintErr(nRtn);
			return EXIT_FAILURE;
		}
	}

	pcXVideo_View = CXVideo_View::Create();

#ifdef __MUX
	////////////////////////////////////重封装////////////////////////////////////
	const char* pchOutURL = "07_12.mp4";

	constexpr double dbBeginSec = 300.0;							//截取开始时间
	constexpr double dbEndSec = dbBeginSec + 10;					//截取结束时间

	cXMux.Create_AVFormatContext(pchOutURL);

	cXMux.SetBeginSec(dbBeginSec);
	cXMux.SetEndSec(dbEndSec);

	cXMux.SetVideoParameters(&cXDemux.GetAVStream_Video()->time_base, (const AVCodecParameters*)cXDemux.GetAVStream_Video()->codecpar);
	cXMux.SetAudioParameters(&cXDemux.GetAVStream_Audio()->time_base, (const AVCodecParameters*)cXDemux.GetAVStream_Audio()->codecpar);

	cXMux.Write_Header(cXDemux.GetAVFormatContext(), cXDemux.GetAVStream_Video(), cXDemux.GetAVStream_Audio());

	//////////////////////////////////////////////////////////////////////////////
#endif // __MUX

	while (1)
	{
		nRtn = cXDemux.Read_Frame(&tAVPacket);
		if (nRtn < 0)
		{
			break; // 读取结束或出错时退出
		}

#ifdef __MUX
		if (cXMux.Write_Frame(&tAVPacket) != 0)
			break;
#else
		if (cXDemux.GetAVStream_Video() && tAVPacket.stream_index == cXDemux.GetAVStream_Video()->index)
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
#endif
	}

	cXDemux.Close();

#ifdef __MUX
	cXMux.Close();
#endif // __MUX

	av_frame_free(&ptAVFrame);

	return EXIT_SUCCESS;
}

