/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xdecode.h
作  者:	钱锐      版本: V0.1.2     新建日期: 2025.08.19
描  述: 实现对ffmpeg解码过程的封装
备  注: 
修改记录:

  1.  日期: 2025.08.19
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

  2.  日期: 2025.08.26
	  作者: 钱锐
	  内容:
		  1) 扩展Send_AVPacket、Recv_AVFrame接口，用于MP4格式编码后数据的解码;
	  版本:V0.1.1

  3.  日期: 2025.08.29
	  作者: 钱锐
	  内容:
		  1) 扩展Set_AVCodecParameters接口，用于设置解码参数;
	  版本:V0.1.2

*************************************************/

#pragma once

#include <string>
#include <vector>
#include <mutex>

#include "xcodec.h"

class CXDecode: public CXCodec
{
public:
	CXDecode();
	~CXDecode();

	/// <summary>
	/// 创建编码器上下文
	/// </summary>
	/// <param name="_AVCodecID">数据编码后的格式</param>
	/// <param name="_IsEnable_HwDecode">是否使能硬件解码;false--不使能;true--使能;</param>
	/// <returns>nullptr--失败;!nullptr--成功</returns>
	int Create_AVCodecContext(int _AVCodecID, bool _IsEnable_HwDecode);

	/// <summary>
	/// 设置解码参数
	/// </summary>
	/// <param name="_pAVCodecParameters"></param>
	/// <returns></returns>
	int Set_AVCodecParameters(AVCodecParameters* _pAVCodecParameters);

	/// <summary>
	/// 初始化编码器或解码器上下文（AVCodecContext）并将其与对应的编解码器（AVCodec）绑定
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	int Open(void);

	/// <summary>
	/// 发送原始的AVFrame数据
	/// </summary>
	/// <param name="_pDataBuf">原始数据</param>
	/// <param name="_Len">原始数据长度</param>
	/// <returns></returns>
	std::vector<AVFrame*> SendData(char* _pDataBuf, int _Len);

	/// <summary>
	/// 接收残留的所有数据
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	std::vector<AVFrame*> RecvAll_AVFrameData(void);

	/// <summary>
	/// 发送编码 Send_AVPacket--Recv_AVFrame搭配使用
	/// </summary>
	/// <param name="_pAVPacket"></param>
	/// <returns></returns>
	bool Send_AVPacket(const AVPacket* _pAVPacket);

	/// <summary>
	/// 获取解码 Send_AVPacket--Recv_AVFrame搭配使用
	/// </summary>
	/// <param name="_pAVFrame"></param>
	/// <returns></returns>
	bool Recv_AVFrame(AVFrame* _pAVFrame);

	inline struct AVCodecContext* GetAVCodecContext(void)
	{
		return m_ptAVCodecContext;
	}

private:
	struct AVCodecContext* m_ptAVCodecContext = nullptr;				//编码器上下文
	AVPacket* m_ptAVPacket = nullptr;


	AVCodecParserContext* m_ptAVCodecParserContext = nullptr;

	std::mutex m_mut;

	int m_nFrameNum = 0;

	bool m_bInitFlag = false;
};

