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
#include "xdecode_task.h"
#include "xmux.h"

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

void CXDemux_Task::SetNext(CXThread* _pcXThread)
{
	if (!_pcXThread)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "SetNext input paramter is err.");
		return;
	}

	//m_pcXDecode_Task
	AVCodecID eVideoID = m_cXDemux.GetAVStream_Video()->codecpar->codec_id;							//视频编码器ID
	AVCodecParameters* ptAVCodecParameters = m_cXDemux.GetAVStream_Video()->codecpar;					//视频编码参数

	m_pcXDecode_Task = dynamic_cast<CXDecode_Task*>(_pcXThread);

	m_pcXDecode_Task->Open(eVideoID, false, *ptAVCodecParameters);
}

void CXDemux_Task::SetXEncode_XMux(CXEncode* _pcXEncode, CXMux* _pcXMux, std::string _StoreDir)
{
	AVCodecID eVideoID = m_cXDemux.GetAVStream_Video()->codecpar->codec_id;							//视频编码器ID
	AVCodecParameters* ptAVCodecParameters = m_cXDemux.GetAVStream_Video()->codecpar;					//视频编码参数

	m_pcXEncode = _pcXEncode;
	m_pcXMux = _pcXMux;

	if (m_pcXEncode)
	{
		m_pcXEncode->Create_AVCodecContext(AV_CODEC_ID_H264);
		m_pcXEncode->Set_AVCodecContext_Param(ptAVCodecParameters->width, ptAVCodecParameters->height,
			m_cXDemux.GetAVStream_Video()->avg_frame_rate.num / m_cXDemux.GetAVStream_Video()->avg_frame_rate.den,
			m_pcXDecode_Task->GetAVPixelFormat()
		);

		// 添加编码参数设置
		m_pcXEncode->AV_Opt_Set_Int("crf", 23);       // 恒定质量模式
		m_pcXEncode->AV_Opt_Set("preset", "medium");  // 编码速度/质量权衡
		m_pcXEncode->AV_Opt_Set_Int("g", 50);         // 关键帧间隔
		// 缺少H.265必要参数
		m_pcXEncode->AV_Opt_Set("profile", "main");   // 添加profile设置
		m_pcXEncode->AV_Opt_Set("level", "3.1");      // 添加level设置

		m_pcXEncode->Open();
	}

	if (m_pcXMux)
	{
		//////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////重封装///////////////////////////////////
		//const char* pchOutURL = "AutoMonitorSysterm.mp4";
		const char* pchOutURL = _StoreDir.c_str();

		constexpr double dbBeginSec = 300;							//截取开始时间
		constexpr double dbEndSec = dbBeginSec + 10;					//截取结束时间

		m_pcXMux->Create_AVFormatContext(pchOutURL);

		/*m_pcXMux->SetBeginSec(dbBeginSec);
		m_pcXMux->SetEndSec(dbEndSec);*/

		//cXMux.SetVideoParameters(&cXDemux.GetAVStream_Video()->time_base, (const AVCodecParameters*)cXDemux.GetAVStream_Video()->codecpar);
		m_pcXMux->Set_EncodeFormat(&m_cXDemux.GetAVStream_Video()->time_base, m_pcXEncode->GetAVCodecContext());		//必须使用这个，上一行代码在重编码时，不可用
		
		if(m_cXDemux.GetAVStream_Audio())
			m_pcXMux->SetAudioParameters(&m_cXDemux.GetAVStream_Audio()->time_base, (const AVCodecParameters*)m_cXDemux.GetAVStream_Audio()->codecpar);

		m_pcXMux->Write_Header(m_cXDemux.GetAVFormatContext(), m_cXDemux.GetAVStream_Video(), m_cXDemux.GetAVStream_Audio());
	}
	
	m_pcXDecode_Task->SetXEncode_XMux(m_pcXEncode, m_pcXMux);
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

		//std::cout << ".";
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		//if (m_cXDemux.GetAVStream_Video() && tAVPacket.stream_index == m_cXDemux.GetAVStream_Video()->index && m_pcXDecode_Task)	//TODO:暂时只处理视频流
		if (m_pcXDecode_Task)	//处理音视频流
			m_pcXDecode_Task->DoNext(&tAVPacket);

		av_packet_unref(&tAVPacket);
	}

	m_cXDemux.Close();
}
