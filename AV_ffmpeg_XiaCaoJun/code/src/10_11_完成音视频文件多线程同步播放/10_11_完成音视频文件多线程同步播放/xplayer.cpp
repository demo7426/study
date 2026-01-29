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
#include <mutex>

#include "xencode.h"
#include "xdecode.h"
#include "xdemux.h"
#include "xmux.h"
#include "xthread.h"
#include "debug.h"

#include "xplayer.h"

extern "C" {
#include <libavutil/time.h>
}

int CXPlayer::Open(const char* _pURL, void* _pWinID)
{
	if (!_pURL || _pURL[0] == '\0')
	{
		DEBUG(DEBUG_LEVEL_ERROR, "Input parameter is err.");
		return -1;
	}

	if (m_cDemux_Task.Open(_pURL, 1000) != 0)
	{
		DEBUG(DEBUG_LEVEL_INFO, "%s is not exist", _pURL);
		return -2;
	}

	//nFrameRate = GetFrameRate(pchURL);

	m_pcXVideo_View = CXVideo_View::Create();

	m_cDemux_Task.SetNext(&m_cDecode_Task_Video, &m_cDecode_Task_Audio);

	auto ptAVStream_Video = m_cDemux_Task.GetCXDemux()->GetAVStream_Video();
	auto ptAVStream_Audio = m_cDemux_Task.GetCXDemux()->GetAVStream_Audio();

	m_llVideoTotalDuration = m_cDemux_Task.GetDuration();
	
	if(ptAVStream_Audio)
		CXAudioPlay::GetInstance()->Open(ptAVStream_Audio->codecpar, ptAVStream_Audio->time_base.den / ptAVStream_Audio->time_base.num);

	m_cDemux_Task.Start();
	m_cDecode_Task_Video.Start();
	m_cDecode_Task_Audio.Start();

	return CXThread::Start();
}

int CXPlayer::Pause(void)
{
	m_cDecode_Task_Video.Pause();
	m_cDecode_Task_Audio.Pause();

	//如果暂停解封装线程，会影响到进度跳转功能
	//std::this_thread::sleep_for(std::chrono::milliseconds(300));
	//m_cDemux_Task.Pause();

	CXAudioPlay::GetInstance()->Pause();

	m_llPuaseDurationUs = av_gettime_relative();

	return CXThread::Pause();
}

int CXPlayer::Resume(void)
{
	//m_cDemux_Task.Resume();

	m_cDecode_Task_Video.Resume();
	m_cDecode_Task_Audio.Resume();

	CXAudioPlay::GetInstance()->Resume();

	m_llPuaseDurationUs = av_gettime_relative() - m_llPuaseDurationUs;

	{	
		//补上暂停的时间，否则会导致一瞬间刷新几百帧图像

		std::unique_lock<std::mutex> lock(m_mut);
		m_llStartTimeUs += m_llPuaseDurationUs;
	}

	return CXThread::Resume();
}

void CXPlayer::SetPalyVolume(uint8_t _Volume)
{
	CXAudioPlay::GetInstance()->SetPalyVolume(_Volume);
}

void CXPlayer::SetPalyRate(float _Rate)
{
	CXAudioPlay::GetInstance()->SetPalyRate(_Rate);

	std::unique_lock<std::mutex> lock(m_mut);
	//if (m_fPlayRate > _Rate)
	//{
	//	m_llPlayRateDurationUs = av_gettime_relative() - m_llPlayRateDurationUs;

	//	m_llStartTimeUs += m_llPlayRateDurationUs;
	//}
	//else if (m_fPlayRate < _Rate)
	//{
	//	m_llPlayRateDurationUs = av_gettime_relative() - m_llPlayRateDurationUs;

	//	m_llStartTimeUs -= m_llPlayRateDurationUs;		//将之前减慢的时间流逝消除掉
	//}

	m_fPlayRate = _Rate;
}

int CXPlayer::SetCurPlayTimestamp(long long _Timestamp)
{
	int nRtn = 0;

	if (_Timestamp > m_llVideoTotalDuration)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "Input parameter is err");
		return -1;
	}

	nRtn = this->Pause();
	if (nRtn != 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "");
		return nRtn;
	}

	m_cDecode_Task_Video.Clear();
	m_cDecode_Task_Audio.Clear();

	nRtn = m_cDemux_Task.SetCurPlayTimestamp(_Timestamp);
	if (nRtn != 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "SetCurPlayTimestamp is err");
		return nRtn;
	}

	CXAudioPlay::GetInstance()->Clear();

	{
		std::unique_lock<std::mutex> lock(m_mut);
		m_llStartTimeUs = av_gettime_relative() - _Timestamp;
	}

	nRtn = this->Resume();
	if (nRtn != 0)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "");
		return nRtn;
	}

	return 0;
}

