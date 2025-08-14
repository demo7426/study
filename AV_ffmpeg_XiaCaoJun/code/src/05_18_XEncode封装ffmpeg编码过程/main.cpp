/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.14
描  述: 实现对编码ffmpeg过程的测试
备  注:
修改记录:

  1.  日期: 2025.08.14
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>
#include <iomanip> // 包含格式化控制符的头文件

#include "xencode.h"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavutil/opt.h>
}

static void Test_00() 
{
	CXEncode cXEncode;

	constexpr int nWidth = 1920;
	constexpr int nHeight = 1080;
	constexpr int nFrameNum = 300;

	if (cXEncode.Create_AVCodecContext(AV_CODEC_ID_H264, "05_18_XEncode封装ffmpeg编码过程.h264") != 0)
		return;

	AVFrame* ptAVFrame = cXEncode.Set_AVCodecContext_Param(nWidth, nHeight, 30, AV_PIX_FMT_YUV420P, 8);
	
	if (cXEncode.Open())
		return;

	//10s视频 300帧数据
	for (size_t i = 0; i < nFrameNum; i++)
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

		std::cout << std::setw(4) << std::setfill('0') << i << " ";

		if (cXEncode.SendFrame(ptAVFrame))
			break;
	}
}

int main()
{
	Test_00();

	return 0;
}
