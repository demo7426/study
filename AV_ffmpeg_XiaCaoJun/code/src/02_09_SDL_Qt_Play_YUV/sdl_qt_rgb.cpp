/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.16
描  述: 使用SDL在Qt的界面上播放YUV视频文件
备  注: 
修改记录:

  1.  日期: 2025.03.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <memory>
#include <qimage.h>
#include <qmessagebox.h>

#include "sdl_qt_rgb.h"

using namespace std;

SDL_Qt_RGB::SDL_Qt_RGB(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    InitUi();
}

SDL_Qt_RGB::~SDL_Qt_RGB()
{
    if (m_pcIfstream.is_open())
        m_pcIfstream.close();

    if (m_puchYUV)
    {
        delete[] m_puchYUV;
        m_puchYUV = nullptr;
    }
}

void SDL_Qt_RGB::InitUi(void)
{
    m_pcIfstream.open("../../src/02_09_SDL_Qt_Play_YUV/1.yuv", std::ios::binary);
    if (!m_pcIfstream.is_open())
    {
        QMessageBox::warning(this, tr("警告"), tr("打开文件失败"));
        exit(0);
    }
    
    this->resize(m_nWidth, m_nHeight);
    ui.label->resize(m_nWidth, m_nHeight);

    //初始化SDL video库
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        return;
    }

    //指定SDL窗口
    m_ptSDL_Window = SDL_CreateWindowFrom((void*)ui.label->winId());
    if (!m_ptSDL_Window)
    {
        return;
    }

    //生成渲染器,使用硬件加速
    m_ptSDL_Renderer = SDL_CreateRenderer(m_ptSDL_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_ptSDL_Renderer)
    {
        return;
    }

    //生成材质
    m_ptSDL_Texture = SDL_CreateTexture(m_ptSDL_Renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_nWidth, m_nHeight);
    if (!m_ptSDL_Texture)
    {
        return;
    }

    m_puchYUV = new quint8[m_nWidth * m_nHeight * m_nPixSize]{ 0 };

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchYUV, m_nWidth);

    //清理屏幕
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    tSDL_Rect.x = 0;
    tSDL_Rect.y = 0;
    tSDL_Rect.w = m_nWidth;
    tSDL_Rect.h = m_nHeight;

    //复制材质到渲染
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, &tSDL_Rect);

    //渲染
    SDL_RenderPresent(m_ptSDL_Renderer);

    this->startTimer(10);
}

void SDL_Qt_RGB::timerEvent(QTimerEvent* e)
{
    m_pcIfstream.read(reinterpret_cast<char*>(m_puchYUV), (streamsize)m_nWidth * m_nHeight * 1.5);

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchYUV, m_nWidth);

    //清理屏幕
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    tSDL_Rect.x = 0;
    tSDL_Rect.y = 0;
    tSDL_Rect.w = m_nWidth;
    tSDL_Rect.h = m_nHeight;

    //复制材质到渲染
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, &tSDL_Rect);

    //渲染
    SDL_RenderPresent(m_ptSDL_Renderer);
}
