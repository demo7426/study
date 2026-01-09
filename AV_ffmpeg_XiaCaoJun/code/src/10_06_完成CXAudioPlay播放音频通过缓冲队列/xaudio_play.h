/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xaudio_play.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.09
描  述: 实现对音频播放类的封装
备  注: 
修改记录:

  1.  日期: 2026.01.09
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>

#include "singleton.h"

class CXAudioPlay : public CSingleton<CXAudioPlay>
{
	friend class CSingleton<CXAudioPlay>;
public:
	CXAudioPlay();
	virtual ~CXAudioPlay() {};

	/// <summary>
	/// 音频节点数据
	/// </summary>
	typedef struct _AUDIO_DATA_NODE
	{
		std::vector<uint8_t> Data;				//数据
		int32_t nStartIndex;					//数据的起始索引
	}AUDIO_DATA_NODE, *PAUDIO_DATA_NODE;

	typedef struct _AUDIO_SPEC_INFO
	{
		int freq = 44100;                   //音频采样率

		/**
		 *  \name Audio format flags
		 *
		 *  Defaults to LSB byte order.
		 */
		 /* @{ */
		#define AUDIO_U8        0x0008  /**< Unsigned 8-bit samples */
		#define AUDIO_S8        0x8008  /**< Signed 8-bit samples */
		#define AUDIO_U16LSB    0x0010  /**< Unsigned 16-bit samples */
		#define AUDIO_S16LSB    0x8010  /**< Signed 16-bit samples */
		#define AUDIO_U16MSB    0x1010  /**< As above, but big-endian byte order */
		#define AUDIO_S16MSB    0x9010  /**< As above, but big-endian byte order */
		#define AUDIO_U16       AUDIO_U16LSB
		#define AUDIO_S16       AUDIO_S16LSB
		/* @} */

		/**
		 *  \name int32 support
		 */
		 /* @{ */
		#define AUDIO_S32LSB    0x8020  /**< 32-bit integer samples */
		#define AUDIO_S32MSB    0x9020  /**< As above, but big-endian byte order */
		#define AUDIO_S32       AUDIO_S32LSB
		/* @} */

		/**
		 *  \name float32 support
		 */
		 /* @{ */
		#define AUDIO_F32LSB    0x8120  /**< 32-bit floating point samples */
		#define AUDIO_F32MSB    0x9120  /**< As above, but big-endian byte order */
		#define AUDIO_F32       AUDIO_F32LSB
		/* @} */
		uint16_t format;			//音频样本类型 使用系统字节序
		uint8_t channels;			//音频通道数量（双声道 立体声）
		uint8_t silence;			//静音的值
		uint16_t samples;			//样本数量，2的n次方，用于分割
									//平面模式的通道数据
									//例如：samples = 8
									//		LLLL RRRR
	}AUDIO_SPEC_INFO, *PAUDIO_SPEC_INFO;

	/// <summary>
	/// 打开音频播放器
	/// </summary>
	/// <param name="_tAudioSpecInfo"></param>
	/// <returns>-2--失败;0--成功</returns>
	int Open(const AUDIO_SPEC_INFO _tAudioSpecInfo);
	
	/// <summary>
	/// 添加新的数据节点
	/// </summary>
	/// <param name="_pData"></param>
	/// <param name="_Len"></param>
	/// <returns></returns>
	int Push(uint8_t* _pData, int32_t _Len);

	/// <summary>
	/// 设置音频的播放音量
	/// </summary>
	/// <param name="_Volume">音量;数值范围:0~128</param>
	void SetPalyVolume(uint8_t _Volume);

	/// <summary>
	/// 设置音频的播放速率
	/// </summary>
	/// <param name="_Rate">速率;数值范围:0~10</param>
	void SetPalyRate(float _Rate);

	/// <summary>
	/// 关闭音频播放器
	/// </summary>
	/// <param name=""></param>
	void Close(void);

private:
	std::mutex m_mut;												//音频数据互斥锁
	std::condition_variable m_cond;									//音频数据信号量
	std::deque<AUDIO_DATA_NODE> m_deqAudioDataNode;					//音频数据
	constexpr static uint32_t m_unMaxAudioDataNodeSize = 4096;		//音频数据节点最大数量

	uint8_t m_uchAudioVolume;										//音频音量大小

	AUDIO_SPEC_INFO m_tAudioSpecInfo;								//音频参数信息

private:
	/// <summary>
	/// 音频回调函数，用于静态函数和类方法之间的转换调用
	/// </summary>
	/// <param name="userdata"></param>
	/// <param name="stream"></param>
	/// <param name="len"></param>
	static void AudioCallback(void* userdata, uint8_t* stream, int len);

	/// <summary>
	/// 音频回调函数
	/// </summary>
	/// <param name="stream"></param>
	/// <param name="len"></param>
	void AudioCallback(uint8_t* stream, int len);
};

