/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xencode_mux_task.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.01.17
描  述: 线程内部实现重编码和封装
备  注:
修改记录:

  1.  日期: 2026.01.17
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include "debug.h"
#include "xencode_mux_task.h"

CXEncode_Mux_Task::~CXEncode_Mux_Task()
{
	// 停止线程
	this->Stop();

	// 清理待编码的AVFrame队列
	AVFrame* ptAVFrame = nullptr;
	while ((ptAVFrame = m_cAVFrame_List.Pop()) != nullptr)
	{
		av_frame_unref(ptAVFrame);
		av_frame_free(&ptAVFrame);
	}

	// 清理编码后的Packet队列
	AVPacket* ptAVPacket = nullptr;
	while ((ptAVPacket = m_cXAVPacket_List.Pop()) != nullptr) 
	{
		av_packet_unref(ptAVPacket);
		av_packet_free(&ptAVPacket);
	}
}

bool CXEncode_Mux_Task::Open(int _AVCodecID, const char* _pOutURL, CXDemux* _pcXDemux, CXDecode* _pcXDecode)
{
	AVCodecParameters* ptAVCodecParameters = _pcXDemux->GetAVStream_Video()->codecpar;					//视频编码参数

	//编码初始化

	m_cXEnCode.Create_AVCodecContext(_AVCodecID);
	m_cXEnCode.Set_AVCodecContext_Param(ptAVCodecParameters->width, ptAVCodecParameters->height,
		_pcXDemux->GetAVStream_Video()->avg_frame_rate.num / _pcXDemux->GetAVStream_Video()->avg_frame_rate.den,
		_pcXDecode->GetAVCodecContext()->pix_fmt
	);

	// ========== 修复：补充完整的x265参数，解决帧类型冲突 ==========
	// 基础质量/速度配置
	m_cXEnCode.AV_Opt_Set_Int("crf", 23);       // 恒定质量模式
	m_cXEnCode.AV_Opt_Set("preset", "medium");  // 编码速度/质量权衡
	// 关键帧与GOP配置（解决SI帧与关键帧间隔冲突）
	m_cXEnCode.AV_Opt_Set_Int("g", 50);         // 关键帧间隔（GOP大小）
	m_cXEnCode.AV_Opt_Set_Int("keyint", 50);    // 与g参数一致，避免冲突
	m_cXEnCode.AV_Opt_Set_Int("min-keyint", 10);// 最小关键帧间隔，兼容自动帧类型
	// B帧配置（解决max B-frames兼容问题）
	m_cXEnCode.AV_Opt_Set_Int("bframes", 3);    // 显式指定最大B帧数量
	m_cXEnCode.AV_Opt_Set_Int("b-adapt", 2);    // 自动适配B帧数量（最优算法）
	m_cXEnCode.AV_Opt_Set("b-pyramid", "none"); // 禁用B帧金字塔，避免SI帧冲突
	// 禁用手动帧类型干预（核心：消除SI帧冲突）
	m_cXEnCode.AV_Opt_Set_Int("force-keyframing", 0); // 禁止强制关键帧，让x265自动分配
	m_cXEnCode.AV_Opt_Set_Int("force-cfr", 1);  // 强制恒定帧率，避免帧序错乱
	// H.265基础参数
	m_cXEnCode.AV_Opt_Set("profile", "main");   // 添加profile设置
	m_cXEnCode.AV_Opt_Set("level", "3.1");      // 添加level设置

	m_cXEnCode.Open();

	//封装初始化

	constexpr double dbBeginSec = 00.0;							//截取开始时间
	constexpr double dbEndSec = dbBeginSec + 300;					//截取结束时间

	m_cXMux.Create_AVFormatContext(_pOutURL);

	/*m_cXMux.SetBeginSec(dbBeginSec);
	m_cXMux.SetEndSec(dbEndSec);*/

	//cXMux.SetVideoParameters(&cXDemux.GetAVStream_Video()->time_base, (const AVCodecParameters*)cXDemux.GetAVStream_Video()->codecpar);
	m_cXMux.Set_EncodeFormat(&_pcXDemux->GetAVStream_Video()->time_base, m_cXEnCode.GetAVCodecContext());		//必须使用这个，上一行代码在重编码时，不可用
	m_cXMux.SetAudioParameters(&_pcXDemux->GetAVStream_Audio()->time_base, (const AVCodecParameters*)_pcXDemux->GetAVStream_Audio()->codecpar);

	m_cXMux.Write_Header(_pcXDemux->GetAVFormatContext(), _pcXDemux->GetAVStream_Video(), _pcXDemux->GetAVStream_Audio());

	return true;
}

