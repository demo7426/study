#include "MyButton.h"
#include <QPainter>

CMyButton::CMyButton(QWidget *parent)
    : QWidget{parent}
{
    m_cQPixmap.load(":/new/prefix1/img/heart.png");
    setFixedSize(m_cQPixmap.size());
}

void CMyButton::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    m_cQPixmap.load(":/new/prefix1/img/age-restriction-sixteen.png");
    update();

    emit Pressed();
}

void CMyButton::mouseReleaseEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev)
    m_cQPixmap.load(":/new/prefix1/img/twitter.png");
    update();
}

void CMyButton::enterEvent(QEnterEvent *ev)
{
    Q_UNUSED(ev)
    m_cQPixmap.load(":/new/prefix1/img/twitter.png");
    update();
}

void CMyButton::leaveEvent(QEvent *ev)
{
    Q_UNUSED(ev)
    m_cQPixmap.load(":/new/prefix1/img/heart.png");
    update();
}

void CMyButton::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev)
    QPainter cQPainter(this);
    cQPainter.drawPixmap(rect(), m_cQPixmap);
}
