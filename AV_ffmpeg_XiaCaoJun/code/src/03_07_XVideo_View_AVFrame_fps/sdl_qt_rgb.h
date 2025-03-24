/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.h
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

#pragma once

#include <QtWidgets/QWidget>
#include <fstream>
#include <thread>
#include <qspinbox.h>

#include "ui_sdl_qt_rgb.h"

#include "xvideo_view.h"

class SDL_Qt_RGB : public QWidget
{
    Q_OBJECT

public:
    SDL_Qt_RGB(QWidget *parent = nullptr);
    ~SDL_Qt_RGB();

    /// <summary>
    /// 初始化ui界面
    /// </summary>
    /// <param name=""></param>
    void InitUi(void);

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    /// <param name=""></param>
    void InitSignalSlots(void);

protected:
    void timerEvent(QTimerEvent* e) override;

    void resizeEvent(QResizeEvent* event) override;

signals:
    void SendViews(void);

private:
    /// <summary>
    /// 读取数据，并且刷新到xvideo_view模块
    /// </summary>
    /// <param name=""></param>
    void View(void);

    /// <summary>
    /// 线程主函数
    /// </summary>
    /// <param name=""></param>
    void RunThread(void);

private:
    Ui::SDL_Qt_RGBClass ui;

    int m_nWidth = 1280;                            //窗口的宽
    int m_nHeight = 720;                            //窗口的高
    qint32 m_nPixSize = 4;                          //像素点大小
    AVFrame* m_ptAVFrame = nullptr;

    constexpr static const char* m_pchFilePath = "../../src/03_07_XVideo_View_AVFrame_fps/1.yuv";
    quint64  m_ullFilePathSize = 0;                 //文件大小，单位Byte
    std::ifstream m_pcIfstream;

    CXVideo_View* m_pcXVideo_View = nullptr;

    std::thread m_cTh01;
    bool m_bIsQuitThread = false;                   //是否退出线程

    QLabel* m_pcLabel = nullptr;                    //用于显示fps帧率
    QSpinBox* m_pcSpinBox = nullptr;                //用于设置显示fps帧率

    qint32 m_nRatedFps = 25;                        //额定帧率
};
