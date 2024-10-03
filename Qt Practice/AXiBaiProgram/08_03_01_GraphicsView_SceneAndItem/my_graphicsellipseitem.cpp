/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	my_graphicsellipseitem.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.01
描  述:	自定义 QGraphicsEllipseItem 的实现，实现自定义鼠标拖动
备  注:
修改记录:

  1.  日期: 2024.10.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QGraphicsSceneHoverEvent>
#include "my_graphicsellipseitem.h"

CMy_GraphicsEllipseItem::CMy_GraphicsEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent)
    :QGraphicsEllipseItem(x, y, width, height, parent)
{
}

void CMy_GraphicsEllipseItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    // if(m_mousePressed==true)
    // {
    //     qDebug() << "2";
    //     this->setPos(event->scenePos());
    // }

    QGraphicsEllipseItem::hoverMoveEvent(event);
}

void CMy_GraphicsEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    m_mousePressed=true;

    event->accept();
    // QGraphicsEllipseItem::mousePressEvent(event);
}

void CMy_GraphicsEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(m_mousePressed==true)
    {
        this->setPos(event->scenePos());
    }

    QGraphicsEllipseItem::mouseMoveEvent(event);
}

void CMy_GraphicsEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    // Q_UNUSED(event);

    if(m_mousePressed==true)
    {
        this->setPos(event->scenePos());
    }

    m_mousePressed=false;

    QGraphicsEllipseItem::mouseReleaseEvent(event);
}
