/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xdemux.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.29
��  ��: ʵ�ֽ��װ
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.29
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <iostream>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xdemux.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int CXDemux::Create_AVFormatContext(const char* _pURL)
{
	int nRtn = 0;
	std::unique_lock<std::mutex> lock(m_mut);

	nRtn = avformat_open_input(
		&m_ptAVFormatContext,
		_pURL,
		nullptr,		//��װ����ʽ;nullptr--�Զ�̽�⣬���ݺ�׺�������ļ�ͷ�ж����ʽ
		nullptr			//�������ã�rtsp����Ҫ����
	);
	if (nRtn)
	{
		PrintErr(nRtn);
		return -2;
	}

	//��ȡý���ʽ��Ϣ ��ͷ����ʽ
	nRtn = avformat_find_stream_info(m_ptAVFormatContext, nullptr);
	if (nRtn)
	{
		PrintErr(nRtn);
		return -2;
	}

	//��ӡ��װ��Ϣ
	av_dump_format(
		m_ptAVFormatContext,
		0,
		_pURL,
		0		//������ʱ���뻹�����;0--����;1--���
	);

	for (int i = 0; i < m_ptAVFormatContext->nb_streams; i++)
	{
		if (m_ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			m_ptAVStream_Video = m_ptAVFormatContext->streams[i];

			std::cout << "------��Ƶ------" << std::endl;
			std::cout << "	width��" << m_ptAVStream_Video->codecpar->width << std::endl;
			std::cout << "	height��" << m_ptAVStream_Video->codecpar->height << std::endl;
		}
		else if (m_ptAVFormatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			m_ptAVStream_Audio = m_ptAVFormatContext->streams[i];

			std::cout << "------��Ƶ------" << std::endl;
			std::cout << "	sample_rate��" << m_ptAVStream_Audio->codecpar->sample_rate << std::endl;
		}
	}
	
    return 0;
}

int CXDemux::Read_Frame(AVPacket* _pAVPacket)
{
	int nRtn = 0;
	std::unique_lock<std::mutex> lock(m_mut);

	nRtn = av_read_frame(m_ptAVFormatContext, _pAVPacket);			//
	if (nRtn < 0)
	{
		PrintErr(nRtn);
		return -2;				//��ȡ���������ʱ�˳�
	}

	return 0;
}

void CXDemux::Close(void)
{
	std::unique_lock<std::mutex> lock(m_mut);

	avformat_close_input(&m_ptAVFormatContext);
	m_ptAVFormatContext = nullptr;
}
