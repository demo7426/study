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

#include <QtCore/QCoreApplication>
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

/// <summary>
/// 采集的音频信息
/// </summary>
typedef struct _COLLECT_AUDIO_INFO
{
	char CollectAudioBuf[64 * 1024];		//采集的音频缓冲
	int BufValidLen;						//采集音频缓冲的有效长度
	std::mutex MutCollectAudioBuf;
}COLLECT_AUDIO_INFO, * PCOLLECT_AUDIO_INFO;

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

COLLECT_AUDIO_INFO g_tCollectAudioInfo = { 0 };
std::atomic<bool> g_bRunning = true;  // 线程运行标志

// 提取RTSP字符串的函数
std::string ExtractRtmpRtspUrl(const std::string& input_str) {
	// 正则表达式说明：
	// ^rtsp://  匹配以rtsp://开头
	// .+        匹配任意字符（至少一个），覆盖IP、端口、路径等部分
	// $         匹配字符串结尾
	std::regex rtsp_regex(R"(^(rtsp|rtmp)://.+$)");
	std::smatch match_result;

	// 执行正则匹配
	if (std::regex_match(input_str, match_result, rtsp_regex)) {
		// match_result[0] 是整个匹配到的字符串
		return match_result[1].str();
	}
	else {
		return std::string();
	}
}


int main(int argc, char* argv[])
{
	enumerateAudioInputDevices();

	QCoreApplication app(argc, argv);

	int nSampleRate = 44100;			//采样率
	int nChannels = 2;					//通道数
	int nSampleByte = 2;				//采样大小;单位:字节

	int nNbSamples = 1024;

	//std::string strDesUrl = "rtmp://127.0.0.1:1935/live/test";									//输出文件；rtmp url必须是 rtmp://server/app/stream_name
	std::string strDesUrl = "rtsp://127.0.0.1:8554/output";			//输出url

	std::string strUrlHeader = ExtractRtmpRtspUrl(strDesUrl);

	//qt音频录制
	QAudioFormat cAudioFmt;
	cAudioFmt.setSampleRate(nSampleRate);
	cAudioFmt.setChannelCount(nChannels);
	cAudioFmt.setSampleSize(nSampleByte * 8);
	cAudioFmt.setCodec("audio/pcm");
	cAudioFmt.setByteOrder(QAudioFormat::LittleEndian);
	cAudioFmt.setSampleType(QAudioFormat::SignedInt);
	QAudioDeviceInfo cAudioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
	if (!cAudioDeviceInfo.isFormatSupported(cAudioFmt))
	{
		qDebug() << "Audio format not support!";
		return -2;
	}

	QAudioInput* pcAudioInput = new QAudioInput(cAudioFmt);

	//开始录制音频	
	QIODevice* pcIODevice = pcAudioInput->start();
	if (!pcIODevice)
	{
		qDebug() << "AudioInput start failed";
		return -2;
	}

	//音频重采样 上下文初始化
	SwrContext* ptSwrContext = nullptr;
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

	int nRtn = swr_init(ptSwrContext);
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

	QObject::connect(pcIODevice, &QIODevice::readyRead, [pcIODevice]() {
		QByteArray cByteArray = pcIODevice->readAll();
		//std::cout << cByteArray.size() << " ";

		std::lock_guard<std::mutex> lock(g_tCollectAudioInfo.MutCollectAudioBuf);

		if (sizeof g_tCollectAudioInfo.CollectAudioBuf - g_tCollectAudioInfo.BufValidLen < cByteArray.size())
		{
			qDebug() << "Audio buffer overflow!!!";
			return;
		}

		memcpy(g_tCollectAudioInfo.CollectAudioBuf + g_tCollectAudioInfo.BufValidLen, cByteArray.data(), cByteArray.size());
		g_tCollectAudioInfo.BufValidLen += cByteArray.size();
		});

	std::thread th([&]() {
		int64_t llPts = 0;
		AVPacket* ptAVPacket = nullptr;

		while (g_bRunning)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));

			{
				std::lock_guard<std::mutex> lock(g_tCollectAudioInfo.MutCollectAudioBuf);
				if (g_tCollectAudioInfo.BufValidLen < nAudioFrameSize)
				{
					continue;
				}

				//std::cout << g_tCollectAudioInfo.BufValidLen << " ";
				memcpy(chAudioBuf.get(), g_tCollectAudioInfo.CollectAudioBuf, nAudioFrameSize);			//取出一帧音频数据

				//重新计算并且移动缓冲区数据
				g_tCollectAudioInfo.BufValidLen -= nAudioFrameSize;
				memmove(g_tCollectAudioInfo.CollectAudioBuf, g_tCollectAudioInfo.CollectAudioBuf + nAudioFrameSize, g_tCollectAudioInfo.BufValidLen);
			}

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

	// 设置程序退出处理
	QObject::connect(&app, &QCoreApplication::aboutToQuit, [&]() {
		g_bRunning = false; // 通知线程退出
		if (th.joinable())
		{
			th.join(); // 等待线程结束
		}

		// 停止音频采集
		pcAudioInput->stop();

		// 释放资源
		if (ptSwrContext)
		{
			swr_free(&ptSwrContext);
			ptSwrContext = nullptr;
		}

		delete pcAudioInput;

		qDebug() << "程序正常退出，资源已释放";
		});

	/*if (pcAudioInput)
	{
		delete pcAudioInput;
		pcAudioInput = nullptr;
	}*/

	return app.exec();
}
