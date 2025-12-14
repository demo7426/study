/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	xvideo_view.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.22
描  述: 实现一个抽象类，支持图像的渲染
备  注: 所有的接口均支持线程安全
修改记录:

  1.  日期: 2025.03.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <mutex>

#include "xvideo_view.h"
#include "xsdl.h"

using namespace std;

CXVideo_View::~CXVideo_View()
{
    if (m_pchCache)
    {
        delete[] m_pchCache;
        m_pchCache = nullptr;
    }
}

CXVideo_View* CXVideo_View::Create(RenderType _RenderType)
{
    if (_RenderType == RenderType::SDL)
        return new CXSDL();

    return nullptr;
}

bool CXVideo_View::DrawFrame(AVFrame* _pAVFrame)
{
    if(m_tBegClock <= 0)
        m_tBegClock = clock();
    else if (((clock() - m_tBegClock) / (CLOCKS_PER_SEC / 1000)) >= 1000)
    {
        m_unPerSecFPS = m_unFPSCounter;
        m_unFPSCounter = 0;

        m_tBegClock = clock();
    }

    m_unFPSCounter++;

    switch (_pAVFrame->format)
    {
    case AV_PIX_FMT_YUV420P:
        Draw((char*)_pAVFrame->data[0], _pAVFrame->linesize[0],
            (char*)_pAVFrame->data[1], _pAVFrame->linesize[1],
            (char*)_pAVFrame->data[2], _pAVFrame->linesize[2]
        );
        break;
    case AV_PIX_FMT_ARGB:
        Draw((char*)_pAVFrame->data[0], _pAVFrame->linesize[0]);
        break;
    case AV_PIX_FMT_NV12:
    {
        if (!m_pchCache)
            m_pchCache = new unsigned char[4096 * 2160 * 1.5];                                      //最大支持8k视频

        if (_pAVFrame->linesize[0] == _pAVFrame->width)
        {
            memcpy(m_pchCache, _pAVFrame->data[0], _pAVFrame->linesize[0] * _pAVFrame->height);     //Y
            memcpy(                                                                                 //U、V
                m_pchCache + _pAVFrame->linesize[0] * _pAVFrame->height,
                _pAVFrame->data[1], 
                _pAVFrame->linesize[1] * _pAVFrame->height / 2
            );
        }
        else    //逐行拷贝
        {
            for (int i = 0; i < _pAVFrame->height; i++)                                             //Y
                memcpy(m_pchCache + i * _pAVFrame->width, _pAVFrame->data[0] + i * _pAVFrame->linesize[0], _pAVFrame->width);

            for (int i = 0; i < _pAVFrame->height / 2; i++)                                         //U、V
            {
                auto pchTmp = m_pchCache + _pAVFrame->height * _pAVFrame->width;
                memcpy(pchTmp + i * _pAVFrame->width, _pAVFrame->data[1] + i * _pAVFrame->linesize[1], _pAVFrame->width);
            }
        }

        Draw((char*)m_pchCache, _pAVFrame->linesize[0]);
    }
        break;
    default:
        break;
    }

    return false;
}

bool CXVideo_View::SetScale(int _Width, int _Height)
{
    unique_lock<mutex> lock(m_mutex);

    m_nScale_Width = _Width;
    m_nScale_Height = _Height;

    return false;
}
