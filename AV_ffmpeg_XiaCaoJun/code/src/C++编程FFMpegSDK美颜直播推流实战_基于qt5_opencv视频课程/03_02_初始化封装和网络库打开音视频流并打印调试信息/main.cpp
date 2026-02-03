/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.01
描  述: 初始化封装和网络库打开音视频流并打印调试信息
备  注:
修改记录:

  1.  日期: 2026.02.01
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "debug.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
#include <libavutil/time.h>
}

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

int Test00()
{
	int nRtn = 0;
	const char* pchInUrl = "../01-斗地主项目介绍.mp4";									//输入文件
	const char* pchOutUrl = "../output.mp4";											//输出文件

	AVFormatContext* ptAVFormatContext_In = nullptr;
	AVFormatContext* ptAVFormatContext_Out = nullptr;

	//初始化 libavformat 并注册所有的封装器、解封装器和协议。
	//av_register_all();

	//初始化网络库
	avformat_network_init();

	//打开文件，解封装文件头
	nRtn = avformat_open_input(
		&ptAVFormatContext_In,
		pchInUrl,
		nullptr,					//nullptr--根据文件后缀名进行格式推测
		nullptr
	);
	if (nRtn)
	{
		PrintErr(nRtn);
		return nRtn;
	}

	DEBUG(DEBUG_LEVEL_INFO, "Open %s is success\n", pchInUrl);

	//获取音频、视频流信息
	nRtn = avformat_find_stream_info(ptAVFormatContext_In, nullptr);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//打印封装信息
	av_dump_format(ptAVFormatContext_In, 0, pchInUrl, 0);

	////////////////////////////////////输出流////////////////////////////////////

	//RTMP 推流的封装格式固定为FLV，但你的 RTMP 地址无文件后缀，avformat_alloc_output_context2无法自动推断格式，必须手动指定format_name="flv"
	nRtn = avformat_alloc_output_context2(&ptAVFormatContext_Out, nullptr, nullptr, pchOutUrl);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//配置输出流
	for (size_t i = 0; i < ptAVFormatContext_In->nb_streams; i++)
	{
		auto codec_type = ptAVFormatContext_In->streams[i]->codecpar->codec_type;
		// 关键2：过滤非音视频流（仅保留视频、音频，舍弃tmcd等数据/字幕流）
		if (codec_type != AVMEDIA_TYPE_VIDEO && codec_type != AVMEDIA_TYPE_AUDIO)
		{
			continue;
		}

		AVStream* ptAVStream = avformat_new_stream(ptAVFormatContext_Out, nullptr);
		if (!ptAVStream)
		{
			DEBUG(DEBUG_LEVEL_ERROR, "avformat_new_stream is err\n");

			avformat_close_input(&ptAVFormatContext_In);
			ptAVFormatContext_In = nullptr;

			avformat_free_context(ptAVFormatContext_Out);
			ptAVFormatContext_Out = nullptr;

			return -1;
		}

		//复制配置信息
		avcodec_parameters_copy(ptAVStream->codecpar, ptAVFormatContext_In->streams[i]->codecpar);

		// 移除废弃的ptAVStream->codec->codec_tag = 0; 新版无需操作codec成员
		//ptAVStream->codec->codec_tag = 0;
	}

	DEBUG(DEBUG_LEVEL_INFO, "");

	//打印输出封装信息
	av_dump_format(ptAVFormatContext_Out, 0, pchOutUrl, 1);

	//打开输出IO
	nRtn = avio_open(&ptAVFormatContext_Out->pb, pchOutUrl, AVIO_FLAG_WRITE);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avio_open is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;

		return -1;
	}

	//写入文件头
	nRtn = avformat_write_header(ptAVFormatContext_Out, NULL);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avformat_write_header is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;
		return nRtn;
	}

	AVPacket tAVPacket = { 0 };
	int64_t llStartTime = av_gettime_relative();

	for (;;)
	{
		nRtn = av_read_frame(ptAVFormatContext_In, &tAVPacket);
		if (nRtn < 0)
		{
			std::cout << "- ";
			break;
		}

		tAVPacket.pts = av_rescale_q_rnd(tAVPacket.pts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.dts = av_rescale_q_rnd(tAVPacket.dts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.duration = av_rescale_q_rnd(tAVPacket.duration, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.pos = -1;		//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

		std::cout << tAVPacket.pts << " ";

		//视频帧
		if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			AVRational tTimebase_Video = ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base;
			auto llInterval = av_gettime_relative() - llStartTime;														//系统时间间隔；单位：us

			auto llCurPts_Video = av_rescale_q(tAVPacket.pts, tTimebase_Video, { 1, AV_TIME_BASE });
			auto llTime_Video = llCurPts_Video;				//单位：us

			if (llTime_Video > llInterval)
			{
				av_usleep(llTime_Video - llInterval);
			}
		}

		//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
		nRtn = av_interleaved_write_frame(ptAVFormatContext_Out, &tAVPacket);
		if (nRtn != 0)
		{
			std::cout << "# ";
			break;
		}
	}

	// 10. 关键：写入文件尾（必须执行，否则输出文件损坏无法播放）
	av_write_trailer(ptAVFormatContext_Out);


	avformat_close_input(&ptAVFormatContext_In);
	ptAVFormatContext_In = nullptr;

	avformat_free_context(ptAVFormatContext_Out);
	ptAVFormatContext_Out = nullptr;

	return 0;
}

/// <summary>
/// rtmp推流测试
/// </summary>
/// <returns></returns>
int Test01()
{
	int nRtn = 0;
	//const char* pchInUrl = "../01-斗地主项目介绍.mp4";											//输入文件
	const char* pchInUrl = "../G.E.M.邓紫棋 - 夜的尽头.mp4";											//输入文件
	const char* pchOutUrl = "rtmp://127.0.0.1:1935/live/test";									//输出文件；rtmp url必须是 rtmp://server/app/stream_name
	//const char* pchOutUrl = "rtsp://127.0.0.1:8554/test";										//输出文件	

	AVFormatContext* ptAVFormatContext_In = nullptr;
	AVFormatContext* ptAVFormatContext_Out = nullptr;

	//初始化 libavformat 并注册所有的封装器、解封装器和协议。
	//av_register_all();

	//初始化网络库
	avformat_network_init();

	//打开文件，解封装文件头
	nRtn = avformat_open_input(
		&ptAVFormatContext_In,
		pchInUrl,
		nullptr,					//nullptr--根据文件后缀名进行格式推测
		nullptr
	);
	if (nRtn)
	{
		PrintErr(nRtn);
		return nRtn;
	}

	DEBUG(DEBUG_LEVEL_INFO, "Open %s is success\n", pchInUrl);

	//获取音频、视频流信息
	nRtn = avformat_find_stream_info(ptAVFormatContext_In, nullptr);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//打印封装信息
	av_dump_format(ptAVFormatContext_In, 0, pchInUrl, 0);

	////////////////////////////////////输出流////////////////////////////////////

	//RTMP 推流的封装格式固定为FLV，但你的 RTMP 地址无文件后缀，avformat_alloc_output_context2无法自动推断格式，必须手动指定format_name="flv"
	nRtn = avformat_alloc_output_context2(&ptAVFormatContext_Out, nullptr, "flv", pchOutUrl);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//配置输出流
	for (size_t i = 0; i < ptAVFormatContext_In->nb_streams; i++)
	{
		auto eCodecType = ptAVFormatContext_In->streams[i]->codecpar->codec_type;
		// 关键2：过滤非音视频流（仅保留视频、音频，舍弃tmcd等数据/字幕流）
		if (eCodecType != AVMEDIA_TYPE_VIDEO && eCodecType != AVMEDIA_TYPE_AUDIO)
		{
			continue;
		}

		AVStream* ptAVStream = avformat_new_stream(ptAVFormatContext_Out, nullptr);
		if (!ptAVStream)
		{
			DEBUG(DEBUG_LEVEL_ERROR, "avformat_new_stream is err\n");

			avformat_close_input(&ptAVFormatContext_In);
			ptAVFormatContext_In = nullptr;

			avformat_free_context(ptAVFormatContext_Out);
			ptAVFormatContext_Out = nullptr;

			return -1;
		}

		//复制配置信息
		avcodec_parameters_copy(ptAVStream->codecpar, ptAVFormatContext_In->streams[i]->codecpar);
		ptAVStream->time_base = ptAVFormatContext_In->streams[i]->time_base;								//时间基数与原视频一致

		// 移除废弃的ptAVStream->codec->codec_tag = 0; 新版无需操作codec成员
		ptAVStream->codecpar->codec_tag = 0;
	}

	DEBUG(DEBUG_LEVEL_INFO, "");

	//打印输出封装信息
	av_dump_format(ptAVFormatContext_Out, 0, pchOutUrl, 1);

	//打开输出IO
	nRtn = avio_open(&ptAVFormatContext_Out->pb, pchOutUrl, AVIO_FLAG_WRITE);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avio_open is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;

		return -1;
	}

	//写入文件头
	nRtn = avformat_write_header(ptAVFormatContext_Out, NULL);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avformat_write_header is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;
		return nRtn;
	}

	AVPacket tAVPacket = { 0 };
	int64_t llStartTime = av_gettime_relative();

	for (;;)
	{
		nRtn = av_read_frame(ptAVFormatContext_In, &tAVPacket);
		if (nRtn < 0)
		{
			std::cout << "EOF\n";
			break;
		}

		if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
			ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type != AVMEDIA_TYPE_AUDIO)
		{
			av_packet_unref(&tAVPacket);
			continue;
		}

		//视频帧
		if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			std::cout << "视频:";

			AVRational tTimebase_Video = ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base;
			auto llInterval = av_gettime_relative() - llStartTime;														//系统时间间隔；单位：us

			auto llCurPts_Video = av_rescale_q(tAVPacket.pts, tTimebase_Video, { 1, AV_TIME_BASE });
			auto llTime_Video = llCurPts_Video;				//单位：us

			if (llTime_Video > llInterval)
			{
				av_usleep(llTime_Video - llInterval);
			}
		}
		else if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			std::cout << "音频:";
		}

		std::cout << tAVPacket.pts << "\n";

		tAVPacket.pts = av_rescale_q_rnd(tAVPacket.pts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.dts = av_rescale_q_rnd(tAVPacket.dts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.duration = av_rescale_q_rnd(tAVPacket.duration, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.pos = -1;				//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

		//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
		nRtn = av_interleaved_write_frame(ptAVFormatContext_Out, &tAVPacket);
		if (nRtn != 0)
		{
			std::cout << "# ";
			continue;
		}
	}

	//写入文件尾（必须执行，否则输出文件损坏无法播放）
	av_write_trailer(ptAVFormatContext_Out);

	avformat_close_input(&ptAVFormatContext_In);
	ptAVFormatContext_In = nullptr;

	avformat_free_context(ptAVFormatContext_Out);
	ptAVFormatContext_Out = nullptr;

	return 0;
}

/// <summary>
/// rtsp推流测试
/// </summary>
/// <returns></returns>
int Test02()
{
	int nRtn = 0;
	//const char* pchInUrl = "../01-斗地主项目介绍.mp4";											//输入文件
	const char* pchInUrl = "../G.E.M.邓紫棋 - 夜的尽头.mp4";											//输入文件
	//const char* pchOutUrl = "rtmp://127.0.0.1:1935/live/test";									//输出文件；rtmp url必须是 rtmp://server/app/stream_name
	const char* pchOutUrl = "rtsp://127.0.0.1:8554/test";										//输出文件	

	AVFormatContext* ptAVFormatContext_In = nullptr;
	AVFormatContext* ptAVFormatContext_Out = nullptr;

	//初始化 libavformat 并注册所有的封装器、解封装器和协议。
	//av_register_all();

	//初始化网络库
	avformat_network_init();

	//打开文件，解封装文件头
	nRtn = avformat_open_input(
		&ptAVFormatContext_In,
		pchInUrl,
		nullptr,					//nullptr--根据文件后缀名进行格式推测
		nullptr
	);
	if (nRtn)
	{
		PrintErr(nRtn);
		return nRtn;
	}

	DEBUG(DEBUG_LEVEL_INFO, "Open %s is success\n", pchInUrl);

	//获取音频、视频流信息
	nRtn = avformat_find_stream_info(ptAVFormatContext_In, nullptr);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//打印封装信息
	av_dump_format(ptAVFormatContext_In, 0, pchInUrl, 0);

	////////////////////////////////////输出流////////////////////////////////////

	//RTMP 推流的封装格式固定为FLV，但你的 RTMP 地址无文件后缀，avformat_alloc_output_context2无法自动推断格式，必须手动指定format_name="flv"
	nRtn = avformat_alloc_output_context2(&ptAVFormatContext_Out, nullptr, "rtsp", pchOutUrl);
	if (nRtn)
	{
		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		PrintErr(nRtn);
		return nRtn;
	}

	//配置输出流
	for (size_t i = 0; i < ptAVFormatContext_In->nb_streams; i++)
	{
		auto eCodecType = ptAVFormatContext_In->streams[i]->codecpar->codec_type;
		// 关键2：过滤非音视频流（仅保留视频、音频，舍弃tmcd等数据/字幕流）
		if (eCodecType != AVMEDIA_TYPE_VIDEO && eCodecType != AVMEDIA_TYPE_AUDIO)
		{
			continue;
		}

		AVStream* ptAVStream = avformat_new_stream(ptAVFormatContext_Out, nullptr);
		if (!ptAVStream)
		{
			DEBUG(DEBUG_LEVEL_ERROR, "avformat_new_stream is err\n");

			avformat_close_input(&ptAVFormatContext_In);
			ptAVFormatContext_In = nullptr;

			avformat_free_context(ptAVFormatContext_Out);
			ptAVFormatContext_Out = nullptr;

			return -1;
		}

		//复制配置信息
		avcodec_parameters_copy(ptAVStream->codecpar, ptAVFormatContext_In->streams[i]->codecpar);
		ptAVStream->time_base = ptAVFormatContext_In->streams[i]->time_base;								//时间基数与原视频一致

		// 移除废弃的ptAVStream->codec->codec_tag = 0; 新版无需操作codec成员
		ptAVStream->codecpar->codec_tag = 0;
	}

	DEBUG(DEBUG_LEVEL_INFO, "");

	//打印输出封装信息
	av_dump_format(ptAVFormatContext_Out, 0, pchOutUrl, 1);

	//打开输出IO
	/*nRtn = avio_open(&ptAVFormatContext_Out->pb, pchOutUrl, AVIO_FLAG_WRITE);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avio_open is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;

		return -1;
	}*/

	AVDictionary* opt = nullptr;

	// 强制使用 TCP 推流（推荐）
	av_dict_set(&opt, "rtsp_transport", "tcp", 0);

	// 最大延迟
	av_dict_set(&opt, "max_delay", "500000", 0);

	//写入文件头
	nRtn = avformat_write_header(ptAVFormatContext_Out, &opt);
	av_dict_free(&opt);
	if (nRtn < 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "avformat_write_header is err\n");

		avformat_close_input(&ptAVFormatContext_In);
		ptAVFormatContext_In = nullptr;

		avformat_free_context(ptAVFormatContext_Out);
		ptAVFormatContext_Out = nullptr;
		return nRtn;
	}

	AVPacket tAVPacket = { 0 };
	int64_t llStartTime = av_gettime_relative();

	for (;;)
	{
		nRtn = av_read_frame(ptAVFormatContext_In, &tAVPacket);
		if (nRtn < 0)
		{
			std::cout << "EOF\n";
			break;
		}

		if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
			ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type != AVMEDIA_TYPE_AUDIO)
		{
			av_packet_unref(&tAVPacket);
			continue;
		}

		//视频帧
		if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			std::cout << "视频:";

			AVRational tTimebase_Video = ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base;
			auto llInterval = av_gettime_relative() - llStartTime;														//系统时间间隔；单位：us

			auto llCurPts_Video = av_rescale_q(tAVPacket.pts, tTimebase_Video, { 1, AV_TIME_BASE });
			auto llTime_Video = llCurPts_Video;				//单位：us

			if (llTime_Video > llInterval)
			{
				av_usleep(llTime_Video - llInterval);
			}
		}
		else if (ptAVFormatContext_In->streams[tAVPacket.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			std::cout << "音频:";
		}

		std::cout << tAVPacket.pts << "\n";

		tAVPacket.pts = av_rescale_q_rnd(tAVPacket.pts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.dts = av_rescale_q_rnd(tAVPacket.dts, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.duration = av_rescale_q_rnd(tAVPacket.duration, ptAVFormatContext_In->streams[tAVPacket.stream_index]->time_base, ptAVFormatContext_Out->streams[tAVPacket.stream_index]->time_base,
			(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
		tAVPacket.pos = -1;				//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

		//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
		nRtn = av_interleaved_write_frame(ptAVFormatContext_Out, &tAVPacket);
		if (nRtn != 0)
		{
			std::cout << "# ";
			continue;
		}
	}

	//写入文件尾（必须执行，否则输出文件损坏无法播放）
	av_write_trailer(ptAVFormatContext_Out);

	avformat_close_input(&ptAVFormatContext_In);
	ptAVFormatContext_In = nullptr;

	avformat_free_context(ptAVFormatContext_Out);
	ptAVFormatContext_Out = nullptr;

	return 0;
}


int main()
{
	return Test02();
}

