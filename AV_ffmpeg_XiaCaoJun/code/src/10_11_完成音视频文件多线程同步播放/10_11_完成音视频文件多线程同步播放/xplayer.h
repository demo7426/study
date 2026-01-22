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
	/// <returns>0--成功</returns>
	int Open(const char* _pURL, void* _pWinID = nullptr);

	/// <summary>
	/// 关闭对应的源数据，并进行资源回收
	/// </summary>
	/// <param name=""></param>
	/// <returns>0--成功</returns>
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
};


