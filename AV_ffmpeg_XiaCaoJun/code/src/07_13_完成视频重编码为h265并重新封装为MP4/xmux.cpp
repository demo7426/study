/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	xmux.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.29
��  ��: ʵ�ַ�װ
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

#include "xmux.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int CXMux::Create_AVFormatContext(const char* _pURL)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	m_pchURL = _pURL;

	nRtn = avformat_alloc_output_context2(&m_ptAVFormatContext, nullptr, nullptr,
		m_pchURL			//�����ļ����Ʋ����װ��ʽ
	);
	PrintErr(nRtn);

	//�����IO
	nRtn = avio_open(&m_ptAVFormatContext->pb, m_pchURL, AVIO_FLAG_WRITE);
	PrintErr(nRtn);

    return 0;
}

int CXMux::SetVideoParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters)
{
	if (!_pAVRational || !_pAVCodecParameters)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}
	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Video = avformat_new_stream(m_ptAVFormatContext, NULL);		//��������Ƶ�������

	m_ptAVStream_Video->time_base = *_pAVRational;								//ʱ�������ԭ��Ƶһ��

	//�ӽ��װ���Ʋ���
	avcodec_parameters_copy(m_ptAVStream_Video->codecpar, _pAVCodecParameters);
}

int CXMux::SetAudioParameters(const AVRational* _pAVRational, const AVCodecParameters* _pAVCodecParameters)
{
	if (!_pAVRational || !_pAVCodecParameters)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Audio = avformat_new_stream(m_ptAVFormatContext, NULL);		//��������Ƶ�������

	m_ptAVStream_Audio->time_base = *_pAVRational;								//ʱ�������ԭ��Ƶһ��

	//�ӽ��װ���Ʋ���
	avcodec_parameters_copy(m_ptAVStream_Audio->codecpar, _pAVCodecParameters);
}

int CXMux::Set_EncodeFormat(const AVRational* _pAVRational, const AVCodecContext* codec)
{
	if (!_pAVRational || !codec)
	{
		std::cout << __FUNCTION__ << "input parameter is err" << std::endl;
		return -1;
	}

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVStream_Audio = avformat_new_stream(m_ptAVFormatContext, NULL);		//��������Ƶ�������

	m_ptAVStream_Audio->time_base = *_pAVRational;								//ʱ�������ԭ��Ƶһ��

	// ���Ʊ�������ʽ
	avcodec_parameters_from_context(m_ptAVStream_Audio->codecpar, codec);
}

int CXMux::Write_Header(AVFormatContext* _pAVFormatContext, AVStream* _pAVStream_Video, AVStream* _pAVStream_Audio)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVFormatContext_Demux = _pAVFormatContext;
	m_ptAVStream_Video_Demux = _pAVStream_Video;
	m_ptAVStream_Audio_Demux = _pAVStream_Audio;

	//д���ļ�ͷ
	nRtn = avformat_write_header(m_ptAVFormatContext, NULL);
	PrintErr(nRtn);

	av_dump_format(m_ptAVFormatContext, 0, m_pchURL,
		1			//������ʱ���뻹�����;0--����;1--���
	);

	//��ȡ10~20��֮�����Ƶ����Ƶ��ȡ�಻ȥ��
	// �ٶ�9 11���йؼ�֡��ȡ��9��
	if (m_ptAVStream_Video_Demux && m_ptAVStream_Video_Demux->time_base.num > 0)
	{
		double t = m_ptAVStream_Video_Demux->time_base.den / m_ptAVStream_Video_Demux->time_base.num;		//den��ĸ/num����
		m_llBegin_Video_Pts = m_dbBeginSec * t;
		m_llEnd_Video_Pts = m_dbEndSec * t;
	}

	if (m_ptAVStream_Audio_Demux && m_ptAVStream_Audio_Demux->time_base.num > 0)
	{
		double t = m_ptAVStream_Audio_Demux->time_base.den / m_ptAVStream_Audio_Demux->time_base.num;		//den��ĸ/num����
		m_llBegin_Audio_Pts = m_dbBeginSec * t;
		m_llEnd_Audio_Pts = m_dbEndSec * t;
	}

	//seek����ý�� �ƶ�����10��Ĺؼ�֡λ��
	if (m_ptAVStream_Video_Demux)
	{
		nRtn = av_seek_frame((AVFormatContext*)m_ptAVFormatContext_Demux, m_ptAVStream_Video_Demux->index, m_llBegin_Video_Pts, (int)AVSEEK_FLAG_FRAME | (int)AVSEEK_FLAG_BACKWARD);
		PrintErr(nRtn);
	}
	return 0;
}

