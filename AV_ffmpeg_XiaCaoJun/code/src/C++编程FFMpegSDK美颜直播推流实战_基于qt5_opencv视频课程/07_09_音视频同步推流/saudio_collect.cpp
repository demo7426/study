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

extern "C"
{
#include "libavutil/time.h"
}


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

		auto llTimeStamp = av_gettime_relative();					//当前时间戳

		std::lock_guard<std::mutex> lock(m_cMutCollectAudioBuf);

		m_cDeqCollectAudioInfo.push_back(COLLECT_AUDIO_INFO());

		m_cDeqCollectAudioInfo.back().Data.assign(cByteArray.data(), cByteArray.data() + cByteArray.size());		//防止出现多次拷贝数据的情况
		m_cDeqCollectAudioInfo.back().StartIndex = 0;
		m_cDeqCollectAudioInfo.back().Pts = llTimeStamp;

		m_nDeqCollectAudioInfo_Sum += cByteArray.size();

		if (sizeof m_cDeqCollectAudioInfo.size() > m_nMaxDeqSize)
		{
			qDebug() << __func__ << "Audio buffer overflow!!!";
			//return;
		}
		});

	return m_pcCoreApplication->exec();
}

int CSAudio_Collect_Qt::GetData(char* _pBuf, int _BufSize, int64_t& _TimeStamp)
{
	if (!_pBuf || _BufSize <= 0)
	{
		qDebug() << __func__ << ", input parameter is err.";
		return -1;
	}

	int nMemBufSize = 0;			//已经完成拷贝的数据大小
	COLLECT_AUDIO_INFO tCollectAudioInfo;

	std::lock_guard<std::mutex> lock(m_cMutCollectAudioBuf);

	if(m_cDeqCollectAudioInfo.empty() || m_nDeqCollectAudioInfo_Sum < _BufSize)		//缓冲区数据不足，不可以取出当前数据
	{
		//qDebug() << __func__ << ", not exist audio data.";
		return -3;
	}

	while (nMemBufSize < _BufSize)
	{
		tCollectAudioInfo = m_cDeqCollectAudioInfo.front();

		if (tCollectAudioInfo.Data.size() - tCollectAudioInfo.StartIndex >= _BufSize - nMemBufSize)		//一帧数据即够用
		{
			memcpy(_pBuf, tCollectAudioInfo.Data.data() + tCollectAudioInfo.StartIndex, _BufSize - nMemBufSize);//取出一帧音频数据

			auto nDiff = _BufSize - nMemBufSize;

			nMemBufSize += nDiff;

			m_cDeqCollectAudioInfo[0].StartIndex += nDiff;

			m_nDeqCollectAudioInfo_Sum -= nDiff;
		}
		else  //当前缓冲数据不够一帧，需要继续取出下一帧的缓冲
		{
			memcpy(_pBuf, tCollectAudioInfo.Data.data() + tCollectAudioInfo.StartIndex, tCollectAudioInfo.Data.size() - tCollectAudioInfo.StartIndex);

			auto nDiff = tCollectAudioInfo.Data.size() - tCollectAudioInfo.StartIndex;

			nMemBufSize += nDiff;

			m_cDeqCollectAudioInfo[0].StartIndex = tCollectAudioInfo.Data.size();

			m_nDeqCollectAudioInfo_Sum -= nDiff;
		}

		if (tCollectAudioInfo.StartIndex == tCollectAudioInfo.Data.size())								
			m_cDeqCollectAudioInfo.pop_front();															//当前缓冲数据全部被取走了
	}

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
