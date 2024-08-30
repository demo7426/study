/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	widget.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.30
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.08.30
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QCalendarWidget>

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

void Widget::InitUi() noexcept
{
    InitCurDateTime();

    m_cTimer.setInterval(0);
}

void Widget::InitSignalSlots() noexcept
{
    connect(ui->pushBtnReadCurDatetime, &QPushButton::clicked, this, &Widget::SetCurAllDatetime);
    connect(ui->pushBtnTime, &QPushButton::clicked, this, [=](){
        ui->lineEditCurTime->setText(ui->timeEdit->text());
    });

    connect(ui->pushBtnDate, &QPushButton::clicked, this, [=](){
        ui->lineEditCurDate->setText(ui->dateEdit->text());
    });

    connect(ui->pushBtnDateTime, &QPushButton::clicked, this, [=](){
        ui->lineEditCurDateTime->setText(ui->dateTimeEdit->text());
    });

    //链接定时器
    connect(&this->m_cTimer, &QTimer::timeout, this, &Widget::SetLCDNum);

    connect(ui->pushBtnSetTimePeriod, &QPushButton::clicked, this, [=](){
        m_cTimer.setInterval(ui->spinBox->value());
    });

    connect(ui->pushBtnTimerStart, &QPushButton::clicked, this, [=](){
        ui->pushBtnTimerStart->setEnabled(false);
        ui->pushBtnSetTimePeriod->setEnabled(false);
        ui->pushBtnTimerStop->setEnabled(true);

        m_cTimer.start();
        m_cElapsedTimer.start();
    });

    connect(ui->pushBtnTimerStop, &QPushButton::clicked, this, [=](){
        m_cTimer.stop();
        ui->labelElapsedTime->setText(QString::asprintf("%llu秒%llu毫秒",
                                                        m_cElapsedTimer.elapsed()/1000, m_cElapsedTimer.elapsed()%1000));

        ui->pushBtnTimerStart->setEnabled(true);
        ui->pushBtnSetTimePeriod->setEnabled(true);
        ui->pushBtnTimerStop->setEnabled(false);
    });

    connect(ui->calendarWidget, &QCalendarWidget::selectionChanged, this, [=](){
        QCalendarWidget* pcCalendarWidget = qobject_cast<QCalendarWidget*>(sender());
        QDate cDate = pcCalendarWidget->selectedDate();

        ui->lineEditSelectDateTime->setText(cDate.toString("yyyy/MM/dd"));
    });
}

void Widget::InitCurDateTime() noexcept
{
    QTime cCurTime = QTime::currentTime();
    QDate cCurDate = QDate::currentDate();
    QDateTime cCurDateTime = QDateTime::currentDateTime();

    this->SetCurAllDatetime();

    ui->timeEdit->setTime(cCurTime);
    ui->dateEdit->setDate(cCurDate);
    ui->dateTimeEdit->setDateTime(cCurDateTime);
}

void Widget::SetCurAllDatetime() noexcept
{
    QTime cCurTime = QTime::currentTime();
    QDate cCurDate = QDate::currentDate();
    QDateTime cCurDateTime = QDateTime::currentDateTime();

    ui->lineEditCurTime->setText(cCurTime.toString("HH:mm:ss"));
    ui->lineEditCurDate->setText(cCurDate.toString("yyyy/MM/dd"));
    ui->lineEditCurDateTime->setText(cCurDateTime.toString("yyyy/MM/dd HH:mm:ss"));
}

void Widget::SetLCDNum() noexcept
{
    QTime cCurTime = QTime::currentTime();

    int nHour = cCurTime.hour();
    int nMinute = cCurTime.minute();
    int nSecond = cCurTime.second();

    ui->lcdNumHour->display(nHour);
    ui->lcdNumMinute->display(nMinute);
    ui->lcdNumSecond->display(nSecond);
}


