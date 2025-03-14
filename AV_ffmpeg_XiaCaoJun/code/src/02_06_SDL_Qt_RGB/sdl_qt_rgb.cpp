/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.14
��  ��: ʹ��SDL��Qt�Ľ�������ȾRGBͼ��
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.03.14
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

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

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, puchARGB, m_nWidth * m_nPixSize);

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

    //������ѭ������
    m_nReversal == 0 ? m_uchRedValue-- : m_uchRedValue++;
    if (m_uchRedValue == 0 || m_uchRedValue == 255)
    {
        m_nReversal = (m_nReversal == 0 ? 1 : 0);
    }

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, puchARGB, m_nWidth * m_nPixSize);

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
