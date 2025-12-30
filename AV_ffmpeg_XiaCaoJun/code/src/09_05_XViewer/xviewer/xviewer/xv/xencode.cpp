/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xencode.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.14
描  述: 实现对ffmpeg编码过程的封装
备  注:
修改记录:

  1.  日期: 2025.08.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

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
	std::unique_lock<std::mutex> lock(m_mut);

	av_frame_free(&m_ptAVFrame);
	m_ptAVFrame = nullptr; 

	avcodec_free_context(&m_ptAVCodecContext);
	m_ptAVCodecContext = nullptr;
}

int CXEncode::Create_AVCodecContext(int _AVCodecID)
{
	AVCodecID eAVCodecID = static_cast<AVCodecID>(_AVCodecID);

	std::unique_lock<std::mutex> lock(m_mut);

	//找到编码器
	AVCodec* ptAVCodec = (AVCodec*)avcodec_find_encoder(eAVCodecID);
	if (!ptAVCodec)
	{
		std::cerr << "avcodec_find_encoder is err" << std::endl;
		return -2;
	}

	//编码器上下文
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
	m_ptAVCodecContext->time_base = { 1, _FrameRate };								//帧时间戳的时间单位，比如1/30代表每秒30帧
	m_ptAVCodecContext->pix_fmt = static_cast<AVPixelFormat>(_AVPixelFormat);		//源数据像素格式，与编程算法相关
	m_ptAVCodecContext->thread_count = _ThreadCount;								//编码线程数

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

AVPacket* CXEncode::SendFrame(AVFrame* _pAVFrame)
{
	int nRtn = 0;

	std::unique_lock<std::mutex> lock(m_mut);

	//发送未压缩数据到线程中压缩
	nRtn = avcodec_send_frame(m_ptAVCodecContext, _pAVFrame);
	if (nRtn)
	{
		return nullptr;
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
			return nullptr;
		}

		if (nRtn < 0)		//异常
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;
			return nullptr;
		}

		m_nFrameNum++;

		return ptAVPacket;
		//av_packet_unref(ptAVPacket);		//解引用后会自动释放AVPacket中分配的空间
	}

	return nullptr;
}

std::vector<AVPacket*> CXEncode::RecvAll_AVPacketData(void)
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

		m_nFrameNum++;

		vecAVPacket.push_back(ptAVPacket);
		//av_packet_unref(m_ptAVPacket);		//解引用后会自动释放AVPacket中分配的空间
	}

	std::cout << "帧数：" << m_nFrameNum << std::endl;
	return vecAVPacket;
}

AVFrame* CXEncode::Create_AVFrameAndAVPacket(int _Width, int _Height, int _AVPixelFormat)
{
	int nRtn = 0;

	//创建AvFrame空间 未压缩数据
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


	return m_ptAVFrame;
}
