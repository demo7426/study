/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	my_graphicsview.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.01
描  述:	自定义 QGraphicsView 的实现
备  注:  Scene不会显示图形,item才会显示图形
修改记录:

  1.  日期: 2024.10.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QMouseEvent>
#include <QGraphicsEllipseItem>

#include "my_graphicsview.h"
#include "my_graphicsellipseitem.h"


CMy_GraphicsView::CMy_GraphicsView(QWidget *parent)
    : QGraphicsView{parent}
{

    InitUi();
    InitSignalSlots();
}

void CMy_GraphicsView::InitUi() noexcept
{
    QGraphicsRectItem* pcGraphicsRectItem = new QGraphicsRectItem(-200, -100, 400, 200);
    QGraphicsEllipseItem* pcGraphicsEllipseItem_01 = new QGraphicsEllipseItem(-100, -50, 200, 100);         //椭圆
    QGraphicsEllipseItem* pcGraphicsEllipseItem_02 = new QGraphicsEllipseItem(-50, -50, 100, 100);          //圆

    QPen cPen;

    cPen.setWidth(5);

    this->setCursor(Qt::CrossCursor);
    this->setMouseTracking(true);

    //设置scene
    m_pcGraphicsScene = new QGraphicsScene(-200, -100, 400, 200);
    this->setScene(m_pcGraphicsScene);

    //添加item
    pcGraphicsRectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    pcGraphicsRectItem->setPen(cPen);

    m_pcGraphicsScene->addItem(pcGraphicsRectItem);

    pcGraphicsEllipseItem_01->setPos(0, 0);                     //设置item中心点坐标
    // pcGraphicsEllipseItem_01->setAcceptHoverEvents(true);             //接受鼠标拖动
    // pcGraphicsEllipseItem_01->setSelected(true);
    pcGraphicsEllipseItem_01->setBrush(QBrush(QColor(Qt::GlobalColor::darkBlue)));
    pcGraphicsEllipseItem_01->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    m_pcGraphicsScene->addItem(pcGraphicsEllipseItem_01);

    pcGraphicsEllipseItem_02->setPos(200, 100);                 //设置item中心点坐标
    // pcGraphicsEllipseItem_02->setAcceptHoverEvents(true);             //接受鼠标拖动
    pcGraphicsEllipseItem_02->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    m_pcGraphicsScene->addItem(pcGraphicsEllipseItem_02);

}

void CMy_GraphicsView::InitSignalSlots() noexcept
{

}

void CMy_GraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event == nullptr)
        return;

    if(event->button() & Qt::MouseButton::LeftButton)
    {
        emit SendMouseLeftClickSignal(event->pos());
    }

    QGraphicsView::mousePressEvent(event);
}

void CMy_GraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(event == nullptr)
        return;

    emit SendMouseMoveSignal(event->pos());

    QGraphicsView::mouseMoveEvent(event);
}


bool CMy_GraphicsView::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress){
        qDebug() << "MouseButtonPress";
    }else if(event->type() == QEvent::MouseMove){
        qDebug() <<" MouseMove ";
    }else if(event->type() == QEvent::MouseButtonRelease){
        qDebug() << "MouseButtonRelease";
    }
    return QObject::eventFilter(obj, event);
}
