/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	sdl_qt_rgb.cpp
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2025.03.16
��  ��: ʹ��SDL��Qt�Ľ����ϲ���YUV��Ƶ�ļ�
��  ע: 
�޸ļ�¼:

  1.  ����: 2025.03.16
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
        QMessageBox::warning(this, tr("����"), tr("���ļ�ʧ��"));
        exit(0);
    }
    
    this->resize(m_nWidth, m_nHeight);
    ui.label->resize(m_nWidth, m_nHeight);

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
    m_ptSDL_Texture = SDL_CreateTexture(m_ptSDL_Renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, m_nWidth, m_nHeight);
    if (!m_ptSDL_Texture)
    {
        return;
    }

    m_puchYUV = new quint8[m_nWidth * m_nHeight * m_nPixSize]{ 0 };

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchYUV, m_nWidth);

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
    m_pcIfstream.read(reinterpret_cast<char*>(m_puchYUV), (streamsize)m_nWidth * m_nHeight * 1.5);

    //��ͼ������д�����
    SDL_UpdateTexture(m_ptSDL_Texture, NULL, m_puchYUV, m_nWidth);

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
