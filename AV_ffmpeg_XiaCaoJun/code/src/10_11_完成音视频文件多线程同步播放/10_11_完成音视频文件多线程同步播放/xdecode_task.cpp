/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdecode_task.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.16
描  述: 线程内部实现解码
备  注:
修改记录:

  1.  日期: 2025.12.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>

extern "C" {
#include <libavcodec/avcodec.h>
}

#include "xdecode_task.h"
#include "debug.h"
#include "xencode.h"
#include "xmux.h"
#include "xencode_mux_task.h"

//打印错误信息
static void PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}

CXDecode_Task::~CXDecode_Task()
{
	// 清理剩余的AVFrame
	AVFrame* frame = nullptr;
	while ((frame = m_cAVFrame_List.Pop()) != nullptr) 
	{
		av_frame_free(&frame); // 释放结构体
	}
}

bool CXDecode_Task::Open(int _AVCodecID, bool _IsEnable_HwDecode, AVCodecParameters _tAVCodecParameters, int _VideoId, int _AudioId)
{
	//视频解码初始化，因为后续解码是直接发送的AVPacket数据，在此处只能使用cpu解码
	m_cXDeCode.Create_AVCodecContext(_AVCodecID, _IsEnable_HwDecode);

	m_cXDeCode.Set_AVCodecParameters(&_tAVCodecParameters);

	int nRtn = m_cXDeCode.Open();
	if (nRtn < 0)
	{
		PrintErr(nRtn);
		return false;
	}

	m_nVideoId = _VideoId;
	m_nAudioId = _AudioId;

	return true;
}

void CXDecode_Task::DoNext(AVPacket* _ptAVPacket)
{
#ifdef _AUDIO_TEST 
	if (_ptAVPacket->stream_index == m_nAudioId)
#else
	if (_ptAVPacket->stream_index == m_nVideoId)				//只有视频流需要解码，TODO:注意视频流索引不一定是0
#endif
	{
		m_cXAVPacket_List.Push(_ptAVPacket);
	}

	while (m_cAVFrame_List.Size() >= XPUBLIC_DEMUX_MAX_NODE_NUM)						//反压，控制程序占用的ddr大小
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		continue;
	}

	//std::cout << "#";
	return;
}

AVFrame* CXDecode_Task::GetCurAVFrame(void)
{
	return m_cAVFrame_List.Pop();
}

void CXDecode_Task::Main(void)
{
	int nRtn = 0;
	AVPacket* ptAVPacket = nullptr;
	AVFrame* ptAVFrame = nullptr;

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

		ptAVPacket = m_cXAVPacket_List.Pop();
		if (ptAVPacket == nullptr)
			continue;

		if (!m_cXDeCode.Send_AVPacket(ptAVPacket))
		{
			av_packet_unref(ptAVPacket);
			av_packet_free(&ptAVPacket);		//释放之前 av_packet_alloc 分配出的对象
			continue;
		}

		av_packet_unref(ptAVPacket);
		av_packet_free(&ptAVPacket);		//释放之前 av_packet_alloc 分配出的对象

		if(ptAVFrame == nullptr)
			ptAVFrame = av_frame_alloc();

		if (!m_cXDeCode.Recv_AVFrame(ptAVFrame))
			continue;

		m_cAVFrame_List.Push(ptAVFrame);

		ptAVFrame = nullptr;
	}

	//取出剩余的帧
	auto vecAVFrame = m_cXDeCode.RecvAll_AVFrameData();

	for(auto var : vecAVFrame)
	{
		m_cAVFrame_List.Push(var);

#if 0
		//用于保证当前帧数据被正确的取走，没有遗漏
		while (1)
		{
			{
				std::lock_guard<std::mutex> lock(m_cMutAVFrame);
				if (!m_bAVFrameIsValid)		//数据被取走
					break;
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
#endif
	}
}
