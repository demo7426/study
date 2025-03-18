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
#include <qscreen.h>
#include <qrect.h>

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

    if (m_pcXVideo_View)
    {
        delete m_pcXVideo_View;
        m_pcXVideo_View = nullptr;
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
    ui.label->move(0, 0);

    QScreen* screen = QGuiApplication::primaryScreen();

    m_puchYUV = new char[screen->geometry().width() * screen->geometry().height() * m_nPixSize]{ 0 };

    m_pcXVideo_View = CXVideo_View::Create();
    m_pcXVideo_View->Init(m_nWidth, m_nHeight, CXVideo_View::Format::YUV420P, (void*)ui.label->winId());
    //m_pcXVideo_View->Init(m_nWidth, m_nHeight, CXVideo_View::Format::YUV420P, nullptr);
    m_pcXVideo_View->Draw(m_puchYUV);

    this->startTimer(10);
}

void SDL_Qt_RGB::timerEvent(QTimerEvent* e)
{
    if (m_pcXVideo_View->IsExit())
    {
        m_pcXVideo_View->Close();
        exit(0);
    }

    m_pcIfstream.read(reinterpret_cast<char*>(m_puchYUV), (streamsize)m_nWidth * m_nHeight * 1.5);

    m_pcXVideo_View->Draw(m_puchYUV);
}

void SDL_Qt_RGB::resizeEvent(QResizeEvent* event)
{
    ui.label->resize(this->size());
    ui.label->move(0, 0);

    m_pcXVideo_View->SetScale(this->size().width(), this->size().height());
}
