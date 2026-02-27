/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.26
描  述: Qt音频录制、音频重采样空间分配并完成重采样
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

extern "C"
{
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
}

#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "avutil.lib")

/// <summary>
/// 采集的音频信息
/// </summary>
typedef struct _COLLECT_AUDIO_INFO
{
	char CollectAudioBuf[64 * 1024];		//采集的音频缓冲
	int BufValidLen;						//采集音频缓冲的有效长度
	std::mutex MutCollectAudioBuf;
}COLLECT_AUDIO_INFO, *PCOLLECT_AUDIO_INFO;
 
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

int main(int argc, char* argv[])
{
	enumerateAudioInputDevices();

	QCoreApplication app(argc, argv);

	int nSampleRate = 44100;			//采样率
	int nChannelCount = 2;				//通道数
	int nSampleByte = 2;				//采样大小;单位:字节

	//qt音频录制
	QAudioFormat cAudioFmt;
	cAudioFmt.setSampleRate(nSampleRate);
	cAudioFmt.setChannelCount(nChannelCount);
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
		av_get_default_channel_layout(nChannelCount), AV_SAMPLE_FMT_FLTP, nSampleRate,	//输出格式
		av_get_default_channel_layout(nChannelCount), AV_SAMPLE_FMT_S16, nSampleRate,	//输入格式
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

	AVFrame* ptAVFrame = av_frame_alloc();
	ptAVFrame->format = AV_SAMPLE_FMT_FLTP;
	ptAVFrame->channels = nChannelCount;
	ptAVFrame->channel_layout = av_get_default_channel_layout(nChannelCount);
	ptAVFrame->nb_samples = 1024;		//一帧音频一通道的采样数量

	nRtn = av_frame_get_buffer(ptAVFrame, 0);
	if (nRtn)
	{
		qDebug() << "av_frame_get_buffer failed";
		PrintErr(nRtn);
		return -2;
	}

	//一次读取一帧音频的字节数
	int nAudioFrameSize = ptAVFrame->nb_samples * nChannelCount * nSampleByte;		//一帧音频字节大小
	std::shared_ptr<char> chAudioBuf(new char[nAudioFrameSize] { 0 }, [&](char* p) {
		if (p)
		{
			delete[] p;
			p = nullptr;
		}
		});

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

	std::thread th([nAudioFrameSize, &chAudioBuf, &ptSwrContext, &ptAVFrame]() {
		for (;;)
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
				memcpy(g_tCollectAudioInfo.CollectAudioBuf, g_tCollectAudioInfo.CollectAudioBuf + nAudioFrameSize, g_tCollectAudioInfo.BufValidLen);
			}

			const uint8_t* uchInData[AV_NUM_DATA_POINTERS] = { nullptr };
			uchInData[0] = (const uint8_t*)chAudioBuf.get();

			//重采样这一帧源数据
			int nSwrConvertLen = swr_convert(ptSwrContext, 
				ptAVFrame->data, ptAVFrame->nb_samples,			//输出参数
				uchInData, ptAVFrame->nb_samples				//输入参数
			);
			std::cout << nSwrConvertLen << " ";
		}
		});

	/*if (pcAudioInput)
	{
		delete pcAudioInput;
		pcAudioInput = nullptr;
	}*/

	return app.exec();
}
