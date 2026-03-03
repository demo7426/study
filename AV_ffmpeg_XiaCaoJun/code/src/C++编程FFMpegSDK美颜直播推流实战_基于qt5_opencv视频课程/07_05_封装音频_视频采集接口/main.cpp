/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.26
描  述: Qt音频录制->音频重采样空间分配并完成重采样->音视频推流并测试
备  注:
修改记录:

  1.  日期: 2026.02.26
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <QAudioInput>
#include <QDebug>
#include <QTimer>
#include <QAudioDeviceInfo>
#include <QThread>

#include <iostream>
#include <mutex>
#include <regex>
#include <stdexcept>

#include "sencode.h"
#include "smux.h"
#include "saudio_collect.h"

#include "opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

extern "C"
{
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
#include <libavformat/avformat.h>
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
#include "libavcodec/codec.h"
}

#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")

//打印错误信息
static void PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}

// 枚举所有音频输入设备
void enumerateAudioInputDevices()
{
	QList<QAudioDeviceInfo> inputDevices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
	std::cout << "系统可用的音频输入设备列表：\n";
	for (const QAudioDeviceInfo& device : inputDevices)
	{
		qDebug() << "device name：" << device.deviceName();
		qDebug() << "device support type：" << device.supportedCodecs();
	}
}

std::atomic<bool> g_bRunning = true;  // 线程运行标志

/// <summary>
/// 音频录制并推送流
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
static int AudioRecord_PushStream(int argc, char* argv[])
{
	enumerateAudioInputDevices();
	
	int nRtn = 0;
	int nSampleRate = 44100;			//采样率
	int nChannels = 2;					//通道数
	int nSampleByte = 2;				//采样大小;单位:字节

	int nNbSamples = 1024;

	//std::string strDesUrl = "rtmp://127.0.0.1:1935/live/test";									//输出文件；rtmp url必须是 rtmp://server/app/stream_name
	std::string strDesUrl = "rtsp://127.0.0.1:8554/output";			//输出url

	CSAudio_Collect* pcSAudio_Collect = new CSAudio_Collect_Qt(argc, argv);
	if (pcSAudio_Collect->Init(nSampleRate, nChannels, nSampleByte))
	{
		qDebug() << __func__ << ", Init failed";
		return -2;
	}

	SwrContext* ptSwrContext = nullptr;

	//音频重采样 上下文初始化
	ptSwrContext = swr_alloc_set_opts(ptSwrContext,
		av_get_default_channel_layout(nChannels), AV_SAMPLE_FMT_FLTP, nSampleRate,	//输出格式
		av_get_default_channel_layout(nChannels), AV_SAMPLE_FMT_S16, nSampleRate,	//输入格式
		0, nullptr
	);
	if (!ptSwrContext)
	{
		qDebug() << "swr_alloc_set_opts failed";
		return -2;
	}

	nRtn = swr_init(ptSwrContext);
	if (nRtn)
	{
		qDebug() << "swr_init failed";
		PrintErr(nRtn);
		return -2;
	}
	std::cout << "音频重采样 上下文初始化成功!" << std::endl;

	//一次读取一帧音频的字节数
	int nAudioFrameSize = nNbSamples * nChannels * nSampleByte;		//一帧音频字节大小
	std::shared_ptr<char> chAudioBuf(new char[nAudioFrameSize] { 0 }, [&](char* p) {
		if (p)
		{
			delete[] p;
			p = nullptr;
		}
		});

	CSAudioEncode cSAudioEncode;

	if (cSAudioEncode.Init(CSAudioEncode::SAVCodecID::AAC))
	{
		qDebug() << __func__ << ", Init failed";
		return -2;
	}

	if (cSAudioEncode.Open(nSampleRate, nChannels))
	{
		qDebug() << "Open failed";
		return -2;
	}

	CSMux cSMux;

	if (cSMux.Init(strDesUrl.data(), cSAudioEncode.GetAVCodecContext()))
	{
		qDebug() << __func__ << ", init failed";
		return -2;
	}

	//写入文件头
	nRtn = cSMux.Write_Header();
	if (nRtn != 0)
	{
		qDebug() << __func__ << ", avformat_write_header failed";
		return -2;
	}

	std::thread th([&]() {
		int64_t llPts = 0;
		AVPacket* ptAVPacket = nullptr;

		while (g_bRunning)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			if (pcSAudio_Collect->GetData(chAudioBuf.get(), nAudioFrameSize))
				continue;

			AVFrame* ptAVFrame = av_frame_alloc();
			ptAVFrame->format = AV_SAMPLE_FMT_FLTP;
			ptAVFrame->channels = nChannels;
			ptAVFrame->channel_layout = av_get_default_channel_layout(nChannels);
			ptAVFrame->nb_samples = nNbSamples;		//一帧音频一通道的采样数量

			nRtn = av_frame_get_buffer(ptAVFrame, 0);
			if (nRtn)
			{
				qDebug() << "av_frame_get_buffer failed";
				PrintErr(nRtn);
				return -2;
			}

			const uint8_t* uchInData[AV_NUM_DATA_POINTERS] = { nullptr };
			uchInData[0] = (const uint8_t*)chAudioBuf.get();

			//重采样这一帧源数据
			int nSwrConvertLen = swr_convert(ptSwrContext,
				ptAVFrame->data, ptAVFrame->nb_samples,			//输出参数
				uchInData, ptAVFrame->nb_samples				//输入参数
			);
			//std::cout << nSwrConvertLen << " ";

			ptAVPacket = cSAudioEncode.SendFrame(ptAVFrame);
			if (!ptAVPacket)
			{
				av_packet_free(&ptAVPacket);
				ptAVPacket = nullptr;
				continue;
			}

			std::cout << ptAVPacket->size << " ";

			//写入音视频帧，会自动av_packet_unref(&tAVPacket_Demux)
			nRtn = cSMux.Write_Packet(ptAVPacket);
			if (nRtn != 0)
			{
				std::cout << "# ";
				continue;
			}

			//av_packet_unref(&tAVPacket);

			av_frame_unref(ptAVFrame);

			av_frame_free(&ptAVFrame);
			ptAVFrame = nullptr;
		}

		cSAudioEncode.Close();
		cSMux.Close();
	});

	return pcSAudio_Collect->Start();
}

