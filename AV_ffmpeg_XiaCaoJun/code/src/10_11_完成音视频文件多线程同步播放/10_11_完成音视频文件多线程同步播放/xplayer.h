/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xplayer.h
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

#pragma once

#include "xvideo_view.h"
#include "xdemux_task.h"
#include "xdecode_task.h"
#include "xaudio_play.h"

class CXPlayer :public CXThread
{
public:
	using CXThread::CXThread;
	virtual ~CXPlayer() = default;

	/// <summary>
	/// 打开对应的源数据
	/// </summary>
	/// <param name="_pURL">rtsp地址/本地文件</param>
    /// <param name="_pWinID">窗口句柄;如果为空,创建新窗口</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Open(const char* _pURL, void* _pWinID = nullptr);

	/// <summary>
	/// 暂停播放
	/// </summary>
	/// <param name=""></param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Pause(void);

	/// <summary>
	/// 继续播放
	/// </summary>
	/// <param name=""></param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Resume(void);

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
	/// 获取视频总时长;单位:us
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	inline long long GetVideoTotalDuration(void)
	{
		return m_llVideoTotalDuration;
	}
	
	/// <summary>
	/// 获取当前播放的时间戳;单位:us
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	inline long long GetCurPlayTimestamp(void)
	{
		return m_llCurPlayTimestamp;
	}

	/// <summary>
	/// 设置当前播放的是时间戳
	/// </summary>
	/// <param name="">时间戳;单位:us</param>
	/// <returns></returns>
	int SetCurPlayTimestamp(long long _Timestamp);

	/// <summary>
	/// 关闭对应的源数据，并进行资源回收
	/// </summary>
	/// <param name=""></param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Close(void);

protected:
	/// <summary>
	/// 线程运行函数
	/// </summary>
	/// <param name="_pArg"></param>
	void Main(void) override;

private:
	CXDemux_Task m_cDemux_Task;
	CXDecode_Task m_cDecode_Task_Video;
	CXDecode_Task m_cDecode_Task_Audio;

	CXVideo_View* m_pcXVideo_View = nullptr;

	long long m_llVideoTotalDuration = 0;						//视频总时长;单位us
	std::atomic_int64_t m_llCurPlayTimestamp = 0;				//当前播放的时间戳;单位us
};


