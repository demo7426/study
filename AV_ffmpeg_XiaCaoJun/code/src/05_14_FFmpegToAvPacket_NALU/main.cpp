﻿/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.1     新建日期: 2025.04.15
描  述: 编写一个AvFrame(主动生成的未压缩数据)格式转换到AvPacket(.h264、.h265压缩格式数据)，在上一版的基础上扩展支持预设编码器参数
备  注: 
修改记录:

  1.  日期: 2025.04.15
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

  2.  日期: 2025.04.16
	  作者: 钱锐
	  内容:
		  1) 扩展支持平均码率、恒定QP质量(CQP)、恒定比特率(CBR)、恒定速率因子(CRF)、约束编码(VBV);
	  版本:V0.1.1
*************************************************/

#include <iostream>
#include <fstream>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

int main(int argc, char* argv[])
{
	int nRtn = 0;
	std::string strFilePath = "05_14_FFmpegToAvPacket_NALU.";
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

	constexpr int64_t ullBitRate = 100'000;
	//预设编码器参数
#if 0	//选择一个
	nRtn = av_opt_set(ptAVCodecContext->priv_data, "preset", "ultrafast", 0);			//编码最快速度，但是压缩程度不高
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_opt_set is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return EXIT_FAILURE;
	}
#elif 0
	ptAVCodecContext->max_b_frames = 0;
	nRtn = av_opt_set(ptAVCodecContext->priv_data, "tune", "zerolatency", 0);			//零延时，编码后不会产生b帧，画面实时性能最高
	if (nRtn != 0)
	{
		char chErrBuf[1024] = { 0 };
		av_strerror(nRtn, chErrBuf, sizeof(chErrBuf) - 1);

		std::cerr << "av_opt_set is err" << std::endl;
		std::cout << chErrBuf << std::endl;
		return EXIT_FAILURE;
	}
#elif 0
	//平均码率，单位为bit
	ptAVCodecContext->bit_rate = ullBitRate;
#elif 0
	//CQP 恒定质量 h264中的QP范围从0到51，如果QP为0则接近无损压缩质量
	//	h264 QP默认23 效果较好18
	//	h265 QP默认28 效果较好25
	av_opt_set_int(ptAVCodecContext->priv_data, "qp", 23, 0);
#elif 0
	//恒定比特率(CBR) 由于MP4不支持NAL填充，因此输出文件必须为（MPEG-2 TS）
	//电影一般就是恒定比特率(CBR)的，比如在画面快速变化的时候，画面会模糊
	ptAVCodecContext->rc_min_rate = ullBitRate;
	ptAVCodecContext->rc_max_rate = ullBitRate;
	ptAVCodecContext->rc_buffer_size = ullBitRate * 2;
	ptAVCodecContext->bit_rate = ullBitRate;
	av_opt_set(ptAVCodecContext->priv_data, "nal-hrd", "cbr", 0);
#elif 0
	//恒定速率因子（CRF）,一般用于约束编码（VBV）
	av_opt_set_int(ptAVCodecContext->priv_data, "crf", 23, 0);
#elif 1
	//约束编码（VBV）
	av_opt_set_int(ptAVCodecContext->priv_data, "crf", 23, 0);
	ptAVCodecContext->rc_max_rate = ullBitRate;
	ptAVCodecContext->rc_buffer_size = ullBitRate * 2;
#endif

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
			//std::cout << ptAVPacket->size << " " << std::flush;

#if 1
			/*
			分析NALU
			一个典型的 NALU 包含两部分：
				起始码（Start Code）：
				通常是 0x000001 或 0x00000001（3 字节或 4 字节），用于标识一个新的 NALU 开始。
				比如 00 00 01 或 00 00 00 01

			NAL Header（1 字节）：
				以 H.264 为例：
				forbidden_zero_bit：1 bit，必须为0
				nal_ref_idc：2 bit，表示这个NALU的重要程度

			nal_unit_type：5 bit，表示当前 NALU 的类型，例如：
				类型值	名称		含义
				1		非IDR图像	普通帧，如P帧、B帧
				5		IDR图像		关键帧，解码不依赖其他帧
				6		SEI			补充增强信息
				7		SPS			序列参数集（分辨率、帧率）
				8		PPS			图像参数集
				9		AUD			访问单元分隔符
			RBSP 数据（Raw Byte Sequence Payload）：
				编码后的实际视频数据。
			*/

			int nNalUnit_Type = 0;
			unsigned char uchNalHead = *(ptAVPacket->data + 4);		//+4 去掉开头的0001

			nNalUnit_Type = uchNalHead & 0x1f;						//只取后5位，0001 1111
			std::cout << nNalUnit_Type << " " << std::flush;

			for (size_t i = 4; i < ptAVPacket->size; i++)
			{
				if (ptAVPacket->data[i] == 0 && ptAVPacket->data[i + 1] == 0 && ptAVPacket->data[i + 2] == 1)
				{
					nNalUnit_Type = ptAVPacket->data[i + 3] & 0x1f;
					std::cout << "(" << nNalUnit_Type << ") " << std::flush;
				}
				
			}
#endif

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
