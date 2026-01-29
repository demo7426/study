/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdemux_task.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.14
描  述: 线程内部实现解封装
备  注:
修改记录:

  1.  日期: 2025.12.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
#include <libavutil/avutil.h>
}

#include "xdemux_task.h"
#include "debug.h"
#include "xdecode_task.h"
#include "xmux.h"

/// <summary>
/// 获取对应文件的帧率
/// </summary>
/// <param name="_pchURL">帧率</param>
/// <returns></returns>
static int GetFrameRate(const char* _pchURL)
{
	CXDemux cDemux;
	struct AVFormatContext* ptAVFormatContext = nullptr;

	int nRtn = cDemux.Create_AVFormatContext(_pchURL);
	if (nRtn)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "%s, 不存在", _pchURL);
		return -2;
	}

	ptAVFormatContext = cDemux.GetAVFormatContext();
	if (!ptAVFormatContext)
	{
		cDemux.Close();
		DEBUG(DEBUG_LEVEL_ERROR, "GetAVFormatContext is err");
		return -2;
	}

	int nFrameRate = ptAVFormatContext->streams[0]->avg_frame_rate.num / ptAVFormatContext->streams[0]->avg_frame_rate.den;

	cDemux.Close();

	return nFrameRate;
}


int CXDemux_Task::Open(const char* _pURL, int _TimeoutMs)
{
	if (m_cXDemux.Create_AVFormatContext(_pURL))
	{
		return -2;
	}

	m_cXDemux.SetTimeoutMs(_TimeoutMs);

	m_pURL = _pURL;
	m_TimeoutMs = _TimeoutMs;

	m_nFrameRate = GetFrameRate(_pURL);

	return 0;
}

void CXDemux_Task::SetNext(CXThread* _pcXThread_Video, CXThread* _pcXThread_Audio)
{
	if (!_pcXThread_Video && !_pcXThread_Audio)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "SetNext input paramter is err.");
		return;
	}

	m_pcXDecode_Task_Video = dynamic_cast<CXDecode_Task*>(_pcXThread_Video);
	m_pcXDecode_Task_Audio = dynamic_cast<CXDecode_Task*>(_pcXThread_Audio);

	{
		AVCodecID eVideoID = m_cXDemux.GetAVStream_Video()->codecpar->codec_id;								//视频编码器ID
		AVCodecParameters* ptAVCodecParameters = m_cXDemux.GetAVStream_Video()->codecpar;					//视频编码参数

		if(m_pcXDecode_Task_Video)
			m_pcXDecode_Task_Video->Open(eVideoID, false, *ptAVCodecParameters);
	}

	if(m_cXDemux.GetAVStream_Audio())
	{
		AVCodecID eVideoID = m_cXDemux.GetAVStream_Audio()->codecpar->codec_id;								//音频编码器ID
		AVCodecParameters* ptAVCodecParameters = m_cXDemux.GetAVStream_Audio()->codecpar;					//音频编码参数

		if (m_pcXDecode_Task_Audio)
			m_pcXDecode_Task_Audio->Open(eVideoID, false, *ptAVCodecParameters);
	}

}

int CXDemux_Task::SetCurPlayTimestamp(long long _Timestamp)
{
	return m_cXDemux.SetCurPlayTimestamp(_Timestamp);
}

long long CXDemux_Task::GetDuration(void)
{
	auto ptAVStream_Video = m_cXDemux.GetAVStream_Video();
	auto ptAVStream_Audio = m_cXDemux.GetAVStream_Audio();
	
	long long llDurationUs = av_rescale_q(
		ptAVStream_Video->duration, 
		ptAVStream_Video->time_base, 
		{ 1, AV_TIME_BASE }					//AV_TIME_BASE_Q
	);

	return llDurationUs;
}

void CXDemux_Task::Main(void)
{
	int nRtn = 0;
	AVPacket tAVPacket = { 0 };

	while (1)
	{
		{
			std::lock_guard<std::mutex> lock(m_cMut);
			if (m_IsExit)
			{
				DEBUG(DEBUG_LEVEL_INFO, "CXDemux_Task is end");
				break;
			}

			if (m_bIsPause)			//暂停
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				continue;
			}
		}

		nRtn = m_cXDemux.Read_Frame(&tAVPacket);
		if (nRtn < 0)
		{
			std::cout << "-";
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			if (m_cXDemux.IsIsConnected() == false)
			{	
				//重新连接
				m_cXDemux.Close();
				m_cXDemux.Create_AVFormatContext(m_pURL);
				m_cXDemux.SetTimeoutMs(m_TimeoutMs);
			}

			continue; // 读取结束或出错时继续等待，直到成功为止
		}

		//std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//if (m_cXDemux.GetAVStream_Video() && tAVPacket.stream_index == m_cXDemux.GetAVStream_Video()->index && m_pcXDecode_Task)	//TODO:暂时只处理视频流
		if (m_pcXDecode_Task_Video && m_cXDemux.GetAVStream_Video() && tAVPacket.stream_index == m_cXDemux.GetAVStream_Video()->index)	//处理视频流
			m_pcXDecode_Task_Video->DoNext(&tAVPacket);		

		if (m_pcXDecode_Task_Audio && m_cXDemux.GetAVStream_Audio() && tAVPacket.stream_index == m_cXDemux.GetAVStream_Audio()->index)	//处理音频流
			m_pcXDecode_Task_Audio->DoNext(&tAVPacket);

		av_packet_unref(&tAVPacket);
	}

	m_cXDemux.Close();
}
