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
    connect(&m_cDiceObject, &CDiceObject::SendCurMsg, this, [this](quint32 _CurFreq, quint8 _CurDiceRoll){
        QPixmap cPixmap(QString::asprintf(":/images/images/d%1d.jpg", _CurDiceRoll));

        ui->LabPic->setPixmap(cPixmap);
        ui->plainTextEdit->appendPlainText(QString::asprintf("投掷骰子当前次数: %08d, 点数: %1d", _CurFreq, _CurDiceRoll));
    });
}

void MainWindow::on_btnStartThread_clicked()
{
    m_cDiceObject.StartThread();
    QThreadPool::globalInstance()->start(&m_cDiceObject);

    ui->btnStartThread->setEnabled(false);
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
    ui->btnStopThread->setEnabled(true);

    ui->LabA->setText("Thread状态：thread start" );
}


void MainWindow::on_btnDiceBegin_clicked()
{
    m_cDiceObject.StartThrowDice();

    ui->btnStartThread->setEnabled(false);
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(true);
    ui->btnStopThread->setEnabled(false);

    ui->LabA->setText("Thread状态：thread begin" );
}


void MainWindow::on_btnDiceEnd_clicked()
{
    m_cDiceObject.StopThrowDice();

    ui->btnStartThread->setEnabled(false);
    ui->btnDiceBegin->setEnabled(true);
    ui->btnDiceEnd->setEnabled(false);
    ui->btnStopThread->setEnabled(true);

    ui->LabA->setText("Thread状态：thread end" );
}


void MainWindow::on_btnStopThread_clicked()
{
    m_cDiceObject.StopThread();
    // QThreadPool::globalInstance()->waitForDone();

    ui->btnStartThread->setEnabled(true);
    ui->btnDiceBegin->setEnabled(false);
    ui->btnDiceEnd->setEnabled(false);
    ui->btnStopThread->setEnabled(false);

    ui->LabA->setText("Thread状态：thread finish" );
}


void MainWindow::on_btnClear_clicked()
{
    ui->plainTextEdit->clear();
}

