/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xencode.h
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

#pragma once

#include <fstream>
#include <thread>
#include <mutex>
#include <vector>

#include "xcodec.h"

class LCB_DLLEXPORT CXEncode: public CXCodec
{
public:
	CXEncode();
	~CXEncode();

	/// <summary>
	/// 创建编码器上下文
	/// </summary>
	/// <param name="_AVCodecID">数据编码后的格式</param>
	/// <returns>nullptr--失败;!nullptr--成功</returns>
	int Create_AVCodecContext(int _AVCodecID);

	/// <summary>
	/// 设置编码器上下文参数
	/// </summary>
	/// <param name="_Width"></param>
	/// <param name="_Height"></param>
	/// <param name="_FrameRate"></param>
	/// <param name="_AVPixelFormat"></param>
	/// <param name="_ThreadCount"></param>
	AVFrame* Set_AVCodecContext_Param(int _Width, int _Height, int _FrameRate, int _AVPixelFormat, int _ThreadCount = std::thread::hardware_concurrency());

	/// <summary>
	/// 预设编码器参数
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_Value"></param>
	/// <returns></returns>
	int AV_Opt_Set(std::string _Name, std::string _Value);

	/// <summary>
	/// 预设编码器参数
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_Value"></param>
	/// <returns></returns>
	int AV_Opt_Set_Int(std::string _Name, int _Value);

	/// <summary>
	/// 初始化编码器或解码器上下文（AVCodecContext）并将其与对应的编解码器（AVCodec）绑定
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int Open(void);

	/// <summary>
	/// 发送原始的AVFrame数据
	/// </summary>
	/// <param name="_pAVFrame"></param>
	/// <returns></returns>
	AVPacket* SendFrame(AVFrame* _pAVFrame);
	
	/// <summary>
	/// 接收残留的所有数据
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<AVPacket*> RecvAll_AVPacketData(void);

	inline AVCodecContext* GetAVCodecContext(void)
	{
		return m_ptAVCodecContext;
	}

private:
	AVCodecContext* m_ptAVCodecContext = nullptr;				//编码器上下文
	AVFrame* m_ptAVFrame = nullptr;

	std::mutex m_mut;

	int m_nFrameNum = 0;

	/// <summary>
	/// 创建并分配AVFrame、AVPacket
	/// </summary>
	/// <param name="_Width"></param>
	/// <param name="_Height"></param>
	/// <param name="_AVPixelFormat"></param>
	/// <returns></returns>
	AVFrame* Create_AVFrameAndAVPacket(int _Width, int _Height, int _AVPixelFormat);
};


