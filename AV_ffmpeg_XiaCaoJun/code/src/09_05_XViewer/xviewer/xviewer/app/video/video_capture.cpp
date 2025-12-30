/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	video_capture.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.18
描  述:	实现音视频数据的采集
备  注:
修改记录:

  1.  日期: 2025.12.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QElapsedTimer>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <string>

#include "video_capture.h"

#include "xthread.h"
#include "Debug.h"

#define USER_EXIT_FAILURE           -2                      //执行失败
#define USER_INPUT_PARAMETER_ERR    -1                      //传入参数错误
#define USER_EXIT_SUCCESS           0                       //执行成功

CVideo_Capture::CVideo_Capture(QObject *parent)
    : QThread{parent}
{
    
}

int CVideo_Capture::StartThread(QString _URL, QString _StoreDir, bool _IsSave, void* _pWinID) noexcept
{
	if (_URL.isEmpty())
	{
		DEBUG(DEBUG_LEVEL_WARN, "StartThread input param is err");
		return USER_INPUT_PARAMETER_ERR; // 防止重复启动
	}

    {
        QMutexLocker locker(&m_mut); // 加锁保护线程运行标志
        if (m_bIsRun) {
            return USER_EXIT_FAILURE; // 防止重复启动
        }

        m_bIsRun = true;
    }

	m_strURL = _URL;
	m_strStoreDir = _StoreDir;
	m_bIsSave = _IsSave;
	m_pvWinID = _pWinID;

    this->start();

    return USER_EXIT_SUCCESS;
}

void CVideo_Capture::StopThread() noexcept
{
    {
        QMutexLocker locker(&m_mut);
        m_bIsRun = false;
    }

	m_cDemux_Task.Stop();
	m_cDecode_Task.Stop();

	this->wait();

	m_pvWinID = nullptr;
}

int CVideo_Capture::GetVideoInfo(QString _URL, CVideo_Capture::PAVIDEO_INFO _ptVideo_Info)
{
	int nRtn = 0;
	struct AVFormatContext* ptAVFormatContext = nullptr;

	nRtn = m_cXDemux.Create_AVFormatContext(_URL.toStdString().c_str());
	if (nRtn)
	{
		DEBUG(DEBUG_LEVEL_ERROR, "%s, 不存在", _URL.toStdString().c_str());
		return USER_EXIT_FAILURE;
	}

	ptAVFormatContext = m_cXDemux.GetAVFormatContext();
	if (!ptAVFormatContext)
	{
		m_cXDemux.Close();
		DEBUG(DEBUG_LEVEL_ERROR, "GetAVFormatContext is err");
		return USER_EXIT_FAILURE;
	}
	
	_ptVideo_Info->Width = ptAVFormatContext->streams[0]->codecpar->width;
	_ptVideo_Info->Height = ptAVFormatContext->streams[0]->codecpar->height;
	_ptVideo_Info->FrameRate = ptAVFormatContext->streams[0]->avg_frame_rate.num / ptAVFormatContext->streams[0]->avg_frame_rate.den;
	_ptVideo_Info->Duration = ptAVFormatContext->duration / AV_TIME_BASE;
	_ptVideo_Info->Video_CodeID = ptAVFormatContext->streams[0]->codecpar->codec_id;
	_ptVideo_Info->PixFmt = ptAVFormatContext->streams[0]->codecpar->format;
	
	m_cXDemux.Close();

	return USER_EXIT_SUCCESS;
}

void CVideo_Capture::run()
{
	//const char* pchURL = "rtsp://127.0.0.1:8554/test";						//媒体文件
	//const char* pchURL = "4K故宫紫禁城建筑宫殿古城皇宫城楼北京城日出日落高清视频素材_爱给网_aigei_com.mp4";						//媒体文件
	//const char* pchURL = "剑士4k超高清_爱给网_aigei_com.mp4";						//媒体文件
	//const char* pchURL = "1.mp4";						//媒体文件
	//const char* pchURL = "rtsp://admin:qr13419484865.@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0";						//大华相机
	auto strURL = m_strURL.toStdString();				//源流
	std::string strStoreFilePath = "";		//存储路径
	const char* pchURL = strURL.c_str();

	CXVideo_View* pcXVideo_View = nullptr;
	bool bInitFlag = false;
	AVFrame* ptAVFrame = nullptr;
	CXVideo_View::Format eFmt = CXVideo_View::Format::YUV420P;

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	if(!m_strStoreDir.isEmpty())
		strStoreFilePath = m_strStoreDir.toStdString() + "/" + GetLocalTime() + ".mp4";
	else
		strStoreFilePath = GetLocalTime() + ".mp4";

	while (m_cDemux_Task.Open(pchURL, 1000) != 0)
	{
		DEBUG(DEBUG_LEVEL_INFO, "重新连接:%s", pchURL);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	pcXVideo_View = CXVideo_View::Create();

	m_cDemux_Task.SetNext(&m_cDecode_Task);
	if(m_bIsSave)
		m_cDemux_Task.SetXEncode_XMux(&m_cXEncode, &m_cXMux, strStoreFilePath);

	m_cDemux_Task.Start();
	m_cDecode_Task.Start();

	while (1)
	{
		{
			QMutexLocker locker(&m_mut);
			if (m_bIsRun == false)
				break;
		}

		ptAVFrame = m_cDecode_Task.GetCurAVFrame();

		if (!ptAVFrame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			continue;
		}

		if (!bInitFlag)
		{
			switch (ptAVFrame->format)
			{
			case AVPixelFormat::AV_PIX_FMT_RGBA:
				eFmt = CXVideo_View::Format::RGBA;
				break;
			case AVPixelFormat::AV_PIX_FMT_ARGB:
				eFmt = CXVideo_View::Format::ARGB;
				break;
			case AVPixelFormat::AV_PIX_FMT_YUV420P:
			case AVPixelFormat::AV_PIX_FMT_YUVJ420P:
				eFmt = CXVideo_View::Format::YUV420P;
				break;
			case AVPixelFormat::AV_PIX_FMT_NV12:
				eFmt = CXVideo_View::Format::NV12;
				break;
			default:
				break;
			}

			pcXVideo_View->Init(ptAVFrame->width, ptAVFrame->height, eFmt, m_pvWinID);
			bInitFlag = true;
		}

		pcXVideo_View->DrawFrame(ptAVFrame);
		nFrameCounter++;

		av_frame_unref(ptAVFrame);

		cEnd_TimePoint = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::milliseconds>(cEnd_TimePoint - cStart_TimePoint).count() >= 1000)
		{
			std::cout << "Frames per second:" << nFrameCounter << std::endl;

			nFrameCounter = 0;
			cStart_TimePoint = cEnd_TimePoint;
		}
	}

    //QThread::msleep(20);
    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
    
}

std::string CVideo_Capture::GetLocalTime(void)
{
	// 获取当前时间戳
	std::time_t now = std::time(nullptr);

	// 转换为本地时间
	std::tm* localTime = std::localtime(&now);
	std::chrono::system_clock::time_point cSystem_ClockNow = std::chrono::system_clock::now();
	auto cSystemSuration = std::chrono::duration_cast<std::chrono::nanoseconds>(cSystem_ClockNow.time_since_epoch());

	// 使用stringstream格式化输出
	std::stringstream ss;
	ss << std::put_time(localTime, "%Y_%m_%d %H_%M_%S");

	//获取当前的时间戳，精确到ns级别
	ss << " " << std::to_string(cSystemSuration.count());

	ss << " " << std::this_thread::get_id();												//使用线程id命名文件，防止多个线程同一时间抢占到同一个文件名

	return ss.str();
}


