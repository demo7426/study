/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.02
描  述: 使用SDL在Qt的界面上,播放两路AVFrame的YUV、RGBA等视频文件，并且控制帧率
备  注: 帧率控制使用的是 QElapsedTimer 计算的时间间隔，可以使用 clock 提高时间精度精确控制帧率，或者多线程发送信号精确控制帧率

        cmd终端执行以下指令
            ffmpeg -i lu_fei.mp4 -s 400x300 lu_fei_400x300_30.yuv                      //可以生成 yuv 格式的文件
            ffmpeg -i lu_fei.mp4 -s 800x400 -pix_fmt rgba lu_fei_800x400_30.rgb        //可以生成 rgba 格式的文件
修改记录:

  1.  日期: 2025.04.02
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
#include <qfiledialog.h>

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
    for (size_t i = 0; i < sizeof(m_pcXVideo_View) / sizeof(m_pcXVideo_View[0]); i++)
    {
        if (m_pcXVideo_View[i])
        {
            delete m_pcXVideo_View[i];
            m_pcXVideo_View[i] = nullptr;
        }
    }

    m_bIsQuitThread = true;         //保证线程退出，资源正常释放
    m_cTh01.join();
}

void SDL_Qt_RGB::InitUi(void)
{
    qint32 nRet = 0;
    QStringList strFormatItem = { "ARGB", "RGBA", "ABGR", "BGRA", "YUV420P" };

    QScreen* screen = QGuiApplication::primaryScreen();

    m_pcXVideo_View[0] = CXVideo_View::Create();
    m_pcXVideo_View[1] = CXVideo_View::Create();
    //m_pcXVideo_View->Init(m_nWidth, m_nHeight, CXVideo_View::Format::YUV420P, nullptr);

    for (size_t i = 0; i < sizeof(m_pcLabel) / sizeof(m_pcLabel[0]); i++)
    {
        m_pcLabel[i] = new QLabel(this);
        m_pcLabel[i]->adjustSize();
    }

    m_pcLabel[0]->move(ui.labelVideo_0->pos());
    m_pcLabel[1]->move(ui.labelVideo_1->pos());

    ui.spinBox_Width_0->setRange(1, 9999'9999);
    ui.spinBox_Height_0->setRange(1, 9999'9999);
    ui.spinBox_FPS_0->setRange(1, 360);

    ui.spinBox_Width_0->setValue(m_nWidth[0]);
    ui.spinBox_Height_0->setValue(m_nHeight[0]);
    ui.spinBox_FPS_0->setValue(m_nRatedFps[0]);

    ui.spinBox_Width_1->setRange(1, 9999'9999);
    ui.spinBox_Height_1->setRange(1, 9999'9999);
    ui.spinBox_FPS_1->setRange(1, 360);

    ui.spinBox_Width_1->setValue(m_nWidth[1]);
    ui.spinBox_Height_1->setValue(m_nHeight[1]);
    ui.spinBox_FPS_1->setValue(m_nRatedFps[1]);

    ui.comboBox_Format_0->addItems(strFormatItem);
    ui.comboBox_Format_1->addItems(strFormatItem);

    ui.labelVideo_0->resize(ui.spinBox_Width_0->value(), ui.spinBox_Height_0->value());
    ui.labelVideo_1->resize(ui.spinBox_Width_1->value(), ui.spinBox_Height_1->value());

    m_cTh01 = std::thread(&SDL_Qt_RGB::RunThread, this);
}

void SDL_Qt_RGB::InitSignalSlots(void)
{
    connect(this, &SDL_Qt_RGB::SendViews, this, &SDL_Qt_RGB::View);

    connect(ui.pushBtnSelectFile_0, &QPushButton::clicked, this, [=]() {
        QString strFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QDir::currentPath());
        CXVideo_View::Format eFmt = CXVideo_View::Format::ARGB;

        if (strFilePath.isEmpty())
            return;

        ui.labelVideo_0->resize(ui.spinBox_Width_0->value(), ui.spinBox_Height_0->value());

        if (ui.comboBox_Format_0->currentText() == "ARGB")
            eFmt = CXVideo_View::Format::ARGB;
        else if (ui.comboBox_Format_0->currentText() == "RGBA")
            eFmt = CXVideo_View::Format::RGBA;
        else if (ui.comboBox_Format_0->currentText() == "ABGR")
            eFmt = CXVideo_View::Format::ABGR;
        else if (ui.comboBox_Format_0->currentText() == "BGRA")
            eFmt = CXVideo_View::Format::BGRA;
        else if (ui.comboBox_Format_0->currentText() == "YUV420P")
            eFmt = CXVideo_View::Format::YUV420P;

        m_pcXVideo_View[0]->Init(ui.spinBox_Width_0->value(), ui.spinBox_Height_0->value(), eFmt, (void*)ui.labelVideo_0->winId());
        m_pcXVideo_View[0]->OpenFile(strFilePath.toLocal8Bit().constData());
        m_cElapsedTimer[0].start();
        });

    connect(ui.pushBtnSelectFile_1, &QPushButton::clicked, this, [=]() {
        QString strFilePath = QFileDialog::getOpenFileName(this, tr("选择单个文件"), QDir::currentPath());
        CXVideo_View::Format eFmt = CXVideo_View::Format::ARGB;

        if (strFilePath.isEmpty())
            return;

        ui.labelVideo_1->resize(ui.spinBox_Width_1->value(), ui.spinBox_Height_1->value());

        if (ui.comboBox_Format_1->currentText() == "ARGB")
            eFmt = CXVideo_View::Format::ARGB;
        else if (ui.comboBox_Format_1->currentText() == "RGBA")
            eFmt = CXVideo_View::Format::RGBA;
        else if (ui.comboBox_Format_1->currentText() == "ABGR")
            eFmt = CXVideo_View::Format::ABGR;
        else if (ui.comboBox_Format_1->currentText() == "BGRA")
            eFmt = CXVideo_View::Format::BGRA;
        else if (ui.comboBox_Format_1->currentText() == "YUV420P")
            eFmt = CXVideo_View::Format::YUV420P;

        m_pcXVideo_View[1]->Init(ui.spinBox_Width_1->value(), ui.spinBox_Height_1->value(), eFmt, (void*)ui.labelVideo_1->winId());
        m_pcXVideo_View[1]->OpenFile(strFilePath.toLocal8Bit().constData());
        m_cElapsedTimer[1].start();
        });
}

void SDL_Qt_RGB::timerEvent(QTimerEvent* e)
{}

void SDL_Qt_RGB::resizeEvent(QResizeEvent* event)
{
    //m_pcXVideo_View->SetScale(this->size().width(), this->size().height());
}

void SDL_Qt_RGB::View(void)
{
    if (m_pcXVideo_View[0]->IsExit())
        m_pcXVideo_View[0]->Close();

    if (m_pcXVideo_View[1]->IsExit())
        m_pcXVideo_View[1]->Close();

    AVFrame* ptAVFrame = nullptr;

    for (size_t i = 0; i < sizeof(m_pcXVideo_View) / sizeof(m_pcXVideo_View[0]); i++)
    {
        if (m_cElapsedTimer[i].elapsed() < (1000 / m_nRatedFps[i]))         //实现ui界面帧率分开控制的效果
            continue;

        m_cElapsedTimer[i].restart();

        ptAVFrame = m_pcXVideo_View[i]->GetFileAVFrame();
        if (!ptAVFrame)
            continue;

        m_pcXVideo_View[i]->DrawFrame(ptAVFrame);

        m_pcXVideo_View[0]->SetScale(ui.spinBox_Width_0->value(), ui.spinBox_Height_0->value());
        m_pcXVideo_View[1]->SetScale(ui.spinBox_Width_1->value(), ui.spinBox_Height_1->value());

        //////////////////////////////////处理ui变化//////////////////////////////////
        
        ui.labelVideo_0->resize(ui.spinBox_Width_0->value(), ui.spinBox_Height_0->value());
        ui.labelVideo_1->resize(ui.spinBox_Width_1->value(), ui.spinBox_Height_1->value());

        m_nRatedFps[0] = ui.spinBox_FPS_0->value();
        m_nRatedFps[1] = ui.spinBox_FPS_1->value();

        m_pcLabel[i]->setText(QString::asprintf("FPS: %u", m_pcXVideo_View[i]->GetPerSecFPS()));
        m_pcLabel[i]->adjustSize();

        //////////////////////////////////////////////////////////////////////////////
    }
    
}

void SDL_Qt_RGB::RunThread(void)
{
    qint32 nTimeout = 5;
    while (!m_bIsQuitThread)
    {
        emit SendViews();
        
        QApplication::processEvents(QEventLoop::AllEvents, nTimeout);       //表示调用后将处理所有类型的事件，但最多只处理 nTimeout 毫秒时间内的事件
        MSleep(nTimeout);
    }
}
