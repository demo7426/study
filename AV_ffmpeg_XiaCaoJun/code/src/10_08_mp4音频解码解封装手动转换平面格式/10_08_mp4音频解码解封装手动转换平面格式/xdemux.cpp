/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 实现解封装
备  注:
修改记录:

  1.  日期: 2025.08.29
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <thread>
#include <chrono>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xdemux.h"

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

			std::cout << "------视频------" << std::endl;
			std::cout << "	width：" << m_ptAVStream_Video->codecpar->width << std::endl;
			std::cout << "	height：" << m_ptAVStream_Video->codecpar->height << std::endl;
		}
		else if (m_ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			m_ptAVStream_Audio = m_ptAVFormatContext->streams[i];

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

	nRtn = av_read_frame(m_ptAVFormatContext, _pAVPacket);			//
	if (nRtn < 0)
	{
		PrintErr(nRtn);
		return -2;				//读取结束或出错时退出
	}

	return 0;
}

void CXDemux::Close(void)
{
	std::unique_lock<std::mutex> lock(m_mut);

	avformat_close_input(&m_ptAVFormatContext);
	m_ptAVFormatContext = nullptr;
}
