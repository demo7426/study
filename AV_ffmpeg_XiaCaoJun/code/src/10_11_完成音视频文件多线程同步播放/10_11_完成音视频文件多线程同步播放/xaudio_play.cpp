/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xaudio_play.cpp
作  者:	钱锐      版本: V0.1.1     新建日期: 2026.01.09
描  述: 实现对音频播放类的封装
备  注:
修改记录:

  1.  日期: 2026.01.09
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

  2.  日期: 2026.01.20
	  作者: 钱锐
	  内容:
		  1) 重载 Open、Push 函数;
	  版本:V0.1.1

*************************************************/

#include <vector>

#include "xaudio_play.h"

extern "C" {
#include <libavutil/time.h>
}

#include "sdl/SDL.h"

#undef main

#pragma comment(lib, "SDL2.lib")

CXAudioPlay::CXAudioPlay(): m_uchAudioVolume(SDL_MIX_MAXVOLUME)
{
}

int CXAudioPlay::Open(const AUDIO_SPEC_INFO _tAudioSpecInfo, double _AudioTimeBaseDescend)
{
	SDL_QuitSubSystem(SDL_INIT_AUDIO);			//退出之前已经打开的音频

	if (SDL_Init(SDL_INIT_AUDIO) != 0)			//初始化
	{
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return EXIT_FAILURE;
	}

	SDL_AudioSpec tSDL_AudioSpec;

	tSDL_AudioSpec.freq = _tAudioSpecInfo.freq;								//音频采样率
	tSDL_AudioSpec.format = _tAudioSpecInfo.format;							//音频样本类型 使用系统字节序
	tSDL_AudioSpec.channels = _tAudioSpecInfo.channels;						//音频通道数量（双声道 立体声）
	tSDL_AudioSpec.silence = _tAudioSpecInfo.silence;						//静音的值
	tSDL_AudioSpec.samples = _tAudioSpecInfo.samples;						//样本数量，2的n次方，用于分割
																			//平面模式的通道数据
																			//例如：samples = 8
																			//		LLLL RRRR
	tSDL_AudioSpec.callback = AudioCallback;								//回调函数
	tSDL_AudioSpec.userdata = this;

	m_dbAudioTimeBaseDescend = _AudioTimeBaseDescend;

	if (SDL_OpenAudio(&tSDL_AudioSpec, nullptr) != 0)
	{
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;

		return -2;
	}

	m_tAudioSpecInfo = _tAudioSpecInfo;

	SDL_PauseAudio(0);			//开始播放音频

	return 0;
}

int CXAudioPlay::Open(AVCodecParameters* _ptPara_Audio, double _AudioTimeBase)
{
	if (!_ptPara_Audio)
	{
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return -1;
	}

	CXAudioPlay::AUDIO_SPEC_INFO tAudio_Spec_Info;

	tAudio_Spec_Info.freq = _ptPara_Audio->sample_rate;
	tAudio_Spec_Info.silence = 0;
	tAudio_Spec_Info.channels = _ptPara_Audio->channels;
	tAudio_Spec_Info.samples = 1024;

	switch (_ptPara_Audio->format)
	{
	case AVSampleFormat::AV_SAMPLE_FMT_U8:
	case AVSampleFormat::AV_SAMPLE_FMT_U8P:
		tAudio_Spec_Info.format = AUDIO_U8;
		break;
	case AVSampleFormat::AV_SAMPLE_FMT_S16:
	case AVSampleFormat::AV_SAMPLE_FMT_S16P:
		tAudio_Spec_Info.format = AUDIO_S16;
		break;
	case AVSampleFormat::AV_SAMPLE_FMT_S32:
	case AVSampleFormat::AV_SAMPLE_FMT_S32P:
		tAudio_Spec_Info.format = AUDIO_S32;
		break;
	case AVSampleFormat::AV_SAMPLE_FMT_FLT:
	case AVSampleFormat::AV_SAMPLE_FMT_FLTP:
		tAudio_Spec_Info.format = AUDIO_F32;
		break;
	default:
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return -2;
	}

	return this->Open(tAudio_Spec_Info, _AudioTimeBase);
}

