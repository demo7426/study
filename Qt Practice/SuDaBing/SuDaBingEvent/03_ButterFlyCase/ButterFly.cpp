#include "ButterFly.h"
#include <QPainter>
#include <QMouseEvent>
#include <QRandomGenerator>
#include <QScreen>
#include <QGuiApplication>

CButterFly::CButterFly(QWidget *parent)
    : QWidget{parent}, m_nCurPicPath_Index(0)
{
    for (size_t i = 0; i < sizeof(m_strPicPath) / sizeof(m_strPicPath[0]); ++i)
    {
        m_strPicPath[i] = QString(":/new/prefix1/%1").arg(i + 1);
    }

    m_cQPixmap.load(m_strPicPath[m_nCurPicPath_Index++]);
    setFixedSize(m_cQPixmap.size());
    update();

    startTimer(100);
}



void CButterFly::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter cQPainter(this);                       //这里一定要指定其画布对象为this
    cQPainter.drawPixmap(rect(), m_cQPixmap);
}

void CButterFly::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    Fly();
}

void CButterFly::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    {
        m_cQPoint_Relative = event->globalPos() - this->geometry().topLeft();
    }
}

void CButterFly::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->buttons() & Qt::LeftButton)
    {
        this->move(event->globalPos() - m_cQPoint_Relative);
    }
}

void CButterFly::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    Fly(40, 100);
}

void CButterFly::Fly(int _Min, int _Max)
{
    m_cQPixmap.load(m_strPicPath[m_nCurPicPath_Index++]);

    m_nCurPicPath_Index %= sizeof(m_strPicPath) / sizeof(m_strPicPath[0]);
    update();

    int nRandomX = QRandomGenerator::global()->bounded(_Min, _Max);
    int nRandomY = QRandomGenerator::global()->bounded(_Min, _Max);

    int nCurX = nRandomX + this->x();
    int nCurY = nRandomY + this->y();

    QScreen* pcQScreen = QGuiApplication::primaryScreen();
    if(nCurX >= pcQScreen->geometry().left() + pcQScreen->geometry().right())
        nCurX = pcQScreen->geometry().left();

    if(nCurY >= pcQScreen->geometry().top() + pcQScreen->geometry().bottom())
        nCurY = pcQScreen->geometry().top();

    this->move(nCurX, nCurY);
}
