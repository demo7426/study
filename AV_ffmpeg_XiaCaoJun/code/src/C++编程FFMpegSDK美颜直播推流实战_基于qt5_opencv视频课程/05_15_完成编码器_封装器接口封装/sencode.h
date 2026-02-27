/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sencode.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.27
描  述: 实现对原始数据的编码
备  注: 
修改记录:

  1.  日期: 2026.02.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#pragma once

#include <vector>
#include <mutex>

struct AVPacket;
struct AVFrame;
struct AVCodec;
struct AVCodecContext;

class CSEncode
{
public:
	CSEncode() = default;
	virtual ~CSEncode();

	enum SAVCodecID
	{
		H264 = 27,
		H265 = 173,
		AAC = 86018
	};
	enum SAVPixelFormat
	{
		YUV420P = 0
	};

	/// <summary>
	/// 初始化编码器
	/// </summary>
	/// <param name="_AVCodecID">编码器ID</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Init(SAVCodecID _AVCodecID);

	/// <summary>
	/// 打开编码器
	/// </summary>
	/// <param name="_Width">宽度</param>
	/// <param name="_Height">高度</param>
	/// <param name="_FrameRate">帧率</param>
	/// <param name="_PixFmt">像素格式</param>
	/// <returns>-2--失败;-1--参数错误;0--成功</returns>
	int Open(int _Width, int _Height, int _FrameRate, SAVPixelFormat _PixFmt);

	/// <summary>
	/// 发送原始的AVFrame数据
	/// </summary>
	/// <param name="_pAVFrame">nullptr--仅仅需要编码后的帧，不再新增数据</param>
	/// <returns>需要手动释放AVPacket及其buf</returns>
	AVPacket* SendFrame(AVFrame* _pAVFrame);

	/// <summary>
	/// 接收残留的所有数据
	/// </summary>
	/// <param name=""></param>
	/// <returns>需要手动释放AVPacket及其buf</returns>
	std::vector<AVPacket*> RecvAll_AVPacketData(void);

	/// <summary>
	/// 获取当前的编码器上下文指针
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	inline AVCodecContext* GetAVCodecContext(void)
	{
		std::unique_lock<std::mutex> lock(m_mut);

		return m_ptAVCodecContext;
	}

	/// <summary>
	/// 关闭编码器并且释放资源
	/// </summary>
	void Close();

private:
	AVCodec* m_ptAVCodec = nullptr;
	AVCodecContext* m_ptAVCodecContext = nullptr;
	
	std::mutex m_mut;

	int64_t m_llPts = 0;
};