int CXAudioPlay::Push(uint8_t* _pData, int32_t _Len, int64_t _Pts)
{
	std::unique_lock<std::mutex> lock(m_mut);

	while (m_deqAudioDataNode.size() >= m_unMaxAudioDataNodeSize)
	{
		m_cond.wait(lock);
	}

	m_deqAudioDataNode.push_back(AUDIO_DATA_NODE());

	m_deqAudioDataNode.back().Data.assign(_pData, _pData + _Len);		//防止出现多次拷贝数据的情况
	m_deqAudioDataNode.back().StartIndex = 0;
	m_deqAudioDataNode.back().Pts = _Pts;

	return 0;
}

int CXAudioPlay::Push(AVFrame* _ptAVFrame)
{
	if (!_ptAVFrame || !_ptAVFrame->data[0])
	{
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return -1;
	}

	std::vector<unsigned char> vecBuf;
	int nSampleSize = 0;								//采样大小
	int nChannels = _ptAVFrame->channels;				//音频通道数量

	unsigned char* puchLF = _ptAVFrame->data[0];		//左前声道
	unsigned char* puchRF = _ptAVFrame->data[1];		//右前声道
	unsigned char* puchLR = _ptAVFrame->data[2];		//左后声道
	unsigned char* puchRR = _ptAVFrame->data[3];		//右后声道

	unsigned char* puchData = nullptr;

	switch (_ptAVFrame->format)
	{
	case AVSampleFormat::AV_SAMPLE_FMT_U8P:
		nSampleSize = 1;
		break;
	case AVSampleFormat::AV_SAMPLE_FMT_S16P:
		nSampleSize = 2;
		break;
	case AVSampleFormat::AV_SAMPLE_FMT_S32P:
	case AVSampleFormat::AV_SAMPLE_FMT_FLTP:
		nSampleSize = 4;
	break;
	default:
		std::cout << __FUNCTION__ << ", " << __LINE__ << ", " << SDL_GetError() << std::endl;
		return -2;
	}

	switch (_ptAVFrame->format)
	{
	case AVSampleFormat::AV_SAMPLE_FMT_U8P:
	case AVSampleFormat::AV_SAMPLE_FMT_S16P:
	case AVSampleFormat::AV_SAMPLE_FMT_S32P:
	case AVSampleFormat::AV_SAMPLE_FMT_FLTP:
	{
		//TODO:暂时只支持双、四通道音频数据
		vecBuf.resize(_ptAVFrame->linesize[0]);
		puchData = vecBuf.data();

		//LLLL 
		//RRRR			
		//LR LR LR LR	4
		for (size_t i = 0; i < _ptAVFrame->nb_samples; i++)			//_ptAVFrame->nb_samples -- 所有通道的采样数量
		{
			memcpy(puchData + i * nSampleSize * nChannels, puchLF + i * nSampleSize, nSampleSize);
			memcpy(puchData + i * nSampleSize * nChannels + nSampleSize, puchRF + i * nSampleSize, nSampleSize);

			// 4声道额外处理左后（BL）、右后（BR）
			if (nChannels == 4)
			{
				memcpy(puchData + nSampleSize * nChannels + 2 * nSampleSize, puchLR + i * nSampleSize, nSampleSize);
				memcpy(puchData + nSampleSize * nChannels + 3 * nSampleSize, puchRR + i * nSampleSize, nSampleSize);
			}
		}
	}
	return this->Push(puchData, _ptAVFrame->linesize[0], _ptAVFrame->pts);
	default:
		break;
	}
	
	return this->Push(_ptAVFrame->data[0], _ptAVFrame->linesize[0], _ptAVFrame->pts);
}