static int VideoRecord_PushStream(int argc, char* argv[])
{
	int nRtn = 0;
	//std::string strSrcUrl = "rtsp://admin:level@12@10.0.0.170:554/Stream";
	std::string strSrcUrl = "D:/BaiduNetdiskDownload/mksz279-2022年经典再升级-FFmpeg5.0核心技术精讲，打造音视频播放器【完结】/{1}--第1章学习指南【课程提供200+问题与答案库】/[1.1]--1-2FFmpeg5.0-课程导学【瑞客论坛 www.ruike1.com】.mp4";
	const std::string strWinName = "video";
	//std::string strDesUrl = "rtsp://127.0.0.1:8554/output";				//输出url
	std::string strDesUrl = "rtmp://127.0.0.1:1935/live/test";;			//输出url

	cv::Mat cMat;
	cv::VideoCapture cVideoCapture;

	SwsContext* ptSwsContext = nullptr;

	AVFrame* ptAVFrame = av_frame_alloc();
	if (!ptAVFrame)
	{
		std::cout << "av_frame_alloc is err" << std::endl;
		return -2;
	}

	AVPacket* ptAVPacket = nullptr;

	CSVideoEncode cSVideoEncode;
	CSMux cSMux;

	cv::namedWindow(strWinName);

	try
	{
		if (!cVideoCapture.open(strSrcUrl))										//打开对应的流
			//if (!cVideoCapture.open(0))										//打开对应的摄像头
		{
			throw std::exception("open is err");
		}

		if (cSVideoEncode.Init(CSEncode::SAVCodecID::H264))
		{
			throw std::exception("CSEncode init is err");
		}

		int nSrcW = cVideoCapture.get(cv::CAP_PROP_FRAME_WIDTH);
		int nSrcH = cVideoCapture.get(cv::CAP_PROP_FRAME_HEIGHT);
		int nSrcFps = cVideoCapture.get(cv::CAP_PROP_FPS);

		uint8_t* uchInData[AV_NUM_DATA_POINTERS] = { 0 };
		int nInSize[AV_NUM_DATA_POINTERS] = { 0 };
		int nInHeight = 0;								//输入高度
		int nOutHeight = 0;								//输出高度

		ptSwsContext = sws_getCachedContext(ptSwsContext,
			nSrcW, nSrcH, AVPixelFormat::AV_PIX_FMT_BGR24,
			nSrcW, nSrcH, AVPixelFormat::AV_PIX_FMT_YUV420P,
			SWS_BILINEAR,	//选择支持变化的算法，双线性插值
			0, 0, 0			//过滤器参数
		);
		if (!ptSwsContext)
		{
			throw std::exception("sws_getCachedContext is err");
		}

		if (cSVideoEncode.Open(nSrcW, nSrcH, nSrcFps, CSEncode::SAVPixelFormat::YUV420P))
		{
			throw std::exception("CSEncode Open is err");
		}

		if (cSMux.Init(strDesUrl.data(), cSVideoEncode.GetAVCodecContext()))
		{
			throw std::exception("CSMux init is err");
		}

		if (cSMux.Write_Header())
		{
			throw std::exception("CSMux Write_Header is err");
		}

		while (1)
		{
			if (!cVideoCapture.grab())					//获取当前帧
				continue;

			//对当前帧进行解码操作
			//cMat的数据为解码后BGR24格式的原始数据，可以理解为AVFrame
			if (!cVideoCapture.retrieve(cMat))
				continue;

			uchInData[0] = cMat.data;
			nInSize[0] = cMat.cols * cMat.elemSize();
			nInHeight = cMat.rows;

			//输出的AVFrame结构
			ptAVFrame->width = cMat.cols;
			ptAVFrame->height = cMat.rows;
			ptAVFrame->format = AVPixelFormat::AV_PIX_FMT_YUV420P;

			//分配空间
			int nRet = av_frame_get_buffer(ptAVFrame,
				32										//如果为0，则使用默认的32字节对齐
			);
			if (nRet)
			{
				av_frame_free(&ptAVFrame);
				ptAVFrame = nullptr;

				std::cout << "av_frame_get_buffer is err" << std::endl;
				PrintErr(nRet);
				return -2;
			}

			//BGR32位数据->YUV420P数据
			nOutHeight = sws_scale(ptSwsContext,
				uchInData,
				nInSize,
				0,							//用于多层图像，当前输入0忽略
				nInHeight,
				ptAVFrame->data,
				ptAVFrame->linesize
			);

			ptAVPacket = cSVideoEncode.SendFrame(ptAVFrame);
			if (!ptAVPacket)		//发送未压缩数据到线程中压缩
			{
				av_frame_unref(ptAVFrame);
				continue;
			}

			std::cout << ptAVPacket->size << " ";

			cSMux.Write_Packet(ptAVPacket);

			if (ptAVPacket)
			{
				av_packet_free(&ptAVPacket);
				ptAVPacket = nullptr;
			}

			av_frame_unref(ptAVFrame);

			cv::imshow(strWinName, cMat);
			cv::waitKey(1);
		}

		auto vecAVPacket = cSVideoEncode.RecvAll_AVPacketData();			//接收残留的所有数据
		for (auto it : vecAVPacket)
		{
			std::cout << it->size << " ";

			cSMux.Write_Packet(it);

			if (it)
			{
				av_packet_free(&it);
				it = nullptr;
			}
		}

		cSVideoEncode.Close();
		cSMux.Close();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	if (ptAVFrame)
	{
		av_frame_free(&ptAVFrame);
		ptAVFrame = nullptr;
	}

	if (cVideoCapture.isOpened())
		cVideoCapture.release();

	if (ptSwsContext)
	{
		sws_freeContext(ptSwsContext);
		ptSwsContext = nullptr;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	return AudioRecord_PushStream(argc, argv);
}
