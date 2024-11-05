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
