/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xformat.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.08.29
描  述: 封装、解封装基类
备  注:
修改记录:

  1.  日期: 2025.08.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <thread>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/codec.h>
}

#include "xformat.h"
#include "Debug.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avutil.lib")

CXFormat::~CXFormat()
{

}

static int Timerout_Callback(void* _pArg)
{
    CXFormat* pcXFormat = (CXFormat*)_pArg;

    if (pcXFormat->IsTimerout())
    {
        DEBUG(DEBUG_LEVEL_INFO, "Timerout_Callback is end");        //超时退出
        return 1;
    }

    //DEBUG(DEBUG_LEVEL_INFO, "Timerout_Callback is enter");

    return 0;  //正常阻塞
}

void CXFormat::SetTimeoutMs(int _Ms)
{
    std::unique_lock<std::mutex> lock(m_mut);

    m_nTimeroutMs = _Ms;

    if (m_ptAVFormatContext)            //设置超时回调函数
    {
        AVIOInterruptCB cb = { Timerout_Callback, this };
        m_ptAVFormatContext->interrupt_callback = cb;
    }

    m_bIsConnected = true;

    auto cNowTimePoint = std::chrono::high_resolution_clock::now();//转换为从Epoch开始的时长
    auto cDuration = cNowTimePoint.time_since_epoch();

    m_llLastMs = std::chrono::duration_cast<std::chrono::milliseconds>(cDuration).count();
}

bool CXFormat::IsTimerout(void)
{
    auto cNowTimePoint = std::chrono::high_resolution_clock::now();//转换为从Epoch开始的时长
    auto cDuration = cNowTimePoint.time_since_epoch();

    long long llNowMs = std::chrono::duration_cast<std::chrono::milliseconds>(cDuration).count();

    if (llNowMs - m_llLastMs > m_nTimeroutMs)
    {
        m_bIsConnected = false;             //超时就判定为断开连接

        return true;
    }

    return false;
}

void CXFormat::PrintErr(int _ErrCode)
{
    if (_ErrCode == 0)				//正确时，不打印错误信息
        return;

    char chBuf[1024] = { 0 };

    av_strerror(_ErrCode, chBuf, sizeof(chBuf) - 1);

    std::cerr << chBuf << std::endl;
}


