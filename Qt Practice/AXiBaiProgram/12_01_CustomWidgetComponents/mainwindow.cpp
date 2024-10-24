/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.24
描  述:	实现主界面显示
备  注:
修改记录:

  1.  日期: 2024.10.24
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
    ui->horizontalSlider->setValue(ui->battery->GetPowerLevel());
}

void MainWindow::InitSignalSlots(void) noexcept
{
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [this](int _Value){
        ui->battery->SetPowerLevel(_Value);
        ui->label->setText(QString::asprintf("当前电量:%d%%", ui->battery->GetPowerLevel()));
    });
}

