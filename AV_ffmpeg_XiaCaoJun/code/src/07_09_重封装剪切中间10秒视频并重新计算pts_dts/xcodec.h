/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xcodec.h
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

#pragma once

struct AVCodecContext;
struct AVFrame;
struct AVPacket;
struct AVCodecParserContext;

class CXCodec
{
public:
	CXCodec() = default;
	virtual ~CXCodec() = 0;

private:

};
