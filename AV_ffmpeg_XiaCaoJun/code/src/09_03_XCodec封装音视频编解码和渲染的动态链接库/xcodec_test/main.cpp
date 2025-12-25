/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	main.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.12.25
描  述: 实现对xcodec动态链接库的测试
备  注:
修改记录:

  1.  日期: 2025.08.27
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本;
	  版本:V0.1.0

*************************************************/

#include <iostream>

#include "xencode.h"
#include "xdecode.h"
#include "xvideo_view.h"
#include "xdemux.h"
#include "xmux.h"
#include "xthread.h"
#include "Debug.h"

#include "xdemux_task.h"
#include "xdecode_task.h"

#pragma comment(lib, "xcodec.lib")

int main()
{
	const char* pchURL = "rtsp://127.0.0.1:8554/test";						//媒体文件
	//const char* pchURL = "4K故宫紫禁城建筑宫殿古城皇宫城楼北京城日出日落高清视频素材_爱给网_aigei_com.mp4";						//媒体文件
	//const char* pchURL = "剑士4k超高清_爱给网_aigei_com.mp4";						//媒体文件
	//const char* pchURL = "1.mp4";						//媒体文件
	//const char* pchURL = "rtsp://admin:qr13419484865.@192.168.1.108:554/cam/realmonitor?channel=1&subtype=0";						//大华相机
	CXDemux_Task cDemux_Task;
	CXDecode_Task cDecode_Task;
	CXEncode cXEncode;
	CXMux cXMux;

	CXVideo_View* pcXVideo_View = nullptr;
	bool bInitFlag = false;
	AVFrame* ptAVFrame = nullptr;
	CXVideo_View::Format eFmt = CXVideo_View::Format::YUV420P;

	// 记录开始时间点
	auto cStart_TimePoint = std::chrono::high_resolution_clock::now();
	auto cEnd_TimePoint = cStart_TimePoint;

	int nFrameCounter = 0;					//帧数计数

	while (cDemux_Task.Open(pchURL, 1000) != 0)
	{
		DEBUG(DEBUG_LEVEL_INFO, "重新连接:%s", pchURL);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	pcXVideo_View = CXVideo_View::Create();

	cDemux_Task.SetNext(&cDecode_Task);
	cDemux_Task.SetXEncode_XMux(&cXEncode, &cXMux);

	cDemux_Task.Start();
	cDecode_Task.Start();

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	cDemux_Task.Stop();
	cDecode_Task.Stop();

	return 0;
}
