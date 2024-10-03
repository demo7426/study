/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	my_graphicsellipseitem.h
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

#ifndef MY_GRAPHICSELLIPSEITEM_H
#define MY_GRAPHICSELLIPSEITEM_H

#include <QGraphicsEllipseItem>
#include <QWidget>
#include <QPointF>

class CMy_GraphicsEllipseItem : public QGraphicsEllipseItem
{
public:
    explicit CMy_GraphicsEllipseItem(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);

private:
    bool m_mousePressed = false;

protected:
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;

    void mousePressEvent( QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent( QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent( QGraphicsSceneMouseEvent* event) override;

signals:
};

#endif // MY_GRAPHICSELLIPSEITEM_H
