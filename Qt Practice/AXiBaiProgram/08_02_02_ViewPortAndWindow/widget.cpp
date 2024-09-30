/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.30
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QPainter>
#include <QPen>
#include <QPainterPath>

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

    QPainter cPainter(this);
    QLinearGradient cLinearGradient(0, 0, 100, 0);

    qint32 nCurWindth = this->width();
    qint32 nCurHeight = this->height();

    qint32 nMinLen = qMin(nCurWindth, nCurHeight);
    QRect cRect((nCurWindth - nMinLen) / 2, (nCurHeight - nMinLen) / 2, nMinLen, nMinLen);

    cPainter.drawRect(cRect);
    cPainter.setViewport(cRect);                                //设置视口大小

    cPainter.setRenderHint(QPainter::Antialiasing);             //抗锯齿

    cPainter.setWindow(-100, -100, 200, 200);                   //设置窗口大小、逻辑坐标

    //设置渐变色
    cLinearGradient.setColorAt(0, Qt::gray);
    cLinearGradient.setColorAt(1, QColor(137, 207, 240));
    cLinearGradient.setSpread(QGradient::PadSpread);            //设置扩散模式

    cPainter.setBrush(cLinearGradient);
    cPainter.setCompositionMode(QPainter::CompositionMode::RasterOp_NotSourceXorDestination);       //设置复合模式

    for (int i = 0; i < 36; ++i) {
        cPainter.drawEllipse(QPoint(50, 0), 50, 50);
        cPainter.rotate(10);                                    //顺时针旋转
    }
}

void Widget::InitUi() noexcept
{
    setPalette(QPalette(Qt::GlobalColor::white));
    setAutoFillBackground(true);
    resize(600, 600);
}

void Widget::InitSignalSlots() noexcept
{

}
