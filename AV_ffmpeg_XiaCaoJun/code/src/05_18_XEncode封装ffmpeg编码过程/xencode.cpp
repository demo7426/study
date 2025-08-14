/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.08.14
��  ��: ʵ�ֶԱ���ffmpeg���̵ķ�װs
��  ע:
�޸ļ�¼:

  1.  ����: 2025.08.14
	  ����: Ǯ��
	  ����:
		  1) ��Ϊģ���һ���汾;
	  �汾:V0.1.0

*************************************************/

#include <iostream>

#include "xencode.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

CXEncode::CXEncode()
{
}

CXEncode::~CXEncode()
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	while (1)		//��֤�߳��б�����ʣ��֡��ȫ��ȡ����д���ļ�
	{
		//����δѹ�����ݵ��߳���ѹ��
		nRtn = avcodec_send_frame(m_ptAVCodecContext, NULL);		//����Ҫ�ж��䷵��ֵ����Ϊ��Ҫ��֤�߳��б�����ʣ��֡��������ȫ����ȡ��

		//����ѹ��֡��һ��ǰ���ε��÷��ؿգ����壬�������أ�����δ��ɣ�
		//����ʨ�Ӱ��������߳���
		//ÿ�ε��û����·���ptAVPacket�еĿռ�
		nRtn = avcodec_receive_packet(m_ptAVCodecContext, m_ptAVPacket);
		if (nRtn == AVERROR(EAGAIN) || nRtn == AVERROR_EOF)
		{
			break;
		}

		if (nRtn < 0)		//�쳣
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;
			return;
		}

		m_nFrameNum++;

		m_ofs.write((const char*)m_ptAVPacket->data, m_ptAVPacket->size);
		m_ofs.flush();

		av_packet_unref(m_ptAVPacket);		//�����ú���Զ��ͷ�AVPacket�з���Ŀռ�
	}

	std::cout << "֡����" << m_nFrameNum << std::endl;

	if (m_ofs.is_open())
		m_ofs.close();

	av_packet_free(&m_ptAVPacket);
	m_ptAVPacket = nullptr;

	av_frame_free(&m_ptAVFrame);
	m_ptAVFrame = nullptr; 

	avcodec_free_context(&m_ptAVCodecContext);
	m_ptAVCodecContext = nullptr;
}

int CXEncode::Create_AVCodecContext(int _AVCodecID, std::string _Output_FilePath)
{
	AVCodecID eAVCodecID = static_cast<AVCodecID>(_AVCodecID);

	std::unique_lock<std::mutex> lock(m_mut);

	m_ofs.open(_Output_FilePath, std::ios_base::binary);
	if (!m_ofs.is_open())
	{
		std::cerr << "Open file is err" << std::endl;
		return -2;
	}

	//�ҵ�������
	AVCodec* ptAVCodec = avcodec_find_encoder(eAVCodecID);
	if (!ptAVCodec)
	{
		std::cerr << "avcodec_find_encoder is err" << std::endl;
		return -2;
	}

	//������������
	m_ptAVCodecContext = avcodec_alloc_context3(ptAVCodec);
	if (!m_ptAVCodecContext)
	{
		std::cerr << "avcodec_alloc_context3 is err" << std::endl;
		return -2;
	}

	return 0;
}

AVFrame* CXEncode::Set_AVCodecContext_Param(int _Width, int _Height, int _FrameRate, int _AVPixelFormat, int _ThreadCount)
{
	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVCodecContext->width = _Width;
	m_ptAVCodecContext->height = _Height;
	m_ptAVCodecContext->time_base = { 1, _FrameRate };								//֡ʱ�����ʱ�䵥λ������1/30����ÿ��30֡
	m_ptAVCodecContext->pix_fmt = static_cast<AVPixelFormat>(_AVPixelFormat);		//Դ�������ظ�ʽ�������㷨���
	m_ptAVCodecContext->thread_count = _ThreadCount;								//�����߳���

	return Create_AVFrameAndAVPacket(m_ptAVCodecContext->width, m_ptAVCodecContext->height, m_ptAVCodecContext->pix_fmt);
}

int CXEncode::AV_Opt_Set(std::string _Name, std::string _Value)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	nRtn = av_opt_set(m_ptAVCodecContext->priv_data, _Name.c_str(), _Value.c_str(), 0);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_opt_set is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return -2;
	}

	return 0;
}

int CXEncode::AV_Opt_Set_Int(std::string _Name, int _Value)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	nRtn = av_opt_set_int(m_ptAVCodecContext->priv_data, _Name.c_str(), _Value, 0);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_opt_set_int is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return -2;
	}

	return 0;
}

int CXEncode::Open(void)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	nRtn = avcodec_open2(m_ptAVCodecContext, NULL, NULL);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "avcodec_open2 is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return -2;
	}

	return 0;
}

int CXEncode::SendFrame(AVFrame* _pAVFrame)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	//����δѹ�����ݵ��߳���ѹ��
	nRtn = avcodec_send_frame(m_ptAVCodecContext, _pAVFrame);
	if (nRtn)
	{
		return -2;
	}

	while (nRtn >= 0)		//���ض�֡
	{
		//����ѹ��֡��һ��ǰ���ε��÷��ؿգ����壬�������أ�����δ��ɣ�
		//����ʨ�Ӱ��������߳���
		//ÿ�ε��û����·���ptAVPacket�еĿռ�
		nRtn = avcodec_receive_packet(m_ptAVCodecContext, m_ptAVPacket);
		if (nRtn == AVERROR(EAGAIN) || nRtn == AVERROR_EOF)
		{
			break;
		}

		if (nRtn < 0)		//�쳣
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;
			return -2;
		}

		m_nFrameNum++;

		m_ofs.write((const char*)m_ptAVPacket->data, m_ptAVPacket->size);
		m_ofs.flush();

		av_packet_unref(m_ptAVPacket);		//�����ú���Զ��ͷ�AVPacket�з���Ŀռ�
	}

	return 0;
}

AVFrame* CXEncode::Create_AVFrameAndAVPacket(int _Width, int _Height, int _AVPixelFormat)
{
	int nRtn = 0;

	//����AvFrame�ռ� δѹ������
	m_ptAVFrame = av_frame_alloc();
	m_ptAVFrame->width = _Width;
	m_ptAVFrame->height = _Height;
	m_ptAVFrame->format = _AVPixelFormat;

	nRtn = av_frame_get_buffer(m_ptAVFrame, 0);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_frame_get_buffer is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return nullptr;
	}

	m_ptAVPacket = av_packet_alloc();
	if (!m_ptAVPacket)
	{
		std::cerr << "av_packet_alloc is err" << std::endl;
		return nullptr;
	}

	return m_ptAVFrame;
}
