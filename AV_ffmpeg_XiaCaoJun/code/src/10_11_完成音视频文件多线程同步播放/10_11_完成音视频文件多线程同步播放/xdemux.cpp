/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux.cpp
作  者:	钱锐      版本: V0.1.1     新建日期: 2025.08.29
描  述: 实现解封装
备  注:
修改记录:

  1.  日期: 2025.08.29
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

  2.  日期: 2026.01.20
	  作者: 钱锐
	  内容:
		  1) 新增 GetVideoId、GetAudioId 函数接口，保证使用流id索引时的正确性;
	  版本:V0.1.1

*************************************************/

#include <iostream>
#include <thread>
#include <chrono>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xdemux.h"
#include "debug.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int CXDemux::Create_AVFormatContext(const char* _pURL)
{
	int nRtn = 0;
	std::unique_lock<std::mutex> lock(m_mut);
	AVDictionary* ptAVDictionary = nullptr;

	//av_dict_set(&ptAVDictionary, "rtsp_transport", "tcp", 0);		//设置传输媒体流为tcp
	av_dict_set(&ptAVDictionary, "stimeout", "1000000", 0);			//超时连接1秒

	nRtn = avformat_open_input(
		&m_ptAVFormatContext,
		_pURL,
		nullptr,		//封装器格式;nullptr--自动探测，根据后缀名或者文件头判定其格式
		&ptAVDictionary			//参数设置，rtsp才需要设置
	);

	if (ptAVDictionary)
		av_dict_free(&ptAVDictionary);
	ptAVDictionary = nullptr;

	if (nRtn)
	{
		PrintErr(nRtn);
		return -2;
	}

	//获取媒体格式信息 无头部格式
	nRtn = avformat_find_stream_info(m_ptAVFormatContext, nullptr);
	if (nRtn)
	{
		PrintErr(nRtn);
		return -2;
	}

	//打印封装信息
	av_dump_format(
		m_ptAVFormatContext,
		0,
		_pURL,
		0		//上下文时输入还是输出;0--输入;1--输出
	);

	for (int i = 0; i < m_ptAVFormatContext->nb_streams; i++)
	{
		if (m_ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_ptAVStream_Video = m_ptAVFormatContext->streams[i];

			m_nVideoId = i;

			std::cout << "------视频------" << std::endl;
			std::cout << "	width：" << m_ptAVStream_Video->codecpar->width << std::endl;
			std::cout << "	height：" << m_ptAVStream_Video->codecpar->height << std::endl;
		}
		else if (m_ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			m_ptAVStream_Audio = m_ptAVFormatContext->streams[i];

			m_nAudioId = i;

			std::cout << "------音频------" << std::endl;
			std::cout << "	sample_rate：" << m_ptAVStream_Audio->codecpar->sample_rate << std::endl;
		}
	}
	
    return 0;
}

int CXDemux::Read_Frame(AVPacket* _pAVPacket)
{
	int nRtn = 0;
	auto cNowTimePoint = std::chrono::high_resolution_clock::now();// 2. 转换为从Epoch开始的时长
	auto cDuration = cNowTimePoint.time_since_epoch();

	std::unique_lock<std::mutex> lock(m_mut);

	m_llLastMs = std::chrono::duration_cast<std::chrono::milliseconds>(cDuration).count();

	if (!m_ptAVFormatContext)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "AVFormatContext is nullptr");
		return -2;
	}

	nRtn = av_read_frame(m_ptAVFormatContext, _pAVPacket);			//
	if (nRtn < 0)
	{
		PrintErr(nRtn);
		return -2;				//读取结束或出错时退出
	}

	return 0;
}

int CXDemux::SetCurPlayTimestamp(long long _Timestamp)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	if (m_ptAVFormatContext)
	{
		auto pts = av_rescale_q(_Timestamp, { 1, AV_TIME_BASE }, m_ptAVStream_Video->time_base);

		/*移除AVSEEK_FLAG_FRAME：该 flag 仅用于「按帧索引 seek」（比如直接定位到第 100 帧），而你是按时间戳 seek，使用该 flag 会导致 seek 逻辑错误；
			保留AVSEEK_FLAG_BACKWARD + 不添加AVSEEK_FLAG_ANY：这是保证 seek 到关键帧的核心 ——FFmpeg 默认（不加AVSEEK_FLAG_ANY）会自动定位到目标 PTS 之前最近的关键帧。*/
		//nRtn = av_seek_frame(m_ptAVFormatContext, m_ptAVStream_Video->index, pts, (int)AVSEEK_FLAG_FRAME | (int)AVSEEK_FLAG_BACKWARD);
		nRtn = av_seek_frame(m_ptAVFormatContext, m_ptAVStream_Video->index, pts, AVSEEK_FLAG_BACKWARD);

		PrintErr(nRtn);
	}

	return nRtn;
}

void CXDemux::Close(void)
{
	std::unique_lock<std::mutex> lock(m_mut);

	if (m_ptAVFormatContext)
	{
		avformat_close_input(&m_ptAVFormatContext);
		m_ptAVFormatContext = nullptr;
	}
}
