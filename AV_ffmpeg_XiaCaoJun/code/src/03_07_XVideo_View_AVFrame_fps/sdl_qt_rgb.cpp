/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.25
描  述: 使用SDL在Qt的界面上,播放AVFrame的YUV视频文件，并且控制帧率
备  注: 
修改记录:

  1.  日期: 2025.03.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#include <iostream>
#include <memory>
#include <qimage.h>
#include <qmessagebox.h>
#include <qscreen.h>
#include <qrect.h>
#include <qdebug.h>
#include <qfile.h>

#include "sdl_qt_rgb.h"

using namespace std;

/// <summary>
/// 高精度延时函数
/// </summary>
/// <param name="_Ms">毫秒</param>
static void MSleep(int _Ms)
{
    clock_t tClock_Beg = clock();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::microseconds(1));

        if (((clock() - tClock_Beg) / (CLOCKS_PER_SEC / 1000)) >= _Ms)
        {
            break;
        }
    }
}

SDL_Qt_RGB::SDL_Qt_RGB(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    InitUi();
    InitSignalSlots();
}

SDL_Qt_RGB::~SDL_Qt_RGB()
{
    if (m_pcIfstream.is_open())
        m_pcIfstream.close();

    if (m_ptAVFrame)
    {
        av_frame_free(&m_ptAVFrame);
        m_ptAVFrame = nullptr;
    }

    if (m_pcXVideo_View)
    {
        delete m_pcXVideo_View;
        m_pcXVideo_View = nullptr;
    }

    m_bIsQuitThread = true;         //保证线程退出，资源正常释放
    m_cTh01.join();
}

void SDL_Qt_RGB::InitUi(void)
{
    qint32 nRet = 0;
    QFile cFile(m_pchFilePath);

    m_ullFilePathSize = cFile.size();

    m_pcIfstream.open(m_pchFilePath, std::ios::binary);
    if (!m_pcIfstream.is_open())
    {
        QMessageBox::warning(this, tr("警告"), tr("打开文件失败"));
        exit(0);
    }
    
    this->resize(m_nWidth, m_nHeight);
    ui.label->resize(m_nWidth, m_nHeight);
    ui.label->move(0, 0);

    QScreen* screen = QGuiApplication::primaryScreen();

    m_ptAVFrame = av_frame_alloc();

    m_ptAVFrame->width = m_nWidth;
    m_ptAVFrame->height = m_nHeight;
    m_ptAVFrame->format = AV_PIX_FMT_YUV420P;
    m_ptAVFrame->linesize[0] = m_nWidth;
    m_ptAVFrame->linesize[1] = m_nWidth / 2;
    m_ptAVFrame->linesize[2] = m_nWidth / 2;

    nRet = av_frame_get_buffer(m_ptAVFrame, 0);
    if (nRet)
    {
        char chBuf[1024] = { 0 };
        av_strerror(nRet, chBuf, sizeof(chBuf) - 1);
        qDebug() << chBuf;
    }

    m_pcXVideo_View = CXVideo_View::Create();
    m_pcXVideo_View->Init(m_nWidth, m_nHeight, CXVideo_View::Format::YUV420P, (void*)ui.label->winId());
    //m_pcXVideo_View->Init(m_nWidth, m_nHeight, CXVideo_View::Format::YUV420P, nullptr);
 
    //this->startTimer(40);

    m_pcLabel = new QLabel(this);
    m_pcLabel->move(0, 0);

    m_pcLabel->setText(QString::asprintf("fps:%d", m_pcXVideo_View->GetPerSecFPS()));
    m_pcLabel->adjustSize();

    m_pcSpinBox = new QSpinBox(this);
    m_pcSpinBox->move(this->width() / 2, 0);
    m_pcSpinBox->setValue(m_nRatedFps);
    m_pcSpinBox->setRange(1, 300);

    m_cTh01 = std::thread(&SDL_Qt_RGB::RunThread, this);
}

void SDL_Qt_RGB::InitSignalSlots(void)
{
    connect(this, &SDL_Qt_RGB::SendViews, this, &SDL_Qt_RGB::View);
}

void SDL_Qt_RGB::timerEvent(QTimerEvent* e)
{}

void SDL_Qt_RGB::resizeEvent(QResizeEvent* event)
{
    ui.label->resize(this->size());
    ui.label->move(0, 0);

    m_pcXVideo_View->SetScale(this->size().width(), this->size().height());
}

void SDL_Qt_RGB::View(void)
{
    if (m_pcXVideo_View->IsExit())
    {
        m_pcXVideo_View->Close();
        exit(0);
    }

    m_pcIfstream.read((char*)m_ptAVFrame->data[0], (streamsize)m_nWidth * m_nHeight);
    m_pcIfstream.read((char*)m_ptAVFrame->data[1], (streamsize)m_nWidth * m_nHeight / 4);
    m_pcIfstream.read((char*)m_ptAVFrame->data[2], (streamsize)m_nWidth * m_nHeight / 4);
    
    if (m_pcIfstream.gcount() == m_ullFilePathSize)     //循环播放数据;当m_pcIfstream读取到eof时，seekg无法回到文件开头，故采用此方法
    {
        m_pcIfstream.seekg(0, std::ios::beg);
    }


    m_pcXVideo_View->DrawFrame(m_ptAVFrame);

    m_nRatedFps = m_pcSpinBox->value();

    m_pcLabel->setText(QString::asprintf("fps:%d", m_pcXVideo_View->GetPerSecFPS()));
    m_pcLabel->adjustSize();
}

void SDL_Qt_RGB::RunThread(void)
{
    while (!m_bIsQuitThread)
    {
        emit SendViews();
        
        MSleep(1000 / m_nRatedFps);
    }
}
