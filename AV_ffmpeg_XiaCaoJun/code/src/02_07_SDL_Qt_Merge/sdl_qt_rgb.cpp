/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.15
��  ��: ʹ��SDL��Qt�Ľ����Ϻϲ�����RGBͼ��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.03.15
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

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
    //��������ͼƬ�ܵĴ�С���������ڴ�ռ�
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

    //��ʼ��SDL video��
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        return;
    }

    //ָ��SDL����
    m_ptSDL_Window = SDL_CreateWindowFrom((void*)ui.label->winId());
    if (!m_ptSDL_Window)
    {
        return;
    }

    //������Ⱦ��,ʹ��Ӳ������
    m_ptSDL_Renderer = SDL_CreateRenderer(m_ptSDL_Window, -1, SDL_RENDERER_ACCELERATED);
    if (!m_ptSDL_Renderer)
    {
        return;
    }

    //���ɲ���
    m_ptSDL_Texture = SDL_CreateTexture(m_ptSDL_Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, m_nWidth, m_nHeight);
    if (!m_ptSDL_Texture)
    {
        return;
    }

    m_puchARGB = new quint8[m_nWidth * m_nHeight * m_nPixSize]{ 0 };

    //���ڴ��Ϻϲ�����ͼ������
    for (int i = 0; i < m_nHeight; i++)
    {
        int nRowPixelNum = i * m_nWidth * m_nPixSize;
        
        if (i < cImage01.height())
            memcpy(m_puchARGB + nRowPixelNum, cImage01.scanLine(i), cImage01.width() * m_nPixSize);

        nRowPixelNum += cImage01.width() * m_nPixSize;

        if (i < cImage02.height())
            memcpy(m_puchARGB + nRowPixelNum, cImage02.scanLine(i), cImage02.width() * m_nPixSize);
    }

    //�����ϲ����ͼ������
    QImage cImage_Merge(m_puchARGB, m_nWidth, m_nHeight, QImage::Format_ARGB32);        //QImage::Format_ARGB32 ��Ӧ��SDL��ʽΪ ARGB8888
    cImage_Merge.save("02_06_SDL_Qt_RGB_merge.png");

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchARGB, m_nWidth * m_nPixSize);

    //������Ļ
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    tSDL_Rect.x = 0;
    tSDL_Rect.y = 0;
    tSDL_Rect.w = m_nWidth;
    tSDL_Rect.h = m_nHeight;

    //���Ʋ��ʵ���Ⱦ
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, &tSDL_Rect);

    //��Ⱦ
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

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchARGB, m_nWidth * m_nPixSize);

    //������Ļ
    SDL_RenderClear(m_ptSDL_Renderer);

    SDL_Rect tSDL_Rect;
    tSDL_Rect.x = 0;
    tSDL_Rect.y = 0;
    tSDL_Rect.w = m_nWidth;
    tSDL_Rect.h = m_nHeight;

    //���Ʋ��ʵ���Ⱦ
    SDL_RenderCopy(m_ptSDL_Renderer, m_ptSDL_Texture, NULL, &tSDL_Rect);

    //��Ⱦ
    SDL_RenderPresent(m_ptSDL_Renderer);
}
