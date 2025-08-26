/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdecode.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.19
描  述: 实现对ffmpeg解码过程的封装
备  注:
修改记录:

  1.  日期: 2025.08.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "xdecode.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

CXDeCode::CXDeCode()
{

}

CXDeCode::~CXDeCode()
{
	std::unique_lock<std::mutex> lock(m_mut);

	av_parser_close(m_ptAVCodecParserContext);
	m_ptAVCodecParserContext = nullptr;

	av_packet_free(&m_ptAVPacket);
	m_ptAVPacket = nullptr;

	avcodec_free_context(&m_ptAVCodecContext);
	m_ptAVCodecContext = nullptr;
}

int CXDeCode::Create_AVCodecContext(int _AVCodecID, bool _IsEnable_HwDecode)
{
	AVCodecID eAVCodecID = static_cast<AVCodecID>(_AVCodecID);

	std::unique_lock<std::mutex> lock(m_mut);

	//找到解码器 
	AVCodec* ptAVCodec = avcodec_find_decoder(eAVCodecID);
	if (!ptAVCodec)
	{
		std::cerr << "avcodec_find_encoder is err" << std::endl;
		return -2;
	}

	//解码器上下文
	m_ptAVCodecContext = avcodec_alloc_context3(ptAVCodec);
	if (!m_ptAVCodecContext)
	{
		std::cerr << "avcodec_alloc_context3 is err" << std::endl;
		return -2;
	}

	//m_ptAVCodecContext->thread_count = 1;
	m_ptAVCodecContext->thread_count = std::thread::hardware_concurrency();

	if (_IsEnable_HwDecode)											//硬件加速
	{
		for (int i = 0;; i++)
		{
			auto config = avcodec_get_hw_config(ptAVCodec, i);
			if (!config)
				break;

			if (config->device_type)
				std::cout << av_hwdevice_get_type_name(config->device_type) << std::endl;
		}

		AVHWDeviceType eAVHwDeviceType = AV_HWDEVICE_TYPE_DXVA2;							//硬件加速格式 DXVA2

		//硬件加速上下文
		AVBufferRef* ptAVBufferRef = nullptr;
		av_hwdevice_ctx_create(&ptAVBufferRef, eAVHwDeviceType, NULL, NULL, 0);

		m_ptAVCodecContext->hw_device_ctx = av_buffer_ref(ptAVBufferRef);
	}

	m_ptAVCodecParserContext = av_parser_init(static_cast<int>(eAVCodecID));				//初始化解码器

	m_ptAVPacket = av_packet_alloc();
	if (!m_ptAVPacket)
	{
		std::cerr << "av_packet_alloc is err" << std::endl;
		return -2;
	}

	return 0;
}

int CXDeCode::Open(void)
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

std::vector<AVFrame*> CXDeCode::SendData(char* _pDataBuf, int _Len)
{
	int nRtn = 0;													//返回值
	int nAV_ParserLen = 0;											//取出AV_Packet有效长度

	std::vector<AVFrame*> vecAVFrame = {};
	char* chReadBufTmp = _pDataBuf; 
	std::unique_lock<std::mutex> lock(m_mut);

	if (_Len <= 0)
		return vecAVFrame;

	while (_Len > 0)
	{
		nAV_ParserLen = av_parser_parse2(
			m_ptAVCodecParserContext, m_ptAVCodecContext,
			&(m_ptAVPacket->data), &(m_ptAVPacket->size),												//输出数据
			reinterpret_cast<const uint8_t*>(chReadBufTmp), _Len,			//输入数据
			AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0
		);

		chReadBufTmp += nAV_ParserLen;
		_Len -= nAV_ParserLen;

		if (m_ptAVPacket->size == 0)
			continue;

		//解码
		//发送编码后的数据到线程中解码
		nRtn = avcodec_send_packet(m_ptAVCodecContext, m_ptAVPacket);
		av_packet_unref(m_ptAVPacket);   // ★ 重要：释放引用，避免残留
		if (nRtn)
		{
			continue;
		}

		while (nRtn >= 0)		//返回一帧
		{
			AVFrame* ptAVFrame = av_frame_alloc();
			AVFrame* ptAVFrame_Hw = av_frame_alloc();
			AVFrame* ptAVFrame_Tmp = nullptr;
			
			//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
			//编码运行在独立的线程中
			//每次调用会重新分配ptAVPacket中的空间
			nRtn = avcodec_receive_frame(m_ptAVCodecContext, ptAVFrame);
			if (nRtn == AVERROR(EAGAIN))
			{
				av_frame_free(&ptAVFrame);
				av_frame_free(&ptAVFrame_Hw);
				continue;
			}
			else if (nRtn == AVERROR_EOF)
			{
				av_frame_free(&ptAVFrame);
				av_frame_free(&ptAVFrame_Hw);
				break;					//只能break，不能return;因为可能出现解码器中已缓冲但未接收的帧被遗漏
			}

			if (nRtn < 0)		//异常
			{
				char chErrBuf[1024] = { 0 };
				av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

				std::cerr << "av_frame_get_buffer is err" << std::endl;
				std::cout << chErrBuf << std::endl;

				break;			//只能break，不能return;因为可能出现解码器中已缓冲但未接收的帧被遗漏
			}

			ptAVFrame_Tmp = ptAVFrame;

			if (m_ptAVCodecContext->hw_device_ctx)		//硬解码
			{
				//硬解码转换 GPU->CPU（显存->内存）
				//AV_PIX_FMT_NV12

				av_hwframe_transfer_data(ptAVFrame_Hw, ptAVFrame, 0);

				ptAVFrame_Tmp = ptAVFrame_Hw;

				av_frame_unref(ptAVFrame);
				av_frame_free(&ptAVFrame);
			}

			vecAVFrame.push_back(ptAVFrame_Tmp);
		}
	}

	return vecAVFrame;
}

