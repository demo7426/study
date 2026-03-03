/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	saudio_collect.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.03.03
描  述: 实现音频的数据采集
备  注:
修改记录:

  1.  日期: 2026.03.03
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <QtCore/QCoreApplication>
#include <QAudioInput>
#include <QDebug>

#include "saudio_collect.h"

CSAudio_Collect::~CSAudio_Collect() {}

CSAudio_Collect_Qt::CSAudio_Collect_Qt(int argc, char* argv[])
{
	m_pcCoreApplication = new QCoreApplication(argc, argv);
}

CSAudio_Collect_Qt::~CSAudio_Collect_Qt()
{
	this->Stop();

	if (m_pcCoreApplication)
	{
		delete m_pcCoreApplication;
		m_pcCoreApplication = nullptr;
	}
}

int CSAudio_Collect_Qt::Init(int _SampleRate, int _Channels, int _SampleByte)
{
	//qt音频录制
	QAudioFormat cAudioFmt;
	cAudioFmt.setSampleRate(_SampleRate);
	cAudioFmt.setChannelCount(_Channels);
	cAudioFmt.setSampleSize(_SampleByte * 8);
	cAudioFmt.setCodec("audio/pcm");
	cAudioFmt.setByteOrder(QAudioFormat::LittleEndian);
	cAudioFmt.setSampleType(QAudioFormat::SignedInt);
	QAudioDeviceInfo cAudioDeviceInfo = QAudioDeviceInfo::defaultInputDevice();
	if (!cAudioDeviceInfo.isFormatSupported(cAudioFmt))
	{
		qDebug() << __func__ << "Audio format not support!";
		return -2;
	}

	m_pcAudioInput = new QAudioInput(cAudioFmt); 

	return 0;
}

int CSAudio_Collect_Qt::Start()
{
	//开始录制音频	
	m_pcIODevice = m_pcAudioInput->start();
	if (!m_pcIODevice)
	{
		qDebug() << __func__ << "AudioInput start failed";
		return -2;
	}

	QObject::connect(m_pcIODevice, &QIODevice::readyRead, [&]() {
		QByteArray cByteArray = m_pcIODevice->readAll();
		//std::cout << cByteArray.size() << " ";

		std::lock_guard<std::mutex> lock(m_tCollectAudioInfo.MutCollectAudioBuf);

		if (sizeof m_tCollectAudioInfo.CollectAudioBuf - m_tCollectAudioInfo.BufValidLen < cByteArray.size())
		{
			qDebug() << __func__ << "Audio buffer overflow!!!";
			return;
		}

		memcpy(m_tCollectAudioInfo.CollectAudioBuf + m_tCollectAudioInfo.BufValidLen, cByteArray.data(), cByteArray.size());
		m_tCollectAudioInfo.BufValidLen += cByteArray.size();
		});

	return m_pcCoreApplication->exec();
}

int CSAudio_Collect_Qt::GetData(char* _pBuf, int _BufSize)
{
	if (!_pBuf || _BufSize <= 0)
	{
		qDebug() << __func__ << ", input parameter is err.";
		return -1;
	}

	std::lock_guard<std::mutex> lock(m_tCollectAudioInfo.MutCollectAudioBuf);
	if (m_tCollectAudioInfo.BufValidLen < _BufSize)
	{
		return -3;
	}

	//std::cout << g_tCollectAudioInfo.BufValidLen << " ";
	memcpy(_pBuf, m_tCollectAudioInfo.CollectAudioBuf, _BufSize);			//取出一帧音频数据

	//重新计算并且移动缓冲区数据
	m_tCollectAudioInfo.BufValidLen -= _BufSize;
	memmove(m_tCollectAudioInfo.CollectAudioBuf, m_tCollectAudioInfo.CollectAudioBuf + _BufSize, m_tCollectAudioInfo.BufValidLen);

	return 0;
}

int CSAudio_Collect_Qt::Stop()
{
	//先停止音频输入（QAudioInput会自动处理内部的QIODevice）
	if(m_pcAudioInput)
		m_pcAudioInput->stop();		//停止后，内部的QIODevice会被关闭/清理

	if (m_pcIODevice)
	{
		QObject::disconnect(m_pcIODevice, &QIODevice::readyRead, nullptr, nullptr);
		m_pcIODevice = nullptr;		//置空即可，不需要delete
	}

	if (m_pcAudioInput)
	{
		delete m_pcAudioInput;
		m_pcAudioInput = nullptr;
	}

	return 0;
}
