/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcodec.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.18
描  述: 编、解码基类实现
备  注:
修改记录:

  1.  日期: 2025.08.18
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/
#include <iostream>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xcodec.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

CXCodec::~CXCodec()
{

}

void CXCodec::PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}
