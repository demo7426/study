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
}

#include "xdemux_task.h"
#include "Debug.h"

int CXDemux_Task::Open(const char* _pURL, int _TimeoutMs)
{
	if (m_cXDemux.Create_AVFormatContext(_pURL))
	{
		return -2;
	}

	m_cXDemux.SetTimeoutMs(_TimeoutMs);

	m_pURL = _pURL;
	m_TimeoutMs = _TimeoutMs;

	return 0;
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

		std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		av_packet_unref(&tAVPacket);
	}
}
