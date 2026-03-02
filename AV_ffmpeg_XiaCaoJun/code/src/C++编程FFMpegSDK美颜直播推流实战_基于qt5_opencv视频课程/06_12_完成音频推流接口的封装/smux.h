/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	smux.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.27
描  述: 实现对原始数据的封装/推流
备  注:
修改记录:

  1.  日期: 2026.02.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

extern "C" {
#include <libavformat/avformat.h>
}

struct AVPacket;
struct AVFormatContext;
struct AVStream;
struct AVCodecContext;

class CSMux
{
public:
	CSMux() = default;
	virtual ~CSMux();
	
	/// <summary>
	/// 初始化封装器
	/// </summary>
	/// <param name="_pURL">目的url地址</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Init(const char* _pURL, AVCodecContext* codec);

	/// <summary>
	/// 写入头
	/// </summary>
	/// <param name="_pAVFormatContext">解码后，格式化I/O上下文</param>
	/// <returns></returns>
	int Write_Header();

	/// <summary>
	/// 写入数据
	/// </summary>
	/// <param name="_pAVPacket">解码后，原始数据</param>
	/// <returns>-2--失败;0--成功;</returns>
	int Write_Packet(AVPacket* _pAVPacket);
	
	/// <summary>
	/// 写入文件尾，并释放资源
	/// </summary>
	void Close();

private:
	AVFormatContext* m_ptAVFormatContext = nullptr;
	AVStream* m_ptAVStream = nullptr;

	AVRational m_tAVRational;
};
