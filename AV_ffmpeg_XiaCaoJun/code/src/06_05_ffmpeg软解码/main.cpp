/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.15
描  述: 实现一个h264、h265的解码，并渲染到ui上
备  注: ffmpeg -i xxx.mp4 -s 400x300 06_05_ffmpeg软解码.h264
修改记录:

  1.  日期: 2025.08.15
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>
#include <chrono>
#include <thread>

#include "xsdl.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int main()
{
	int nRtn = 0;													//返回值
	std::string strSrcFilePath = "06_05_ffmpeg软解码.h264";			//源文件路劲
	AVCodecID eAVCodecID = AV_CODEC_ID_NONE;						//格式ID

	std::regex pattern(R"(\.([^.]+)$)");							//匹配最后一个点及其后的内容
	std::smatch match;

	if (std::regex_search(strSrcFilePath, match, pattern)) {
		// match[1] 包含第一个捕获组，即后缀部分
		if (strcmp(match[1].str().c_str(), "h264") == 0)
			eAVCodecID = AV_CODEC_ID_H264;
		else if (strcmp(match[1].str().c_str(), "h265") == 0)
			eAVCodecID = AV_CODEC_ID_H265;
		else
		{
			std::cout << "源文件：" << strSrcFilePath << " 格式错误" << std::endl;
			return EXIT_FAILURE;
		}
	}
	else {
		std::cout << "未找到后缀" << std::endl;
	}

	//解码并渲染

	AVCodec* ptAVCodec = nullptr;
	AVCodecContext* ptAVCodecContext = nullptr;
	AVCodecParserContext* ptAVCodecParserContext = nullptr;
	AVPacket* ptAVPacket = nullptr;
	AVFrame* ptAVFrame = nullptr;

	CXVideo_View* m_pcXVideo_View = nullptr;
	CXVideo_View::Format eFmt = CXVideo_View::Format::YUV420P;

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	char chReadBuf[4096] = { 0 };			//读取缓冲
	int nReadValidLen = 0;					//读取有效长度
	int nAV_ParserLen = 0;					//取出AV_Packet有效长度

	int nFrameCounter = 0;					//帧数计数

	std::fstream ifs(strSrcFilePath, std::ios::binary | std::ios::in);
	if (!ifs.is_open())
	{
		std::cout << "源文件打开失败" << std::endl;
		return EXIT_FAILURE;
	}

	//找到解码器 
	ptAVCodec = avcodec_find_decoder(eAVCodecID);
	if (!ptAVCodec)
	{
		std::cerr << "avcodec_find_decoder is err" << std::endl;
		return EXIT_FAILURE;
	}

	//解码器上下文
	ptAVCodecContext = avcodec_alloc_context3(ptAVCodec);
	if (!ptAVCodecContext)
	{
		std::cerr << "avcodec_alloc_context3 is err" << std::endl;
		return EXIT_FAILURE;
	}

	ptAVCodecContext->thread_count = 16;

	nRtn = avcodec_open2(ptAVCodecContext, NULL, NULL);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "avcodec_open2 is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return EXIT_FAILURE;
	}

	ptAVPacket = av_packet_alloc();
	if (!ptAVPacket)
	{
		std::cerr << "av_packet_alloc is err" << std::endl;
		return EXIT_FAILURE;
	}

	ptAVFrame = av_frame_alloc();

	ptAVCodecParserContext = av_parser_init(static_cast<int>(eAVCodecID));			//初始化解码器

	m_pcXVideo_View = CXVideo_View::Create();

	while (!ifs.eof())		//循环读取源文件数据，并解码
	{
		ifs.read(chReadBuf, sizeof(chReadBuf));

		nReadValidLen = ifs.gcount();
		auto chReadBufTmp = chReadBuf;

		while (nReadValidLen > 0) {
			nAV_ParserLen = av_parser_parse2(
				ptAVCodecParserContext, ptAVCodecContext,
				&(ptAVPacket->data), &(ptAVPacket->size),							//输出数据
				reinterpret_cast<const uint8_t*>(chReadBufTmp), nReadValidLen,		//输入数据
				AV_NOPTS_VALUE, AV_NOPTS_VALUE, 0
			);

			chReadBufTmp += nAV_ParserLen;
			nReadValidLen -= nAV_ParserLen;

			if (ptAVPacket->size == 0)
				continue;

			//std::cout << ptAVPacket->size << " ";

			//解码
			//发送编码后的数据到线程中解码
			nRtn = avcodec_send_packet(ptAVCodecContext, ptAVPacket);
			if (nRtn)
			{
				break;
			}

			while (nRtn >= 0)		//返回多帧
			{
				static bool bInitFlag = false;

				//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
				//编码狮子啊独立的线程中
				//每次调用会重新分配ptAVPacket中的空间
				nRtn = avcodec_receive_frame(ptAVCodecContext, ptAVFrame);
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
					return EXIT_FAILURE;
				}

				if (!bInitFlag)
				{
					switch (ptAVFrame->format)
					{
					case AVPixelFormat::AV_PIX_FMT_RGBA:
						eFmt = CXVideo_View::Format::RGBA;
						break;
					case AVPixelFormat::AV_PIX_FMT_ARGB:
						eFmt = CXVideo_View::Format::ARGB;
						break;
					case AVPixelFormat::AV_PIX_FMT_YUV420P:
						eFmt = CXVideo_View::Format::YUV420P;
						break;
					default:
						break;
					}

					m_pcXVideo_View->Init(ptAVFrame->width, ptAVFrame->height, eFmt, nullptr);
					bInitFlag = true;
				}

				m_pcXVideo_View->DrawFrame(ptAVFrame);
				
				nFrameCounter++;

				cEnd_TimePoint = std::chrono::high_resolution_clock::now();
				if (std::chrono::duration_cast<std::chrono::milliseconds>(cEnd_TimePoint - cStart_TimePoint).count() >= 1000)
				{
					std::cout << "每秒帧数：" << nFrameCounter << std::endl;

					nFrameCounter = 0;
					cStart_TimePoint = cEnd_TimePoint;
				}

			}
		}

	}

	//处理解码线程中的残留数据
	nRtn = avcodec_send_packet(ptAVCodecContext, NULL);
	while (nRtn >= 0)		//返回多帧
	{
		//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
		//编码狮子啊独立的线程中
		//每次调用会重新分配ptAVPacket中的空间
		nRtn = avcodec_receive_frame(ptAVCodecContext, ptAVFrame);
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
			return EXIT_FAILURE;
		}

		m_pcXVideo_View->DrawFrame(ptAVFrame);

		nFrameCounter++;

		cEnd_TimePoint = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cEnd_TimePoint - cStart_TimePoint).count() >= 1000)
		{
			std::cout << "每秒帧数：" << nFrameCounter << std::endl;

			nFrameCounter = 0;
			cStart_TimePoint = cEnd_TimePoint;
		}
	}

	//清理资源
	if (ifs.is_open())
		ifs.close();

	av_parser_close(ptAVCodecParserContext);
	ptAVCodecParserContext = nullptr;

	av_packet_free(&ptAVPacket);
	ptAVPacket = nullptr;

	av_frame_free(&ptAVFrame);
	ptAVFrame = nullptr;

	avcodec_free_context(&ptAVCodecContext);
	ptAVCodecContext = nullptr;

	return EXIT_SUCCESS;
}
