/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.26
描  述:	使用moveToThread实现线程的切换
备  注:
修改记录:

  1.  日期: 2024.10.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QThread>
#include <QtConcurrent>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi(void) noexcept
{
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(&m_cDiceConsumer, &CDiceConsumer::SendCurMsg, this, [this](quint32 _CurFreq, quint8 _CurDiceRoll){
        QPixmap cPixmap(QString::asprintf(":/images/images/d%1d.jpg", _CurDiceRoll));

        ui->LabPic->setPixmap(cPixmap);
        ui->plainTextEdit->appendPlainText(QString::asprintf("投掷骰子当前次数: %08d, 点数: %1d", _CurFreq, _CurDiceRoll));
    });
}

void MainWindow::on_btnStartThread_clicked()
{
    auto bindProducer = std::bind(&CDiceProducer::Run, &m_cDiceProducer);
    auto bindComsumer = std::bind(&CDiceConsumer::Run, &m_cDiceConsumer);

    m_cDiceConsumer.StartThread();
    m_cDiceProducer.StartThread();

    QtConcurrent::run(bindComsumer);
    QtConcurrent::run(bindProducer);

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);

    ui->LabA->setText("Thread状态：thread start" );
}

void MainWindow::on_btnStopThread_clicked()
{
    m_cDiceProducer.StopThread();
    m_cDiceConsumer.StopThread();

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);

    ui->LabA->setText("Thread状态：thread finish" );
}


void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

