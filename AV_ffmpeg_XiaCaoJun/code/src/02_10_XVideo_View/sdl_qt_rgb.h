/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	sdl_qt_rgb.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2025.03.16
描  述: 使用SDL在Qt的界面上播放YUV视频文件
备  注:
修改记录:

  1.  日期: 2025.03.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本;
      版本:V0.1.0

*************************************************/

#pragma once

#include <QtWidgets/QWidget>
#include <fstream>

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

protected:
    void timerEvent(QTimerEvent* e) override;

    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::SDL_Qt_RGBClass ui;

    int m_nWidth = 1280;                            //窗口的宽
    int m_nHeight = 720;                            //窗口的高
    qint32 m_nPixSize = 4;                          //像素点大小
    char* m_puchYUV = nullptr;                      //图像内部ARGB数据

    std::ifstream m_pcIfstream;

    CXVideo_View* m_pcXVideo_View = nullptr;
};