void CXAudioPlay::SetPalyVolume(uint8_t _Volume)
{
	m_uchAudioVolume = _Volume;
}

void CXAudioPlay::SetPalyRate(float _Rate)
{
	AUDIO_SPEC_INFO tOldAudioSpecInfo = m_tAudioSpecInfo;		//之前的参数信息
	AUDIO_SPEC_INFO tCurAudioSpecInfo = m_tAudioSpecInfo;		//当前的参数信息
	
	tCurAudioSpecInfo.freq *= _Rate;
	
	this->Open(tCurAudioSpecInfo);

	m_tAudioSpecInfo = tOldAudioSpecInfo;
}

int64_t CXAudioPlay::GetCurPts(void)
{
	std::unique_lock<std::mutex> lock(m_mutPts);

	return m_llCurPts;
}

int CXAudioPlay::Pause(void)
{
	SDL_PauseAudio(1);			//暂停播放音频
	return 0;
}

int CXAudioPlay::Resume(void)
{
	SDL_PauseAudio(0);			//开始播放音频
	return 0;
}

void CXAudioPlay::Close(void)
{
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	{
		std::unique_lock<std::mutex> lock(m_mut);
		m_deqAudioDataNode.clear();
	}

	{
		std::unique_lock<std::mutex> lockPts(m_mutPts);
		m_llCurPts = 0;
	}
}

void CXAudioPlay::AudioCallback(void* userdata, uint8_t* stream, int len)
{
	CXAudioPlay* pcXAudioPlay = (CXAudioPlay*)userdata;

	pcXAudioPlay->AudioCallback(stream, len);
}

void CXAudioPlay::AudioCallback(uint8_t* stream, int len)
{
	AUDIO_DATA_NODE tAudioDataNode;

	int nStreamSumLen = 0;
	int64_t llStartTimeUs = 0;					//开始us

	SDL_memset(stream, 0, len);

	while (len > 0)
	{
		{
			std::unique_lock<std::mutex> lock(m_mut);
			if (m_deqAudioDataNode.empty())
				break;

			tAudioDataNode = m_deqAudioDataNode.front();

			llStartTimeUs = av_gettime_relative();

			std::unique_lock<std::mutex> lockPts(m_mutPts);
			m_llCurPts = tAudioDataNode.Pts;
		}

		if (m_dbAudioTimeBaseDescend > 0)
		{
			std::unique_lock<std::mutex> lock(m_mutPts);
			m_llCurPts = m_llCurPts + (av_gettime_relative() - llStartTimeUs) / 1000000 / m_dbAudioTimeBaseDescend;

			llStartTimeUs = av_gettime_relative();
		}

		if (tAudioDataNode.Data.size() - tAudioDataNode.StartIndex <= len)		//当前节点数据小于len，直接拷贝即可
		{
			SDL_MixAudio(stream + nStreamSumLen,
				tAudioDataNode.Data.data() + tAudioDataNode.StartIndex,
				tAudioDataNode.Data.size() - tAudioDataNode.StartIndex, 
				m_uchAudioVolume);

			len -= tAudioDataNode.Data.size() - tAudioDataNode.StartIndex;
			nStreamSumLen += tAudioDataNode.Data.size() - tAudioDataNode.StartIndex;

			std::unique_lock<std::mutex> lock(m_mut);

			if (m_deqAudioDataNode.size() >= m_unMaxAudioDataNodeSize)
				m_cond.notify_one();

			m_deqAudioDataNode.pop_front();
		}
		else
		{
			SDL_MixAudio(stream + nStreamSumLen, 
				tAudioDataNode.Data.data() + tAudioDataNode.StartIndex, 
				len, 
				m_uchAudioVolume);

			nStreamSumLen += len;

			std::unique_lock<std::mutex> lock(m_mut);
			m_deqAudioDataNode[0].StartIndex += len;

			len = 0;
		}
	}

}
