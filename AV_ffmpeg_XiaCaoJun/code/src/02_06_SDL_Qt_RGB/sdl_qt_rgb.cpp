/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.14
描  述: 使用SDL在Qt的界面上渲染RGB图像
备  注: 
修改记录:

  1.  日期: 2025.03.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <memory>

#include "sdl_qt_rgb.h"

using namespace std;

SDL_Qt_RGB::SDL_Qt_RGB(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    InitUi();
}

SDL_Qt_RGB::~SDL_Qt_RGB()
{}

void SDL_Qt_RGB::InitUi(void)
{
    m_nWidth = ui.label->width();
    m_nHeight = ui.label->height();

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
    m_ptSDL_Texture = SDL_CreateTexture(m_ptSDL_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_nWidth, m_nHeight);
    if (!m_ptSDL_Texture)
    {
        return;
    }

    shared_ptr<unsigned char> pspARGB(new unsigned char[m_nWidth * m_nHeight * m_nPixSize]);
    auto puchARGB = pspARGB.get();

    for (int i = 0; i < m_nHeight; i++)
    {
        int nRowNum = i * m_nWidth * m_nPixSize;
        for (int j = 0; j < m_nWidth * m_nPixSize; j += m_nPixSize)
        {
            puchARGB[nRowNum + j] = 0;                      //B
            puchARGB[nRowNum + j + 1] = 0;                  //G
            puchARGB[nRowNum + j + 2] = m_uchRedValue;      //R
            puchARGB[nRowNum + j + 3] = 0;                  //A
        }
    }

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, puchARGB, m_nWidth * m_nPixSize);

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
    shared_ptr<unsigned char> pspARGB(new unsigned char[m_nWidth * m_nHeight * m_nPixSize]);
    auto puchARGB = pspARGB.get();

    for (int i = 0; i < m_nHeight; i++)
    {
        int nRowNum = i * m_nWidth * m_nPixSize;
        for (int j = 0; j < m_nWidth * m_nPixSize; j += m_nPixSize)
        {
            puchARGB[nRowNum + j] = 0;                      //B
            puchARGB[nRowNum + j + 1] = 0;                  //G
            puchARGB[nRowNum + j + 2] = m_uchRedValue;      //R
            puchARGB[nRowNum + j + 3] = 0;                  //A
        }
    }

    //让数据循环起来
    m_nReversal == 0 ? m_uchRedValue-- : m_uchRedValue++;
    if (m_uchRedValue == 0 || m_uchRedValue == 255)
    {
        m_nReversal = (m_nReversal == 0 ? 1 : 0);
    }

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, puchARGB, m_nWidth * m_nPixSize);

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