int CXEncode_Mux_Task::Send_AVFrame(AVFrame* _ptAVFrame)
{
	if (_ptAVFrame == nullptr)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "Input parameter is err");
		return -1;
	}

    AVFrame* ptAVFrame = av_frame_alloc();
	if (!ptAVFrame) 
	{
		DEBUG(DEBUG_LEVEL_ERROR, "av_frame_alloc is err");
		return -2; 
	}

    av_frame_ref(ptAVFrame, _ptAVFrame);

	// ========== 修复：重置帧类型，消除SI帧（类型5）标记 ==========
	//ptAVFrame->pict_type = AV_PICTURE_TYPE_NONE;	// 让x265自动分配帧类型
	//ptAVFrame->key_frame = 0;						// 禁止强制标记关键帧s
	//ptAVFrame->pts = AV_NOPTS_VALUE;				// 重置时间戳，让编码器重新计算
	//ptAVFrame->pkt_dts = AV_NOPTS_VALUE;

    m_cAVFrame_List.Push(ptAVFrame);
	
	if(m_cAVFrame_List.Size() == 1)
		m_cond.notify_one();

	while (m_cAVFrame_List.Size() >= XPUBLIC_ENCODE_MAX_NODE_NUM)			//反压，控制程序占用的ddr大小
	{
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}

	return 0;
}

void CXEncode_Mux_Task::Main(void)
{
	AVFrame* ptAVFrame = nullptr;
	AVPacket* ptAVPacket = nullptr;

	// 提前获取编码器和封装器的time_base（避免循环内重复获取）
	AVRational enc_time_base = m_cXEnCode.GetAVCodecContext()->time_base;
	AVRational mux_video_time_base = m_cXMux.GetVideoStream()->time_base;

	while (1)
	{
		{
			std::lock_guard<std::mutex> lock(m_cMut);
			if (m_IsExit)
			{
				DEBUG(DEBUG_LEVEL_INFO, "CXDemux_Task is end");
				break;
			}
		}

		if (m_bIsPause)			//暂停
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		{
			std::unique_lock<std::mutex> lock(m_mut);
			m_cond.wait(lock, [&]() {
				std::this_thread::sleep_for(std::chrono::microseconds(1));
				ptAVFrame = m_cAVFrame_List.Pop();
				return ptAVFrame != nullptr;
				});
		}

		if (ptAVFrame == nullptr)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		while (1)		//取出所有编码后的数据;防止过多的编码后的数据缓冲在ffmpeg的ddr中,而导致的ddr不断上涨
		{
			ptAVPacket = m_cXEnCode.SendFrame(ptAVFrame);

			if (ptAVFrame)
			{
				av_frame_unref(ptAVFrame);
				av_frame_free(&ptAVFrame);
				ptAVFrame = nullptr;
			}

			if (ptAVPacket == nullptr)
			{	
				//当前编码后的数据已经完全取出
				//std::this_thread::sleep_for(std::chrono::milliseconds(1));
				break;
			}

			//{
			//	// ========== 修复：转换Packet时间戳到封装器的time_base ==========
			//	// 1. 设置正确的流索引（必须为视频流索引，通常是0）
			//	ptAVPacket->stream_index = 0;
			//	// 2. 转换PTS/DTS从编码器time_base到封装器time_base
			//	if (ptAVPacket->pts != AV_NOPTS_VALUE) {
			//		ptAVPacket->pts = av_rescale_q(ptAVPacket->pts, enc_time_base, mux_video_time_base);
			//	}
			//	if (ptAVPacket->dts != AV_NOPTS_VALUE) {
			//		ptAVPacket->dts = av_rescale_q(ptAVPacket->dts, enc_time_base, mux_video_time_base);
			//	}
			//	// 3. 确保duration合法（可选，优化封装）
			//	if (ptAVPacket->duration == 0) {
			//		ptAVPacket->duration = av_rescale_q(1, enc_time_base, mux_video_time_base);
			//	}
			//}

			if (m_cXMux.Write_Frame(ptAVPacket) != 0)
			{
				av_packet_unref(ptAVPacket);
				av_packet_free(&ptAVPacket);

				break;
			}

			av_packet_unref(ptAVPacket);
			av_packet_free(&ptAVPacket);
		}
	}

	//收尾
	auto vecAVPacket = m_cXEnCode.RecvAll_AVPacketData();
	for (auto item : vecAVPacket)
	{
		item->stream_index = 0;

		//{
		//	// 转换残留Packet的时间戳
		//	if (item->pts != AV_NOPTS_VALUE) {
		//		item->pts = av_rescale_q(item->pts, enc_time_base, mux_video_time_base);
		//	}
		//	if (item->dts != AV_NOPTS_VALUE) {
		//		item->dts = av_rescale_q(item->dts, enc_time_base, mux_video_time_base);
		//	}
		//	if (item->duration == 0) {
		//		item->duration = av_rescale_q(1, enc_time_base, mux_video_time_base);
		//	}
		//}

		if (m_cXMux.Write_Frame(item) != 0)
			break;

		av_packet_unref(item);
		av_packet_free(&item);
		item = nullptr;
	}

	m_cXMux.Close();
}
