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
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xdecode_task.h"
#include "Debug.h"

//打印错误信息
static void PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}

bool CXDecode_Task::Open(int _AVCodecID, bool _IsEnable_HwDecode, AVCodecParameters _tAVCodecParameters)
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

	return true;
}

void CXDecode_Task::DoNext(AVPacket* _ptAVPacket)
{
	m_cXAVPacket_List.Push(_ptAVPacket);
	//std::cout << "#";
}

AVFrame* CXDecode_Task::GetCurAVFrame(void)
{
	std::lock_guard<std::mutex> lock(m_cMutAVFrame);

	if (m_bAVFrameIsValid)
	{
		m_bAVFrameIsValid = false;
		return m_ptAVFrame;
	}

	return nullptr;
}

void CXDecode_Task::Main(void)
{
	int nRtn = 0;
	AVPacket* ptAVPacket = nullptr;
	m_ptAVFrame = av_frame_alloc();

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
			continue;

		av_packet_unref(ptAVPacket);
		av_packet_free(&ptAVPacket);		//释放之前 av_packet_alloc 分配出的对象

		{
			std::lock_guard<std::mutex> lock(m_cMutAVFrame);

			if (!m_cXDeCode.Recv_AVFrame(m_ptAVFrame))
				continue;

			m_bAVFrameIsValid = true;
		}
	}
}
