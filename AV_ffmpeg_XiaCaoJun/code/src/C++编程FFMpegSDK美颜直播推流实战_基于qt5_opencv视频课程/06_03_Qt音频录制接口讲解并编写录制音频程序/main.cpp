/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.02.24
描  述: Qt音频录制接口讲解并编写录制音频程序
备  注:
修改记录:

  1.  日期: 2026.02.24
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <QtCore/QCoreApplication>
#include <QAudioInput>
#include <QDebug>
#include <QTimer>

#include <iostream>

extern "C"
{
#include <libswresample/swresample.h>
#include <libavutil/avutil.h>
}

#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "avutil.lib")

//打印错误信息
static void PrintErr(int _ErrCode)
{
	if (_ErrCode == 0)				//正确时，不打印错误信息
		return;

	char chBuf[1024] = { 0 };

	av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

	std::cerr << chBuf << std::endl;
}

#include <QAudioDeviceInfo>
#include <QDebug>

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

	//音频重采样 上下文初始化
	SwrContext* ptSwrContext = nullptr;
	ptSwrContext = swr_alloc_set_opts(ptSwrContext,
		av_get_default_channel_layout(nChannelCount), AV_SAMPLE_FMT_FLTP, nSampleRate,	//输出格式
		av_get_default_channel_layout(nChannelCount), AV_SAMPLE_FMT_S16, nSampleRate,	//输入格式
		0, nullptr
	);
	if (!ptSwrContext)
	{
		qDebug() << "swr_alloc_set_opts is failed";
		return -2;
	}

	int nRtn = swr_init(ptSwrContext);
	if (nRtn)
	{
		qDebug() << "swr_init is failed";
		PrintErr(nRtn);
		return -2;
	}
	std::cout << "音频重采样 上下文初始化成功!" << std::endl;

	QObject::connect(pcIODevice, &QIODevice::readyRead, [pcIODevice]() {
		QByteArray data = pcIODevice->readAll();
		std::cout << data.size() << " ";
		});

	/*if (pcAudioInput)
	{
		delete pcAudioInput;
		pcAudioInput = nullptr;
	}*/

	return app.exec();
}
