/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.15
描  述: 使用SDL在Qt的界面上合并两幅RGB图像
备  注: 
修改记录:

  1.  日期: 2025.03.15
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
    if (m_puchARGB)
    {
        delete[] m_puchARGB;
        m_puchARGB = nullptr;
    }
}

void SDL_Qt_RGB::InitUi(void)
{
    //计算两幅图片总的大小，并开辟内存空间
    QImage cImage01("../../src//02_07_SDL_Qt_Merge//IMG_202503158658_800x429.png");
    QImage cImage02("../../src//02_07_SDL_Qt_Merge//IMG_202503159124_600x322.png");

    if (cImage01.isNull() || cImage02.isNull())
    {
        QMessageBox::warning(this, tr("warning"), tr("Load image is err."));
        exit(0);
    }

    m_nWidth = cImage01.width() + cImage02.width();
    m_nHeight = cImage01.height() > cImage02.height()? cImage01.height(): cImage02.height();

    this->resize(m_nWidth, m_nHeight);
    ui.label->resize(m_nWidth, m_nHeight);
    
    this->setFixedSize(this->width(), this->height());

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

    m_puchARGB = new quint8[m_nWidth * m_nHeight * m_nPixSize]{ 0 };

    //从内存上合并两幅图像数据
    for (int i = 0; i < m_nHeight; i++)
    {
        int nRowPixelNum = i * m_nWidth * m_nPixSize;
        
        if (i < cImage01.height())
            memcpy(m_puchARGB + nRowPixelNum, cImage01.scanLine(i), cImage01.width() * m_nPixSize);

        nRowPixelNum += cImage01.width() * m_nPixSize;

        if (i < cImage02.height())
            memcpy(m_puchARGB + nRowPixelNum, cImage02.scanLine(i), cImage02.width() * m_nPixSize);
    }

    //导出合并后的图像数据
    QImage cImage_Merge(m_puchARGB, m_nWidth, m_nHeight, QImage::Format_ARGB32);        //QImage::Format_ARGB32 对应的SDL格式为 ARGB8888
    cImage_Merge.save("02_06_SDL_Qt_RGB_merge.png");

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchARGB, m_nWidth * m_nPixSize);

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
    //for (int i = 0; i < m_nHeight; i++)
    //{
    //    int nRowNum = i * m_nWidth * m_nPixSize;
    //    for (int j = 0; j < m_nWidth * m_nPixSize; j += m_nPixSize)
    //    {
    //        m_puchARGB[nRowNum + j] = 0;                      //B
    //        m_puchARGB[nRowNum + j + 1] = 0;                  //G
    //        m_puchARGB[nRowNum + j + 2] = 255;      //R
    //        m_puchARGB[nRowNum + j + 3] = 0;                  //A
    //    }
    //}

    //将图像数据写入材质
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchARGB, m_nWidth * m_nPixSize);

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
