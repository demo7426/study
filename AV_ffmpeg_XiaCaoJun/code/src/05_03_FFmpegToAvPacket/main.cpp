/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.13
描  述: 编写一个AvFrame(主动生成的未压缩数据)格式转换到AvPacket(.h264、.h265压缩格式数据)
备  注:
修改记录:

  1.  日期: 2025.04.13
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <fstream>

extern "C" {
#include <libavcodec/avcodec.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int main(int argc, char* argv[])
{
	int nRtn = 0;
	std::string strFilePath = "05_03_AvFrameToAvPacket.";
	std::ofstream ofs;

	AVCodecID eAVCodecID;

	if (argc < 2)
	{
		std::cerr << "Input param is err" << std::endl;
		std::cerr << "	Please input: app_name format(h264/h265)" << std::endl;
		return EXIT_FAILURE;
	}

	if (!strcmp(argv[1], "h264"))
	{
		strFilePath += argv[1];
		eAVCodecID = AV_CODEC_ID_H264;
	}
	else if (!strcmp(argv[1], "h265"))
	{
		strFilePath += argv[1];
		eAVCodecID = AV_CODEC_ID_H265;
	}
	else
	{
		std::cerr << "Input param is err" << std::endl;
		std::cerr << "	Please input: app_name format(h264/h265)" << std::endl;
		return EXIT_FAILURE;
	}

	ofs.open(strFilePath, std::ios_base::binary);
	if (!ofs.is_open())
	{
		std::cerr << "Open file is err" << std::endl;
		return EXIT_FAILURE;
	}

	//1、找到编码器 
	AVCodec* ptAVCodec =  avcodec_find_encoder(eAVCodecID);
	if (!ptAVCodec)
	{
		std::cerr << "avcodec_find_encoder is err" << std::endl;
		return EXIT_FAILURE;
	}

	//2、编码器上下文
	AVCodecContext* ptAVCodecContext = avcodec_alloc_context3(ptAVCodec);
	if (!ptAVCodecContext)
	{
		std::cerr << "avcodec_alloc_context3 is err" << std::endl;
		return EXIT_FAILURE;
	}

	//3、设定上下文参数
	ptAVCodecContext->width = 400;
	ptAVCodecContext->height = 300;						
	ptAVCodecContext->time_base = { 1, 30 };			//帧时间戳的时间单位，1/30代表每秒30帧
	ptAVCodecContext->pix_fmt = AV_PIX_FMT_YUV420P;		//源数据像素格式，与编程算法相关
	ptAVCodecContext->thread_count = 16;					//编码线程数

	nRtn = avcodec_open2(ptAVCodecContext, ptAVCodec, NULL);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);
		
		std::cerr << "avcodec_open2 is err" << std::endl;
		std::cout << chErrBuf << std::endl;		
		return EXIT_FAILURE;
	}

	//创建AvFrame空间 未压缩数据
	AVFrame* ptAVFrame = av_frame_alloc();
	ptAVFrame->width = ptAVCodecContext->width;
	ptAVFrame->height = ptAVCodecContext->height;
	ptAVFrame->format = ptAVCodecContext->pix_fmt;

	nRtn = av_frame_get_buffer(ptAVFrame, 0);
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_frame_get_buffer is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return EXIT_FAILURE;
	}

	AVPacket* ptAVPacket = av_packet_alloc();
	if (!ptAVPacket)
	{
		std::cerr << "av_packet_alloc is err" << std::endl;
		return EXIT_FAILURE;
	}

	//10s视频 300帧数据
	for (size_t i = 0; i < 300; i++)
	{
		//生成AvFrame数据

		//Y
		for (size_t y = 0; y < ptAVFrame->height; y++)
		{
			for (size_t x = 0; x < ptAVFrame->width; x++)
				ptAVFrame->data[0][y * ptAVFrame->linesize[0] + x] = x + y + i * 3;
		}

		//UV
		for (size_t y = 0; y < ptAVFrame->height / 2; y++)
		{
			for (size_t x = 0; x < ptAVFrame->width / 2; x++)
			{
				ptAVFrame->data[1][y * ptAVFrame->linesize[1] + x] = 128 + y + i * 2;
				ptAVFrame->data[2][y * ptAVFrame->linesize[2] + x] = 64 + x + i * 5;
			}
		}

		ptAVFrame->pts = i;		//显示的时间

		//发送未压缩数据到线程中压缩
		nRtn = avcodec_send_frame(ptAVCodecContext, ptAVFrame);
		if (nRtn)
		{
			break;
		}

		while (nRtn >= 0)		//返回多帧
		{
			//接受压缩帧，一遍前几次调用返回空（缓冲，立即返回，编码未完成）
			//编码狮子啊独立的线程中
			//每次调用会重新分配ptAVPacket中的空间
			nRtn = avcodec_receive_packet(ptAVCodecContext, ptAVPacket);
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

			//接收到了啊压缩后的数据
			std::cout << ptAVPacket->size << " " << std::flush;

			ofs.write((const char*)ptAVPacket->data, ptAVPacket->size);
			ofs.flush();

			av_packet_unref(ptAVPacket);		//解引用后会自动释放AVPacket中分配的空间
		}
	}

	std::cout << std::endl;

	av_packet_free(&ptAVPacket);
	ptAVPacket = nullptr;

	av_frame_free(&ptAVFrame);
	ptAVFrame = nullptr;

	avcodec_free_context(&ptAVCodecContext);
	ptAVCodecContext = nullptr;

	return EXIT_SUCCESS;
}
