/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.29
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QPainter>
#include <QPen>
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    qint32 nWidth = this->width();
    qint32 nHeight = this->height();

    QPainter cPainter(this);
    QPen cPen;                                              //画笔
    QBrush cBrush;                                          //画刷
    QFont cFont;                                            //画的字体
    QImage cImage(tr(":/images/images/MSI_MAG.jpg"));
    QList<QPoint> cListPoint;

    cPen.setWidth(10);
    cPen.setColor(Qt::GlobalColor::red);
    cPen.setStyle(Qt::PenStyle::DashDotDotLine);
    cPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
    cPen.setCapStyle(Qt::RoundCap);

    cBrush.setColor(Qt::GlobalColor::darkGreen);
    cBrush.setStyle(Qt::BrushStyle::Dense3Pattern);

    cFont.setPointSize(12);

    cPainter.setPen(cPen);
    cPainter.setBrush(cBrush);
    cPainter.setFont(cFont);

    cListPoint.append(QPoint(nWidth / 2, nHeight / 2));
    cListPoint.append(QPoint(nWidth * 3 / 4, nHeight * 3 / 4));
    cListPoint.append(QPoint(nWidth / 2, nHeight / 4));
    cListPoint.append(QPoint(nWidth / 2, nHeight / 2));

    cPainter.drawRect(nWidth / 8, nHeight / 8, nWidth / 4, nHeight / 4);
    cPainter.drawText(nWidth / 2, nHeight / 8, QCoreApplication::applicationName());
    cPainter.drawImage(QRect(nWidth / 8, nHeight / 2, nWidth / 4, nHeight / 4), cImage);
    cPainter.drawPolyline(cListPoint);

}

void Widget::InitUi() noexcept
{
    setPalette(QPalette(Qt::GlobalColor::white));
    setAutoFillBackground(true);
}

void Widget::InitSignalSlots() noexcept
{

}
