/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	userbattery.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.24
描  述:	实现自定义电池绘制及接口
备  注:
修改记录:

  1.  日期: 2024.10.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QPainter>
#include <QFontMetrics>

#include "userbattery.h"
#include "ui_userbattery.h"

CUserBattery::CUserBattery(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CUserBattery)
{
    ui->setupUi(this);
}

CUserBattery::~CUserBattery()
{
    delete ui;
}

void CUserBattery::paintEvent(QPaintEvent *event)
{
    //绘制电池ui界面
    QPainter cPainter(this);
    QRect cRect(this->rect());      //视口大小
    QPen cPen;
    QBrush cBrush;

    cPainter.setViewport(cRect);
    cPainter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    cPainter.setWindow(0, 0, 120, 50);

    //绘制电池边框
    cPen.setWidth(2);
    cPen.setColor(m_cColoBorder);
    cPen.setStyle(Qt::SolidLine);
    cPen.setCapStyle(Qt::FlatCap);
    cPen.setJoinStyle(Qt::BevelJoin);

    cBrush.setColor(m_cColoBorder);
    cBrush.setStyle(Qt::SolidPattern);

    cPainter.setPen(cPen);

    cPainter.drawRect(1, 1, 109, 48);

    cPainter.setBrush(cBrush);
    cPainter.drawRect(110, 15, 9, 20);

    //绘制电池电量
    if(m_shPowerLevel <= m_shElectricThreshold)
    {
        cPen.setColor(m_cColoLowerPower);
        cBrush.setColor(m_cColoLowerPower);
    }
    else
    {
        cPen.setColor(m_cColoHighPower);
        cBrush.setColor(m_cColoHighPower);
    }

    cPainter.setPen(cPen);
    cPainter.setBrush(cBrush);

    if(m_shPowerLevel != 0)
        cPainter.drawRect(6, 5, 100 * m_shPowerLevel / 100, 40);

    //绘制电量百分比字体
    QFontMetrics cFontMetrics(this->font());
    QString strPowerLevel = QString::asprintf("%d%%", m_shPowerLevel);
    QRect cRectFont = cFontMetrics.boundingRect(strPowerLevel);             //得到字符串的rect

    cPen.setColor(m_cColoBorder);
    cPainter.setPen(cPen);
    cPainter.drawText(55 - cRectFont.width() / 2, 40 - cRectFont.height() / 2, strPowerLevel);

    QWidget::paintEvent(event);
}
