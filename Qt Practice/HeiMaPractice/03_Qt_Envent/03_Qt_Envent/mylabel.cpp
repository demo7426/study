#include "mylabel.h"
#include<QDebug>
#include<QMouseEvent>
#include<QEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

}

void MyLabel::enterEvent(QEvent *)
{
    qDebug()<<"鼠标进入";
}

void MyLabel::leaveEvent(QEvent *)
{
    qDebug()<<"鼠标离开";
}

void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QString str = QString("鼠标移动：x = %1, y = %2").arg(event->x()). arg(event->y());
        qDebug() << str;
    }
}

void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        QString str = QString("鼠标按压：x = %1, y = %2").arg(event->x()). arg(event->y());
        qDebug() << str;
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        QString str = QString("鼠标释放：x = %1, y = %2").arg(event->x()). arg(event->y());
        qDebug() << str;
    }
}


bool MyLabel::event(QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *ev = static_cast<QMouseEvent *>(e);

        QString str = QString("event：鼠标按压：x = %1, y = %2").arg(ev->x()). arg(ev->y());
        qDebug() << str;
        return true;
    }

    return QLabel::event(e);
}


