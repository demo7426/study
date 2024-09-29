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
    QPen cPen;
    QBrush cBrush;
    QFont cFont;

    QPainterPath cPainterPath;

    constexpr qreal dbRadius = 100;                                         //半径
    constexpr qreal dbRadian = 3.1415926 * (360 / 5) / 180;                 //弧度(72代表72°)
    static const QPoint cPoints[] = { QPoint(dbRadius, 0),
        QPoint(dbRadius * cos(dbRadian), -dbRadius * sin(dbRadian)),
        QPoint(dbRadius * cos(dbRadian * 2), -dbRadius * sin(dbRadian * 2)),
        QPoint(dbRadius * cos(dbRadian * 3), -dbRadius * sin(dbRadian * 3)),
        QPoint(dbRadius * cos(dbRadian * 4), -dbRadius * sin(dbRadian * 4)) };

    cPen.setStyle(Qt::PenStyle::SolidLine);

    cBrush.setColor(Qt::GlobalColor::yellow);
    cBrush.setStyle(Qt::BrushStyle::Dense3Pattern);

    cFont.setPointSize(7);  //设置字体大小

    //连线
    cPainterPath.moveTo(cPoints[3]);
    cPainterPath.lineTo(cPoints[1]);
    cPainterPath.lineTo(cPoints[4]);
    cPainterPath.lineTo(cPoints[2]);
    cPainterPath.lineTo(cPoints[0]);
    cPainterPath.closeSubpath();

    cPainter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);           //启用抗锯齿功能

    cPainter.setPen(cPen);
    cPainter.setBrush(cBrush);
    cPainter.setFont(cFont);

    for (quint32 i = 0; i < sizeof(cPoints) / sizeof(cPoints[0]); ++i)
    {
        cPainterPath.addText(cPoints[i], cFont, QString::asprintf("%d", i));
    }
    // cPainter.drawText(QPointF(0, 0), tr("五角星"));

    cPainter.save();                            //保存当前状态到栈内
    cPainter.translate(QPoint(200, 200));       //平移 QPainter 对应的原点坐标系
    cPainter.drawPath(cPainterPath);

    //顺时针旋转90°，缩小
    cPainter.restore();                         //回溯之前的状态
    cPainter.save();                            //保存当前状态到栈内
    cPainter.translate(QPoint(400, 200));       //再次平移 QPainter 对应的原点坐标系
    cPainter.rotate(90);                        //旋转 QPainter 坐标系
    cPainter.scale(0.7, 0.7);
    cPainter.drawPath(cPainterPath);

    cPainter.restore();                         //回溯之前的状态
    cPainter.translate(QPoint(600, 200));       //再次平移 QPainter 对应的原点坐标系
    cPainter.rotate(-90);                        //旋转 QPainter 坐标系
    cPainter.scale(1.2, 1.2);
    cPainter.drawPath(cPainterPath);
}

void Widget::InitUi() noexcept
{
    setPalette(QPalette(Qt::GlobalColor::white));
    setAutoFillBackground(true);
}

void Widget::InitSignalSlots() noexcept
{

}