std::vector<AVFrame*> CXDeCode::RecvAll_AVFrameData(void)
{
	int nRtn = 0;													//返回值
	int nAV_ParserLen = 0;											//取出AV_Packet有效长度
	std::vector<AVFrame*> vecAVFrame = {};

	std::unique_lock<std::mutex> lock(m_mut);
	
	//解码
	//发送编码后的数据到线程中解码
	nRtn = avcodec_send_packet(m_ptAVCodecContext, NULL);
	if (nRtn)
	{
		return vecAVFrame;
	}

	while (1)		//返回多帧
	{
		AVFrame* ptAVFrame = av_frame_alloc();
		AVFrame* ptAVFrame_Hw = av_frame_alloc();
		AVFrame* ptAVFrame_Tmp = nullptr;

		//接受解码帧，一般前几次调用返回空（缓冲，立即返回，解码未完成）
		//编码运行在独立的线程中
		//每次调用会重新分配ptAVFrame中的空间
		nRtn = avcodec_receive_frame(m_ptAVCodecContext, ptAVFrame);
		if (nRtn == AVERROR(EAGAIN) )
		{
			av_frame_free(&ptAVFrame);
			av_frame_free(&ptAVFrame_Hw);
			continue;
		}	
		else if (nRtn == AVERROR_EOF)
		{
			av_frame_free(&ptAVFrame);
			av_frame_free(&ptAVFrame_Hw);
			break;								//只能break，不能return;因为可能出现解码器中已缓冲但未接收的帧被遗漏
		}

		if (nRtn < 0)		//异常
		{
			char chErrBuf[1024] = { 0 };
			av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

			std::cerr << "av_frame_get_buffer is err" << std::endl;
			std::cout << chErrBuf << std::endl;
			break;
		}

		ptAVFrame_Tmp = ptAVFrame;

		if (m_ptAVCodecContext->hw_device_ctx)		//硬解码
		{
			//硬解码转换 GPU->CPU（显存->内存）
			//AV_PIX_FMT_NV12

			av_hwframe_transfer_data(ptAVFrame_Hw, ptAVFrame, 0);

			ptAVFrame_Tmp = ptAVFrame_Hw;
		}

		vecAVFrame.push_back(ptAVFrame_Tmp);
	}

	return vecAVFrame;
}

bool CXDeCode::Send_AVPacket(const AVPacket* _pAVPacket)
{
	std::unique_lock<std::mutex> lock(m_mut);

	if(!_pAVPacket)
		return false;

	auto nRet = avcodec_send_packet(m_ptAVCodecContext, _pAVPacket);
	if (nRet != 0)
		return false;

	return true;
}

bool CXDeCode::Recv_AVFrame(AVFrame* _pAVFrame)
{
	std::unique_lock<std::mutex> lock(m_mut);

	if (!_pAVFrame)
		return false;

	auto nRet = avcodec_receive_frame(m_ptAVCodecContext, _pAVFrame);
	if (nRet != 0)
		return false;

	return true;
}
