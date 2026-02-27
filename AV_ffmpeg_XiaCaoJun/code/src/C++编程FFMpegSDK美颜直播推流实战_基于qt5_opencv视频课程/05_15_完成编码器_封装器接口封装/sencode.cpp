/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sencode.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.27
描  述: 实现对原始数据的编码
备  注:
修改记录:

  1.  日期: 2026.02.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <thread>

#include "sencode.h"

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/codec.h"
#include "libavutil/opt.h"
}

#pragma comment(lib, "avcodec.lib")

CSEncode::~CSEncode()
{
	this->Close();
}

int CSEncode::Init(SAVCodecID _AVCodecID)
{
	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVCodec = avcodec_find_encoder(static_cast<AVCodecID>(_AVCodecID));			//查找编码器
	if (!m_ptAVCodec)
	{
		std::cout << "avcodec_find_encoder is err" << std::endl;
		return -2;
	}

	m_ptAVCodecContext = avcodec_alloc_context3(m_ptAVCodec);						//分配编码器上下文
	if (!m_ptAVCodecContext)
	{
		std::cout << "avcodec_alloc_context3 is err" << std::endl;
		return -2;
	}

	m_llPts = 0;

	return 0;
}

int CSEncode::Open(int _Width, int _Height, int _FrameRate, SAVPixelFormat _PixFmt)
{
	std::unique_lock<std::mutex> lock(m_mut);

	m_ptAVCodecContext->width = _Width;
	m_ptAVCodecContext->height = _Height;
	m_ptAVCodecContext->time_base = { 1, _FrameRate };
	m_ptAVCodecContext->pix_fmt = (AVPixelFormat)_PixFmt;

	m_ptAVCodecContext->bit_rate = 1000000;		// 码率：1Mbps（可根据需求调整）
	m_ptAVCodecContext->gop_size = 10;			// 每10帧一个I帧
	m_ptAVCodecContext->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;	//GLOBAL_HEADER 是为了让编码参数（SPS/PPS）脱离帧流，放入封装头部，以适配非裸流封装格式
	m_ptAVCodecContext->max_b_frames = 1;		// B帧数量
	m_ptAVCodecContext->qmin = 18;				// 最小量化值
	m_ptAVCodecContext->qmax = 40;				// 最大量化值

	av_opt_set(m_ptAVCodecContext->priv_data, "preset", "veryfast", 0);
	av_opt_set(m_ptAVCodecContext->priv_data, "tune", "zerolatency", 0);
	av_opt_set(m_ptAVCodecContext->priv_data, "profile", "baseline", 0);

	m_ptAVCodecContext->thread_count = std::thread::hardware_concurrency();

	int nRtn = avcodec_open2(m_ptAVCodecContext, nullptr, nullptr);
	if (nRtn)
	{
		std::cout << "avcodec_open2 is err" << std::endl;
		return -2;
	}

	return 0;
}

AVPacket* CSEncode::SendFrame(AVFrame* _pAVFrame)
{
	int nRtn = 0;

	_pAVFrame->pts = m_llPts++;

	std::unique_lock<std::mutex> lock(m_mut);

	//发送未压缩数据到线程中压缩
	if (_pAVFrame != nullptr)
	{
		nRtn = avcodec_send_frame(m_ptAVCodecContext, _pAVFrame);
		if (nRtn)
		{
			return nullptr;
		}
	}

	if (nRtn >= 0)		//接收一帧即可
	{
		AVPacket* ptAVPacket = av_packet_alloc();
		if (!ptAVPacket)
		{
			std::cerr << "av_packet_alloc is err" << std::endl;
			return nullptr;
		}

		//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
		//编码是运行在独立的线程中
		//每次调用会重新分配ptAVPacket中的空间
		nRtn = avcodec_receive_packet(m_ptAVCodecContext, ptAVPacket);
		if (nRtn == AVERROR(EAGAIN) || nRtn == AVERROR_EOF)
		{
			av_packet_unref(ptAVPacket);
			av_packet_free(&ptAVPacket);

			return nullptr;
		}

		if (nRtn < 0)		//异常
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;

			av_packet_free(&ptAVPacket);

			return nullptr;
		}

		return ptAVPacket;
	}

	return nullptr;
}

std::vector<AVPacket*> CSEncode::RecvAll_AVPacketData(void)
{
	int nRtn = 0;

	std::vector<AVPacket*> vecAVPacket = {};
	std::unique_lock<std::mutex> lock(m_mut);

	while (1)		//保证线程中编码后的剩余帧，全部取出并写入文件
	{
		AVPacket* ptAVPacket = av_packet_alloc();
		if (!ptAVPacket)
		{
			std::cerr << "av_packet_alloc is err" << std::endl;
			break;
		}

		//发送未压缩数据到线程中压缩
		nRtn = avcodec_send_frame(m_ptAVCodecContext, NULL);		//不需要判定其返回值；因为需要保证线程中编码后的剩余帧，其数据全部被取出

		//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
		//编码狮子啊独立的线程中
		//每次调用会重新分配ptAVPacket中的空间
		nRtn = avcodec_receive_packet(m_ptAVCodecContext, ptAVPacket);
		if (nRtn == AVERROR(EAGAIN) || nRtn == AVERROR_EOF)
		{
			break;
		}

		if (nRtn < 0)		//异常
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;
			break;
		}

		vecAVPacket.push_back(ptAVPacket);
		//av_packet_unref(m_ptAVPacket);		//解引用后会自动释放AVPacket中分配的空间
	}

	return vecAVPacket;
}

void CSEncode::Close()
{
	if (m_ptAVCodecContext)
	{
		avcodec_close(m_ptAVCodecContext);

		avcodec_free_context(&m_ptAVCodecContext);
		m_ptAVCodecContext = nullptr;
	}
}
