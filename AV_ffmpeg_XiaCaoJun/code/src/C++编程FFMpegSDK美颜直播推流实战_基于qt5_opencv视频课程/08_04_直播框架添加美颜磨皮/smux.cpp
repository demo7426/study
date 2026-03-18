/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	smux.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.27
描  述: 实现对原始数据的封装/推流
备  注:
修改记录:

  1.  日期: 2026.02.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <string>
#include <regex>
#include <stdexcept>

#include "smux.h"


CSMux::~CSMux()
{
}

// 提取RTSP字符串的函数
static std::string ExtractRtmpRtspUrl(const std::string& input_str) {
	// 正则表达式说明：
	// ^rtsp://  匹配以rtsp://开头
	// .+        匹配任意字符（至少一个），覆盖IP、端口、路径等部分
	// $         匹配字符串结尾
	std::regex rtsp_regex(R"(^(rtsp|rtmp)://.+$)");
	std::smatch match_result;

	// 执行正则匹配
	if (std::regex_match(input_str, match_result, rtsp_regex)) {
		// match_result[0] 是整个匹配到的字符串
		return match_result[1].str();
	}
	else {
		return std::string();
	}
}

int CSMux::Init(const char* _pURL)
{
	if (_pURL == nullptr)
	{
		std::cout << __func__ << ", input parameter is err" << std::endl;
		return -1;
	}

	int nRtn = 0;
	std::string strUrlHeader = ExtractRtmpRtspUrl(_pURL);

	//初始化网络库
	avformat_network_init();

	std::unique_lock<std::mutex> lock(m_mut);
	if (strUrlHeader == "rtsp")
	{
		nRtn = avformat_alloc_output_context2(&m_ptAVFormatContext, nullptr, "rtsp", _pURL);
	}
	else if (strUrlHeader == "rtmp")
	{
		nRtn = avformat_alloc_output_context2(&m_ptAVFormatContext, nullptr, "flv", _pURL);
	}
	else
	{
		nRtn = avformat_alloc_output_context2(&m_ptAVFormatContext, nullptr, nullptr, _pURL);
	}

	if (nRtn)
	{
		std::cout << "avformat_alloc_output_context2 is err" << std::endl;
		return -2;
	}

	m_strDesUrl = _pURL;

	m_vec_ptAVStream.clear();
	m_vec_tAVRational.clear();

	return 0;
}

int CSMux::AddStream(AVCodecContext* codec)
{
	if (codec == nullptr)
	{
		std::cout << __func__ << ", input parameter is err" << std::endl;
		return -1;
	}

	std::unique_lock<std::mutex> lock(m_mut);
	auto ptAVStream = avformat_new_stream(m_ptAVFormatContext, nullptr);
	if (!ptAVStream)
	{
		std::cout << __func__ << ", avformat_new_stream is err" << std::endl;
		return -2;
	}


	//复制配置信息
	avcodec_parameters_from_context(ptAVStream->codecpar, codec);
	ptAVStream->time_base = codec->time_base;								//时间基数与原视频一致

	// 移除废弃的ptAVStream->codec->codec_tag = 0; 新版无需操作codec成员
	ptAVStream->codecpar->codec_tag = 0;

	m_vec_ptAVStream.push_back(ptAVStream);
	m_vec_tAVRational.push_back(codec->time_base);

	return 0;
}

int CSMux::Write_Header()
{
	int nRtn = 0;
	std::string strUrlHeader = ExtractRtmpRtspUrl(m_strDesUrl);

	std::unique_lock<std::mutex> lock(m_mut);
	//打印输出封装信息
	av_dump_format(m_ptAVFormatContext, 0, m_strDesUrl.data(), 1);

	if (strUrlHeader != "rtsp")
	{
		//打开输出IO
		nRtn = avio_open(&m_ptAVFormatContext->pb, m_strDesUrl.data(), AVIO_FLAG_WRITE);
		if (nRtn < 0)
		{
			std::cout << "avio_open is err" << std::endl;
			return -2;
		}
	}

	//写入文件头
	nRtn = avformat_write_header(m_ptAVFormatContext, nullptr);
	if (nRtn < 0)
	{
		std::cout << "avformat_write_header is err" << std::endl;
		return -2;
	}

	return 0;
}

int CSMux::Write_Packet(AVPacket* _pAVPacket)
{
	_pAVPacket->pts = av_rescale_q_rnd(_pAVPacket->pts, m_vec_tAVRational[_pAVPacket->stream_index], m_vec_ptAVStream[_pAVPacket->stream_index]->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->dts = av_rescale_q_rnd(_pAVPacket->dts, m_vec_tAVRational[_pAVPacket->stream_index], m_vec_ptAVStream[_pAVPacket->stream_index]->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->duration = av_rescale_q_rnd(_pAVPacket->duration, m_vec_tAVRational[_pAVPacket->stream_index], m_vec_ptAVStream[_pAVPacket->stream_index]->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->pos = -1;				//表示该数据包在原始媒体文件中的字节偏移量（即数据在文件中的存储位置），重封装时通常需将 pos 设为 -1（由输出格式重新计算）。

	std::unique_lock<std::mutex> lock(m_mut);
	//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
	int nRtn = av_interleaved_write_frame(m_ptAVFormatContext, _pAVPacket);
	if (nRtn != 0)
	{
		std::cout << "av_interleaved_write_frame is err";
		return -2;
	}

	return 0;
}

void CSMux::Close()
{
	std::unique_lock<std::mutex> lock(m_mut);
	//写入文件尾（必须执行，否则输出文件损坏无法播放）
	av_write_trailer(m_ptAVFormatContext);
	
	if (m_ptAVFormatContext)
	{
		avformat_free_context(m_ptAVFormatContext);
		m_ptAVFormatContext = nullptr;
	}

	m_vec_ptAVStream.clear();
	m_vec_tAVRational.clear();
}
