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

#include <iostream>
#include <mutex>

#include "xvideo_view.h"
#include "xsdl.h"

using namespace std;

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
    case AV_PIX_FMT_RGBA:
    case AV_PIX_FMT_ABGR:
    case AV_PIX_FMT_BGRA:
        Draw((char*)_pAVFrame->data[0], _pAVFrame->linesize[0]);
        break;
    default:
        break;
    }

    return false;
}

bool CXVideo_View::OpenFile(const char* _pFilePath)
{
    if(m_cIfstream.is_open())
        m_cIfstream.close();

    m_cIfstream.open(_pFilePath, std::ios::binary);
    if (!m_cIfstream.is_open())
    {
        return false;
    }

    if (m_ptAVFrame && av_buffer_get_ref_count(m_ptAVFrame->buf[0]) > 1)        //多次打开新的文件时，释放内存资源，防止内存泄露
    {
        av_frame_free(&m_ptAVFrame);
        m_ptAVFrame = nullptr;
    }

    m_ptAVFrame = av_frame_alloc();                                             //为了兼容不同格式的文件，重新分配

    switch (m_eFmt)
    {
    case CXVideo_View::Format::ARGB:
    case CXVideo_View::Format::RGBA:
    case CXVideo_View::Format::ABGR:
    case CXVideo_View::Format::BGRA:
    {
        if (m_eFmt == CXVideo_View::Format::ARGB)
            m_ptAVFrame->format = AV_PIX_FMT_ARGB;
        else if (m_eFmt == CXVideo_View::Format::RGBA)
            m_ptAVFrame->format = AV_PIX_FMT_RGBA;
        else if (m_eFmt == CXVideo_View::Format::ABGR)
            m_ptAVFrame->format = AV_PIX_FMT_ABGR;
        else if (m_eFmt == CXVideo_View::Format::BGRA)
            m_ptAVFrame->format = AV_PIX_FMT_BGRA;

        m_ptAVFrame->width = m_nWidth;
        m_ptAVFrame->height = m_nHeight;
        m_ptAVFrame->linesize[0] = m_nWidth * 4;
    }
    break;
    case CXVideo_View::Format::YUV420P:
    {
        m_ptAVFrame->width = m_nWidth;
        m_ptAVFrame->height = m_nHeight;
        m_ptAVFrame->format = AV_PIX_FMT_YUV420P;
        m_ptAVFrame->linesize[0] = m_nWidth;
        m_ptAVFrame->linesize[1] = m_nWidth / 2;
        m_ptAVFrame->linesize[2] = m_nWidth / 2;
    }
    break;
    default:
        return false;
    }

    int nRet = av_frame_get_buffer(m_ptAVFrame, 0);
    if (nRet)
    {
        char chBuf[1024] = { 0 };
        av_strerror(nRet, chBuf, sizeof(chBuf) - 1);
        std::cout << chBuf << std::endl;
        return false;
    }

    return true;
}

AVFrame* CXVideo_View::GetFileAVFrame(void)
{
    if (!m_cIfstream.is_open())
    {
        return nullptr;
    }

    switch (m_eFmt)
    {
    case CXVideo_View::Format::ARGB:
    case CXVideo_View::Format::RGBA:
    case CXVideo_View::Format::ABGR:
    case CXVideo_View::Format::BGRA:
    {
        m_cIfstream.read((char*)m_ptAVFrame->data[0], (streamsize)m_nWidth * m_nHeight * 4);
    }
    break;
    case CXVideo_View::Format::YUV420P:
    {
        m_cIfstream.read((char*)m_ptAVFrame->data[0], (streamsize)m_nWidth * m_nHeight);
        m_cIfstream.read((char*)m_ptAVFrame->data[1], (streamsize)m_nWidth * m_nHeight / 4);
        m_cIfstream.read((char*)m_ptAVFrame->data[2], (streamsize)m_nWidth * m_nHeight / 4);
    }
    break;
    default:
        return nullptr;
    }

    if (m_cIfstream.gcount() == 0)     //循环播放数据;当m_pcIfstream读取到eof时，seekg无法回到文件开头，故采用此方法
    {
        m_cIfstream.clear();
        m_cIfstream.seekg(0, std::ios::beg);
    }

    return m_ptAVFrame;
}

bool CXVideo_View::SetScale(int _Width, int _Height)
{
    unique_lock<mutex> lock(m_mutex);

    m_nScale_Width = _Width;
    m_nScale_Height = _Height;

    return false;
}
