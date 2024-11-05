/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	myvideowidget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.05
描  述:	自定义QVideoWidget子类
备  注:	推荐使用Qt5进行编译
修改记录:

  1.  日期: 2024.11.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QKeyEvent>
#include <QMouseEvent>

#include "myvideowidget.h"

CMyVideoWidget::CMyVideoWidget(QWidget *parent) : QVideoWidget(parent)
{
}

void CMyVideoWidget::SetMediaPlayer(QMediaPlayer *_pMediaPlayer)
{
    m_pcMediaPlayer = _pMediaPlayer;
}

void CMyVideoWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        setFullScreen(false);
    }

    QVideoWidget::keyPressEvent(event);
}

void CMyVideoWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton && m_pcMediaPlayer != nullptr)
    {
        if(m_pcMediaPlayer->state() == QMediaPlayer::State::PlayingState)
            m_pcMediaPlayer->pause();
        else
            m_pcMediaPlayer->play();
    }

    QVideoWidget::mousePressEvent(event);
}
