/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xplayer.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.21
描  述: 实现一个播放类
备  注:
修改记录:

  1.  日期: 2026.01.21
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <chrono>

#include "xencode.h"
#include "xdecode.h"
#include "xdemux.h"
#include "xmux.h"
#include "xthread.h"
#include "debug.h"

#include "xplayer.h"

int CXPlayer::Start(const char* _pURL, void* _pWinID)
{
	if (!_pURL || _pURL[0] == '\0')
	{
		DEBUG(DEBUG_LEVEL_ERROR, "Input parameter is err.");
		return -1;
	}

	bool bInitFlag = false;
	AVFrame* ptAVFrame = nullptr;
	CXVideo_View::Format eFmt;

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	int nFrameRate = 0;						//帧率

	while (m_cDemux_Task.Open(_pURL, 1000) != 0)
	{
		DEBUG(DEBUG_LEVEL_INFO, "重新连接:%s", _pURL);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//nFrameRate = GetFrameRate(pchURL);

	m_pcXVideo_View = CXVideo_View::Create();

	m_cDemux_Task.SetNext(&m_cDecode_Task_Video, &m_cDecode_Task_Audio);

	auto ptAVStream_Video = m_cDemux_Task.GetCXDemux()->GetAVStream_Video();
	auto ptAVStream_Audio = m_cDemux_Task.GetCXDemux()->GetAVStream_Audio();

	CXAudioPlay::GetInstance()->Open(ptAVStream_Audio->codecpar, ptAVStream_Audio->time_base.den / ptAVStream_Audio->time_base.num);

	m_cDemux_Task.Start();
	m_cDecode_Task_Video.Start();
	m_cDecode_Task_Audio.Start();

	m_bIsRun = true;

	while (m_bIsRun)
	{
		//获取视频
		ptAVFrame = m_cDecode_Task_Video.GetCurAVFrame();
		if (!ptAVFrame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
			continue;
		}

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
			case AVPixelFormat::AV_PIX_FMT_YUVJ420P:
				eFmt = CXVideo_View::Format::YUV420P;
				break;
			case AVPixelFormat::AV_PIX_FMT_NV12:
				eFmt = CXVideo_View::Format::NV12;
				break;
			default:
			{
				DEBUG(DEBUG_LEVEL_INFO, "不支持的编码格式, format = %d", ptAVFrame->format);
				return -2;
			}
			}

			m_pcXVideo_View->Init(ptAVFrame->width, ptAVFrame->height, eFmt, nullptr);
			bInitFlag = true;
		}

		auto llVideoPtsTrans = av_rescale_q(ptAVFrame->pts, ptAVStream_Video->time_base, ptAVStream_Audio->time_base);			//必须将pts统一到音频的时间基数上，才可以正常比较
		while (llVideoPtsTrans > CXAudioPlay::GetInstance()->GetCurPts())		//保证音画同步
		{
			if (!m_bIsRun)
				break;

			//获取音频
			auto ptAVFrameTmp = m_cDecode_Task_Audio.GetCurAVFrame();
			if (ptAVFrameTmp)
			{
				CXAudioPlay::GetInstance()->Push(ptAVFrameTmp);

				av_frame_unref(ptAVFrameTmp);
				av_frame_free(&ptAVFrameTmp);
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		m_pcXVideo_View->DrawFrame(ptAVFrame);
		av_frame_unref(ptAVFrame);
		av_frame_free(&ptAVFrame);

		nFrameCounter++;

		cEnd_TimePoint = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cEnd_TimePoint - cStart_TimePoint).count() >= 1000)
		{
			std::cout << "每秒帧数：" << nFrameCounter << "\n";

			nFrameCounter = 0;
			cStart_TimePoint = cEnd_TimePoint;
		}
	}

	m_bIsRun = false;

	m_cDemux_Task.Stop();
	m_cDecode_Task_Video.Stop();
	m_cDecode_Task_Audio.Stop();

	if (m_pcXVideo_View)
	{
		delete m_pcXVideo_View;
		m_pcXVideo_View = nullptr;
	}

	return 0;
}

int CXPlayer::Stop(void)
{
	if (m_bIsRun)
	{
		m_cDemux_Task.Stop();
		m_cDecode_Task_Video.Stop();
		m_cDecode_Task_Audio.Stop();

		if (m_pcXVideo_View)
		{
			delete m_pcXVideo_View;
			m_pcXVideo_View = nullptr;
		}
	}

	return 0;
}