int CXMux::RescaleTime(AVPacket* _pAVPacket)
{
	int nRtn = 0;
	std::unique_lock<std::mutex> lock(m_mut);

	AVStream* ptAVStream_In = m_ptAVFormatContext_Demux->streams[_pAVPacket->stream_index];
	AVStream* ptAVStream_Out = nullptr;
	long long llPtsOffset = 0;

	if (m_ptAVStream_Video_Demux && _pAVPacket->stream_index == m_ptAVStream_Video_Demux->index)
	{
		if (_pAVPacket->pts < m_llBegin_Video_Pts)		//����dbBeginSec��ǰ�Ĳ�����Ƶ��
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		if (_pAVPacket->pts > m_llEnd_Video_Pts)		//������dbEndSec���˳���ֻ��dbBeginSec~dbEndSec��
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		ptAVStream_Out = m_ptAVFormatContext->streams[0];
		llPtsOffset = m_llBegin_Video_Pts;
	}
	else if (m_ptAVStream_Audio_Demux && _pAVPacket->stream_index == m_ptAVStream_Audio_Demux->index)
	{
		if (_pAVPacket->pts < m_llBegin_Audio_Pts)		//����dbBeginSec��ǰ�Ĳ�����Ƶ��
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		if (_pAVPacket->pts > m_llEnd_Audio_Pts)		//������dbEndSec���˳���ֻ��dbBeginSec~dbEndSec��
		{
			//av_packet_unref(_pAVPacket);
			return -2;
		}

		ptAVStream_Out = m_ptAVFormatContext->streams[1];
		llPtsOffset = m_llBegin_Audio_Pts;
	}
	else
	{
		//av_packet_unref(_pAVPacket);
		return -2;
	}

	_pAVPacket->pts = av_rescale_q_rnd(_pAVPacket->pts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->dts = av_rescale_q_rnd(_pAVPacket->dts - llPtsOffset, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->duration = av_rescale_q_rnd(_pAVPacket->duration, ptAVStream_In->time_base, ptAVStream_Out->time_base,
		(AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
	_pAVPacket->pos = -1;		//��ʾ�����ݰ���ԭʼý���ļ��е��ֽ�ƫ���������������ļ��еĴ洢λ�ã����ط�װʱͨ���轫 pos ��Ϊ -1���������ʽ���¼��㣩��

	if (m_ptAVStream_Video_Demux && _pAVPacket->stream_index == m_ptAVStream_Video_Demux->index)
		std::cout << "��Ƶ��";
	else if (m_ptAVStream_Audio_Demux && _pAVPacket->stream_index == m_ptAVStream_Audio_Demux->index)
		std::cout << "��Ƶ��";

	std::cout << _pAVPacket->pts << ", " << _pAVPacket->dts << ", " << _pAVPacket->size << std::endl;

	return 0;
}

int CXMux::Write_Frame(AVPacket* _pAVPacket)
{
	int nRtn = av_interleaved_write_frame(m_ptAVFormatContext, _pAVPacket);		//д������Ƶ֡�����Զ�av_packet_unref(&tAVPacket_Demux)
	PrintErr(nRtn);
	av_packet_unref(_pAVPacket);

	return 0;
}

void CXMux::Close(void)
{
	std::unique_lock<std::mutex> lock(m_mut);
	av_write_trailer(m_ptAVFormatContext);			//д���β

	avio_closep(&m_ptAVFormatContext->pb);
	avformat_free_context(m_ptAVFormatContext);
	m_ptAVFormatContext = nullptr;
}