int CXPlayer::Close(void)
{
	m_cDemux_Task.Stop();
	m_cDecode_Task_Video.Stop();
	m_cDecode_Task_Audio.Stop();

	CXThread::Stop();

	CXAudioPlay::GetInstance()->Close();
	m_pcXVideo_View->Close();

	if (m_pcXVideo_View)
	{
		delete m_pcXVideo_View;
		m_pcXVideo_View = nullptr;
	}

	return 0;
}

void CXPlayer::Main(void)
{
	bool bInitFlag = false;
	AVFrame* ptAVFrame = nullptr;
	CXVideo_View::Format eFmt;

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	int nFrameRate = 0;						//帧率

	auto ptAVStream_Video = m_cDemux_Task.GetCXDemux()->GetAVStream_Video();
	auto ptAVStream_Audio = m_cDemux_Task.GetCXDemux()->GetAVStream_Audio();

	m_llStartTimeUs = av_gettime_relative();
	m_llPlayRateDurationUs = m_llStartTimeUs;

	while (1)
	{
		{
			std::lock_guard<std::mutex> lock(m_cMut);
			if (m_IsExit)
			{
				DEBUG(DEBUG_LEVEL_INFO, "%s is end", __FUNCTION__);
				break;
			}

			if (m_bIsPause)			//暂停
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				continue;
			}
		}

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
				return;
			}
			}

			m_pcXVideo_View->Init(ptAVFrame->width, ptAVFrame->height, eFmt, nullptr);
			bInitFlag = true;
		}

		m_llCurPlayTimestamp = av_rescale_q(ptAVFrame->pts, ptAVStream_Video->time_base, { 1, AV_TIME_BASE });

		int64_t llVideoPtsTrans = 0;
		int64_t llAudioPlayPts = 0;

		if (ptAVStream_Audio)		//如果存在音频则使用音频同步，否则使用纯视频同步
		{
			llVideoPtsTrans = av_rescale_q(ptAVFrame->pts, ptAVStream_Video->time_base, ptAVStream_Audio->time_base);			//必须将pts统一到音频的时间基数上，才可以正常比较
			llAudioPlayPts = CXAudioPlay::GetInstance()->GetCurPts();

			while (llVideoPtsTrans > llAudioPlayPts)		//保证音画同步
			{
				{
					std::lock_guard<std::mutex> lock(m_cMut);
					if (m_IsExit)
					{
						DEBUG(DEBUG_LEVEL_INFO, "%s is end", __FUNCTION__);
						break;
					}
				}

				if (m_bIsPause)			//暂停
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
					break;
				}

				//获取音频
				auto ptAVFrameTmp = m_cDecode_Task_Audio.GetCurAVFrame();
				if (ptAVFrameTmp)
				{
					CXAudioPlay::GetInstance()->Push(ptAVFrameTmp);

					av_frame_unref(ptAVFrameTmp);
					av_frame_free(&ptAVFrameTmp);
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
				llAudioPlayPts = CXAudioPlay::GetInstance()->GetCurPts();
				continue;
			}
		}
		else							//使用纯视频同步
		{
			double llElapsedUs = 0;		//时间间隙;单位:us

			llVideoPtsTrans = ptAVFrame->pts;

			std::unique_lock<std::mutex> lock(m_mut);

			while (llVideoPtsTrans > llAudioPlayPts)							//纯视频同步
			{
				llElapsedUs = av_gettime_relative() - m_llStartTimeUs;
				llElapsedUs = llElapsedUs < 0 ? 0 : llElapsedUs;				//防止系统时间跳变导致已流逝时间为负
				llElapsedUs *= m_fPlayRate;										//支持倍速播放

				llAudioPlayPts = llElapsedUs / AV_TIME_BASE * (ptAVStream_Video->time_base.den / ptAVStream_Video->time_base.num);

				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}

		//DEBUG(DEBUG_LEVEL_INFO, "llVideoPtsTrans = %d, llAudioPlayPts = %d", llVideoPtsTrans, llAudioPlayPts);

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
}
