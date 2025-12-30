/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xmux.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 实现封装
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

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
#include <libavcodec/avcodec.h>
}

#include "xmux.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int CXMux::Create_AVFormatContext(const char* _pURL)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	m_pchURL = _pURL;

	nRtn = avformat_alloc_output_context2(&m_ptAVFormatContext, nullptr, nullptr,
		m_pchURL			//根据文件名推测其封装格式
	);
	PrintErr(nRtn);

	//打开输出IO
	nRtn = avio_open(&m_ptAVFormatContext->pb, m_pchURL, AVIO_FLAG_WRITE);
	PrintErr(nRtn);

    return 0;
}

int CXMux::SetVideoParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters)
{
	if (!_pAVRational || !_pAVCodecParameters)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}
	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Video = avformat_new_stream(m_ptAVFormatContext, NULL);		//处理有视频流的情况

	m_ptAVStream_Video->time_base = *_pAVRational;								//时间基数与原视频一致

	//从解封装复制参数
	avcodec_parameters_copy(m_ptAVStream_Video->codecpar, _pAVCodecParameters);

	return 0;
}

int CXMux::SetAudioParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters)
{
	if (!_pAVRational || !_pAVCodecParameters)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Audio = avformat_new_stream(m_ptAVFormatContext, NULL);		//处理有视频流的情况

	m_ptAVStream_Audio->time_base = *_pAVRational;								//时间基数与原视频一致

	//从解封装复制参数
	avcodec_parameters_copy(m_ptAVStream_Audio->codecpar, _pAVCodecParameters);

	return 0;
}

int CXMux::Set_EncodeFormat(const AVRational* _pAVRational, const struct AVCodecContext* codec)
{
	if (!_pAVRational || !codec)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Video = avformat_new_stream(m_ptAVFormatContext, NULL);		//处理有视频流的情况

	m_ptAVStream_Video->time_base = *_pAVRational;								//时间基数与原视频一致

	// 复制编码器格式
	avcodec_parameters_from_context(m_ptAVStream_Video->codecpar, codec);

	return 0;
}

int CXMux::Write_Header(AVFormatContext* _pAVFormatContext, AVStream* _pAVStream_Video, AVStream* _pAVStream_Audio)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVFormatContext_Demux = _pAVFormatContext;
	m_ptAVStream_Video_Demux = _pAVStream_Video;
	m_ptAVStream_Audio_Demux = _pAVStream_Audio;

	//写入文件头
	nRtn = avformat_write_header(m_ptAVFormatContext, NULL);
	if (nRtn < 0)
	{
		PrintErr(nRtn);
		return nRtn;
	}

	av_dump_format(m_ptAVFormatContext, 0, m_pchURL,
		1			//上下文时输入还是输出;0--输入;1--输出
	);

	//截取10~20秒之间的音频、视频，取多不去少
	// 假定9 11秒有关键帧，取第9秒
	if (m_ptAVStream_Video_Demux && m_ptAVStream_Video_Demux->time_base.num > 0)
	{
		double t = m_ptAVStream_Video_Demux->time_base.den / m_ptAVStream_Video_Demux->time_base.num;		//den分母/num分子
		m_ullBegin_Video_Pts = m_dbBeginSec * t;
		m_ullEnd_Video_Pts = m_dbEndSec * t;
	}

	if (m_ptAVStream_Audio_Demux && m_ptAVStream_Audio_Demux->time_base.num > 0)
	{
		double t = m_ptAVStream_Audio_Demux->time_base.den / m_ptAVStream_Audio_Demux->time_base.num;		//den分母/num分子
		m_ullBegin_Audio_Pts = m_dbBeginSec * t;
		m_ullEnd_Audio_Pts = m_dbEndSec * t;
	}

	//seek输入媒体 移动到第10秒的关键帧位置
	if (m_ptAVStream_Video_Demux)
	{
		nRtn = av_seek_frame((AVFormatContext*)m_ptAVFormatContext_Demux, m_ptAVStream_Video_Demux->index, m_ullBegin_Video_Pts, (int)AVSEEK_FLAG_FRAME | (int)AVSEEK_FLAG_BACKWARD);
		PrintErr(nRtn);
	}
	return 0;
}

int CXMux::RescaleTime(AVPacket* _pAVPacket)
{
	int nRtn = 0;
	std::unique_lock<std::mutex> lock(m_mut);

	AVStream* ptAVStream_In = m_ptAVFormatContext_Demux->streams[_pAVPacket->stream_index];
	AVStream* ptAVStream_Out = nullptr;
	long long llPtsOffset = 0;

	if (m_ptAVStream_Video_Demux && _pAVPacket->stream_index == m_ptAVStream_Video_Demux->index)
	{
		if (_pAVPacket->pts < m_ullBegin_Video_Pts)		//过滤dbBeginSec秒前的残留视频包
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		if (_pAVPacket->pts > m_ullEnd_Video_Pts)		//超过第dbEndSec秒退出，只存dbBeginSec~dbEndSec秒
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		ptAVStream_Out = m_ptAVFormatContext->streams[0];
		llPtsOffset = m_ullBegin_Video_Pts;
	}
	else if (m_ptAVStream_Audio_Demux && _pAVPacket->stream_index == m_ptAVStream_Audio_Demux->index)
	{
		if (_pAVPacket->pts < m_ullBegin_Audio_Pts)		//过滤dbBeginSec秒前的残留音频包
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		if (_pAVPacket->pts > m_ullEnd_Audio_Pts)		//超过第dbEndSec秒退出，只存dbBeginSec~dbEndSec秒
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		ptAVStream_Out = m_ptAVFormatContext->streams[1];
		llPtsOffset = m_ullBegin_Audio_Pts;
	}
	else
	{
		//av_packet_unref(_pAVPacket);
		return -2;
	}

	_pAVPacket->pts = av_rescale_q_rnd(_pAVPacket->pts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->dts = av_rescale_q_rnd(_pAVPacket->dts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->duration = av_rescale_q_rnd(_pAVPacket->duration, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->pos = -1;		//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

	//if (m_ptAVStream_Video_Demux && _pAVPacket->stream_index == m_ptAVStream_Video_Demux->index)
	//	std::cout << "视频：";
	//else if (m_ptAVStream_Audio_Demux && _pAVPacket->stream_index == m_ptAVStream_Audio_Demux->index)
	//	std::cout << "音频：";

	//std::cout << _pAVPacket->pts << ", " << _pAVPacket->dts << ", " << _pAVPacket->size << std::endl;

	return 0;
}

int CXMux::Write_Frame(AVPacket* _pAVPacket)
{
	int nRtn = av_interleaved_write_frame(m_ptAVFormatContext, _pAVPacket);		//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
	PrintErr(nRtn);
	av_packet_unref(_pAVPacket);

	return 0;
}

void CXMux::Close(void)
{
	std::unique_lock<std::mutex> lock(m_mut);
	av_write_trailer(m_ptAVFormatContext);			//写入结尾

	avio_closep(&m_ptAVFormatContext->pb);
	avformat_free_context(m_ptAVFormatContext);
	m_ptAVFormatContext = nullptr;
}
