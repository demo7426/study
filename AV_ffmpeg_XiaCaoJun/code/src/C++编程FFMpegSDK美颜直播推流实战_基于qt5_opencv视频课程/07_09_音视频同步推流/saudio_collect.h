/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	saudio_collect.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.03
描  述: 实现音频的数据采集
备  注:
修改记录:

  1.  日期: 2026.03.03
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

#include <mutex>

class QAudioInput;
class QIODevice;
class QCoreApplication;

class CSAudio_Collect
{
public:
	CSAudio_Collect() = default;
	virtual ~CSAudio_Collect() = 0;
	
	/// <summary>
	/// 初始化采样
	/// </summary>
	/// <param name="_SampleRate">采样率</param>
	/// <param name="_Channels">音频通道数</param>
	/// <param name="_SampleByte">采样大小;单位:字节</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	virtual int Init(int _SampleRate, int _Channels, int _SampleByte) = 0;

	/// <summary>
	/// 开始采集(函数阻塞执行，且不主动退出)
	/// </summary>
	/// <returns></returns>
	virtual int Start() = 0;

	/// <summary>
	/// 获取采集的缓冲区数据
	/// </summary>
	/// <param name="_pBuf">缓冲区</param>
	/// <param name="_BufSize">缓冲区大小;(只有>=_BufSize时，才能成功取走数据)</param>
	/// <returns>-3--当前有效数据小于_BufSize;-2--失败;-1--参数错误;0--成功</returns>
	virtual int GetData(char* _pBuf, int _BufSize) = 0;

	/// <summary>
	/// 停止采集
	/// </summary>
	/// <returns></returns>
	virtual int Stop() = 0;

private:
	/// <summary>
	/// 采集的音频信息
	/// </summary>
	typedef struct _COLLECT_AUDIO_INFO
	{
		char CollectAudioBuf[64 * 1024];		//采集的音频缓冲
		int BufValidLen;						//采集音频缓冲的有效长度
		std::mutex MutCollectAudioBuf;
	}COLLECT_AUDIO_INFO, * PCOLLECT_AUDIO_INFO;

protected:
	COLLECT_AUDIO_INFO m_tCollectAudioInfo;

};

class CSAudio_Collect_Qt : public CSAudio_Collect
{
public:
	CSAudio_Collect_Qt(int argc, char* argv[]);
	~CSAudio_Collect_Qt();

	/// <summary>
	/// 初始化采样
	/// </summary>
	/// <param name="_SampleRate">采样率</param>
	/// <param name="_Channels">音频通道数</param>
	/// <param name="_SampleByte">采样大小;单位:字节</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Init(int _SampleRate, int _Channels, int _SampleByte) override;

	/// <summary>
	/// 开始采集(函数阻塞执行，且不主动退出)
	/// </summary>
	/// <returns></returns>
	int Start() override;

	/// <summary>
	/// 获取采集的缓冲区数据
	/// </summary>
	/// <param name="_pBuf">缓冲区</param>
	/// <param name="_BufSize">缓冲区大小;(只有>=_BufSize时，才能成功取走数据)</param>
	/// <returns>-3--当前有效数据小于_BufSize;-2--失败;-1--参数错误;0--成功</returns>
	int GetData(char* _pBuf, int _BufSize) override;

	/// <summary>
	/// 停止采集
	/// </summary>
	/// <returns></returns>
	int Stop() override;

private:
	QAudioInput* m_pcAudioInput = nullptr;
	QIODevice* m_pcIODevice = nullptr;

	QCoreApplication* m_pcCoreApplication = nullptr;
};

