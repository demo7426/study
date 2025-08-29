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

	bool bInitFlag = false;

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

#ifdef __DEMUX
	////////////////////////////////////重封装////////////////////////////////////
	const char* pchOutURL = "07_09_重封装剪切中间10秒视频并重新计算pts_dts.mp4";
	AVFormatContext* ptAVFormatContext_Mux = nullptr;
	AVStream* ptAVStream_Video_Mux = nullptr;						//封装后的视频流
	AVStream* ptAVStream_Audio_Mux = nullptr;						//封装后的音频流

	constexpr double dbBeginSec = 300.0;							//截取开始时间
	constexpr double dbEndSec = dbBeginSec + 10;					//截取结束时间
	long long llBegin_Video_Pts = 0;								//视频开始的时间
	long long llEnd_Video_Pts = 0;									//视频结束的时间	
	long long llBegin_Audio_Pts = 0;								//音频开始的时间
	long long llEnd_Audio_Pts = 0;									//视频结束的时间	

	nRtn = avformat_alloc_output_context2(&ptAVFormatContext_Mux, nullptr, nullptr,
		pchOutURL			//根据文件名推测其封装格式
	);
	PrintErr(nRtn);

	//打开输出IO
	nRtn = avio_open(&ptAVFormatContext_Mux->pb, pchOutURL, AVIO_FLAG_WRITE);
	PrintErr(nRtn);

	//设置编码音视频流参数
	if (ptAVStream_Video)
	{
		ptAVStream_Video_Mux = avformat_new_stream(ptAVFormatContext_Mux, NULL);		//处理有视频流的情况

		ptAVStream_Video_Mux->time_base = ptAVStream_Video->time_base;					//时间基数与原视频一致

		//从解封装复制参数
		avcodec_parameters_copy(ptAVStream_Video_Mux->codecpar, ptAVStream_Video->codecpar);
	}

	if (ptAVStream_Audio)
	{
		ptAVStream_Audio_Mux = avformat_new_stream(ptAVFormatContext_Mux, NULL);		//处理有音频流的情况

		ptAVStream_Audio_Mux->time_base = ptAVStream_Audio->time_base;					//时间基数与原视频一致

		//从解封装复制参数
		avcodec_parameters_copy(ptAVStream_Audio_Mux->codecpar, ptAVStream_Audio->codecpar);
	}

	//写入文件头
	nRtn = avformat_write_header(ptAVFormatContext_Mux, NULL);
	PrintErr(nRtn);

	av_dump_format(ptAVFormatContext_Mux, 0, pchOutURL, 
		1			//上下文时输入还是输出;0--输入;1--输出
	);

	//截取10~20秒之间的音频、视频，取多不去少
	// 假定9 11秒有关键帧，取第9秒
	if (ptAVStream_Video && ptAVStream_Video->time_base.num > 0)
	{
		double t = ptAVStream_Video->time_base.den / ptAVStream_Video->time_base.num;		//den分母/num分子
		llBegin_Video_Pts = dbBeginSec * t;
		llEnd_Video_Pts = dbEndSec * t;
	}	
	
	if (ptAVStream_Audio && ptAVStream_Audio->time_base.num > 0)
	{
		double t = ptAVStream_Audio->time_base.den / ptAVStream_Audio->time_base.num;		//den分母/num分子
		llBegin_Audio_Pts = dbBeginSec * t;
		llEnd_Audio_Pts = dbEndSec * t;
	}

	//seek输入媒体 移动到第10秒的关键帧位置
	if (ptAVStream_Video)
	{
		nRtn = av_seek_frame(ptAVFormatContext, ptAVStream_Video->index, llBegin_Video_Pts, (int)AVSEEK_FLAG_FRAME | (int)AVSEEK_FLAG_BACKWARD);
		PrintErr(nRtn);
	}

	//////////////////////////////////////////////////////////////////////////////
#endif // __DEMUX

	while (1)
	{
		nRtn = av_read_frame(ptAVFormatContext, &tAVPacket);
		if (nRtn < 0) 
		{
			PrintErr(nRtn);
			break; // 读取结束或出错时退出
		}
		
#ifdef __DEMUX
		AVStream* ptAVStream_In = ptAVFormatContext->streams[tAVPacket.stream_index];
		AVStream* ptAVStream_Out = nullptr;
		long long llPtsOffset = 0;

		if (ptAVStream_Video && tAVPacket.stream_index == ptAVStream_Video->index)
		{
			if (tAVPacket.pts < llBegin_Video_Pts)		//过滤dbBeginSec秒前的残留视频包
			{
				av_packet_unref(&tAVPacket);
				continue;
			}

			if (tAVPacket.pts > llEnd_Video_Pts)		//超过第dbEndSec秒退出，只存dbBeginSec~dbEndSec秒
			{
				av_packet_unref(&tAVPacket);
				break;
			}

			ptAVStream_Out = ptAVFormatContext_Mux->streams[0];
			llPtsOffset = llBegin_Video_Pts;
		}
		else if (ptAVStream_Audio && tAVPacket.stream_index == ptAVStream_Audio->index)
		{
			if (tAVPacket.pts > llEnd_Audio_Pts)		//超过第dbEndSec秒退出，只存dbBeginSec~dbEndSec秒
			{
				av_packet_unref(&tAVPacket);
				break;
			}

			if (tAVPacket.pts < llBegin_Audio_Pts)		//过滤dbBeginSec秒前的残留视频包
			{
				av_packet_unref(&tAVPacket);
				continue;
			}

			ptAVStream_Out = ptAVFormatContext_Mux->streams[1];
			llPtsOffset = llBegin_Audio_Pts;
		}
		else
		{
			av_packet_unref(&tAVPacket);
			continue;
		}

		tAVPacket.pts = av_rescale_q_rnd(tAVPacket.pts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.dts = av_rescale_q_rnd(tAVPacket.dts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.duration = av_rescale_q_rnd(tAVPacket.duration, ptAVStream_In->time_base, ptAVStream_Out->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.pos = -1;		//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

		if (ptAVStream_Video && tAVPacket.stream_index == ptAVStream_Video->index)
			std::cout << "视频：";
		else if (ptAVStream_Audio && tAVPacket.stream_index == ptAVStream_Audio->index)
			std::cout << "音频：";

		std::cout << tAVPacket.pts << ", " << tAVPacket.dts << ", " << tAVPacket.size << std::endl;

		nRtn = av_interleaved_write_frame(ptAVFormatContext_Mux, &tAVPacket);		//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
		PrintErr(nRtn);
		av_packet_unref(&tAVPacket);
#else
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
#endif
	}

	avformat_close_input(&ptAVFormatContext);

#ifdef __DEMUX
	av_write_trailer(ptAVFormatContext_Mux);			//写入结尾

	avio_closep(&ptAVFormatContext_Mux->pb);
	avformat_free_context(ptAVFormatContext_Mux);
	ptAVFormatContext_Mux = nullptr;
#endif // __DEMUX

	av_frame_free(&ptAVFrame);

	return EXIT_SUCCESS;
}

