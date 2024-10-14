/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	customchartview.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.14
描  述:	自定义实现一个chartView,支持鼠标缩放，按键上下左右查看（暂只支持折线图）
备  注:
修改记录:

  1.  日期: 2024.10.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QChart>
#include <QValueAxis>
#include <QWheelEvent>

#include "customchartview.h"

CCustomChartView::CCustomChartView(QWidget *parent)
    : QChartView{parent}
{
    InitUi();
    InitSignalSlots();
}

void CCustomChartView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        m_cPointF_StartPos = event->position();
    }
    else if(event->button() & Qt::RightButton)
    {
        ScrollAndZoomReset();
    }

    QChartView::mousePressEvent(event);
}

void CCustomChartView::mouseMoveEvent(QMouseEvent *event)
{
    QChartView::mouseMoveEvent(event);
}

void CCustomChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::LeftButton)
    {
        QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Horizontal).at(0));
        QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Vertical).at(0));

        if(m_bResetStatus)
        {
            m_listPos.append((QPair<qreal, qreal>(pcValueAxis_X->min(), pcValueAxis_X->max())));
            m_listPos.append((QPair<qreal, qreal>(pcValueAxis_Y->min(), pcValueAxis_Y->max())));
            m_bResetStatus = false;
        }

        m_cPointF_EndPos = event->position();

        this->chart()->zoomIn(QRectF(m_cPointF_StartPos, m_cPointF_EndPos));
    }
    QChartView::mouseReleaseEvent(event);
}

void CCustomChartView::keyPressEvent(QKeyEvent *event)
{
    QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Horizontal).at(0));
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Vertical).at(0));

    if(m_bResetStatus)
    {
        m_listPos.append((QPair<qreal, qreal>(pcValueAxis_X->min(), pcValueAxis_X->max())));
        m_listPos.append((QPair<qreal, qreal>(pcValueAxis_Y->min(), pcValueAxis_Y->max())));
        m_bResetStatus = false;
    }

    switch (event->key()) {
    case Qt::Key_Up:
        this->chart()->scroll(0, -1);     
        break;
    case Qt::Key_Down:
        this->chart()->scroll(0, 1);
        break;
    case Qt::Key_Left:
        this->chart()->scroll(-1, 0);
        break;
    case Qt::Key_Right:
        this->chart()->scroll(1, 0);
        break;
    case Qt::Key_PageUp:
        this->chart()->scroll(0, -10);
        break;
    case Qt::Key_PageDown:
        this->chart()->scroll(0, 10);
        break;
    case Qt::Key_Home:
        ScrollAndZoomReset();
        break;
    case Qt::Key_Plus:
        this->chart()->zoom(1.1);
        break;
    case Qt::Key_Minus:
        this->chart()->zoom(0.9);
        break;
    default:
        m_bResetStatus = true;
        break;
    }

    QChartView::keyPressEvent(event);
}

void CCustomChartView::wheelEvent(QWheelEvent *event)
{
    QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Horizontal).at(0));
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Vertical).at(0));

    if(m_bResetStatus)
    {
        m_listPos.append((QPair<qreal, qreal>(pcValueAxis_X->min(), pcValueAxis_X->max())));
        m_listPos.append((QPair<qreal, qreal>(pcValueAxis_Y->min(), pcValueAxis_Y->max())));
        m_bResetStatus = false;
    }

    QPointF mousePos = chart()->mapToValue(event->position(), chart()->series().at(0));

    // 缩放因子，滚轮向上放大，向下缩小
    qreal factor = (event->angleDelta().y() > 0) ? 0.9 : 1.1;

    // 获取当前坐标轴的范围
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart()->axisX());
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart()->axisY());

    if (axisX && axisY)
    {
        qreal xMin = axisX->min();
        qreal xMax = axisX->max();
        qreal yMin = axisY->min();
        qreal yMax = axisY->max();

        // 计算新的范围，以鼠标为中心缩放
        qreal newXMin = mousePos.x() - (mousePos.x() - xMin) * factor;
        qreal newXMax = mousePos.x() + (xMax - mousePos.x()) * factor;
        qreal newYMin = mousePos.y() - (mousePos.y() - yMin) * factor;
        qreal newYMax = mousePos.y() + (yMax - mousePos.y()) * factor;

        // 设置新的坐标轴范围
        axisX->setRange(newXMin, newXMax);
        axisY->setRange(newYMin, newYMax);
    }
    QChartView::wheelEvent(event);
}

void CCustomChartView::InitUi() noexcept
{

    this->setMouseTracking(true);                           //设置鼠标追踪
    this->setDragMode(QGraphicsView::RubberBandDrag);       //设置鼠标拖动，显示矩形窗口

    m_cPointF_StartPos.setX(0);
    m_cPointF_StartPos.setY(0);
    m_cPointF_EndPos.setX(0);
    m_cPointF_EndPos.setY(0);

}

void CCustomChartView::InitSignalSlots() noexcept
{

}

void CCustomChartView::ScrollAndZoomReset(void)
{
    QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Horizontal).at(0));
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>(this->chart()->axes(Qt::Vertical).at(0));

    pcValueAxis_X->setRange(m_listPos[0].first, m_listPos[0].second);
    pcValueAxis_Y->setRange(m_listPos[1].first, m_listPos[1].second);

    m_bResetStatus = true;
}
