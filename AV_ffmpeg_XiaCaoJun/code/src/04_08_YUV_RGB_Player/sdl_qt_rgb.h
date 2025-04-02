/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.04.02
描  述: 使用SDL在Qt的界面上,播放两路AVFrame的YUV、RGBA等视频文件，并且控制帧率
备  注: 帧率控制使用的是 QElapsedTimer 计算的时间间隔，可以使用 clock 提高时间精度精确控制帧率，或者多线程发送信号精确控制帧率
        
        cmd终端执行以下指令
            ffmpeg lu_fei.mp4 -s 400x300 lu_fei_400x300_30.yuv                      //可以生成 yuv 格式的文件
            ffmpeg lu_fei.mp4 -s 800x400 -pix_fmt rgba lu_fei_800x400_30.rgb        //可以生成 rgba 格式的文件
修改记录:

  1.  日期: 2025.04.02
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
#include <qelapsedtimer.h>

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

    int m_nWidth[2] = { 400, 800 };                 //窗口的宽
    int m_nHeight[2] = { 300, 400 };                //窗口的高
    qint32 m_nPixSize = 4;                          //像素点大小

    quint64  m_ullFilePathSize = 0;                 //文件大小，单位Byte

    CXVideo_View* m_pcXVideo_View[2] = { nullptr, nullptr };

    std::thread m_cTh01;
    bool m_bIsQuitThread = false;                   //是否退出线程

    QLabel* m_pcLabel[2] = { nullptr, nullptr };    //用于显示fps帧率

    qint32 m_nRatedFps[2] = { 30, 30 };             //额定帧率

    QElapsedTimer m_cElapsedTimer[2];
};
