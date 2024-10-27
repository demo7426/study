/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.27
描  述:	使用信号量实现线程之间的同步
备  注:
修改记录:

  1.  日期: 2024.10.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

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
    resize(1200, 800);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(&m_cDiceConsumer, &CDiceConsumer::SendCurMsg, this, [this](quint32 _CurFreq, QVector<quint32> _CurData){
        QString strContent = QString::asprintf("投掷骰子当前次数: %08d, 数值: ", _CurFreq);

        for (int i = 0; i < _CurData.size(); ++i) {
            strContent += QString::asprintf("%08d ", _CurData[i]);
        }

        ui->plainTextEdit->appendPlainText(strContent);
    });

    connect(&m_cDiceConsumer, &CDiceConsumer::SendCurState, this, [this](CDiceConsumer::STATE _State){
        if(_State == CDiceConsumer::STATE::RUN)
            ui->LabConsumer->setText(tr("消费者状态: 正在计算"));
        else
            ui->LabConsumer->setText(tr("消费者状态: 正在等待"));
    });

    connect(&m_cDiceProducer, &CDiceProducer::SendCurState, this, [this](CDiceProducer::STATE _State){
        if(_State == CDiceProducer::STATE::RUN)
            ui->LabProducer->setText(tr("生产者状态: 正在计算"));
        else
            ui->LabProducer->setText(tr("生产者状态: 正在等待"));
    });
}


void MainWindow::on_btnStartThread_clicked()
{
    m_cDiceConsumer.StartThread();
    m_cDiceProducer.StartThread();

    ui->btnStartThread->setEnabled(false);
    ui->btnStopThread->setEnabled(true);
}


void MainWindow::on_btnStopThread_clicked()
{
    m_cDiceProducer.StopThread();
    m_cDiceConsumer.StopThread();

    ui->btnStartThread->setEnabled(true);
    ui->btnStopThread->setEnabled(false);
}


void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

