/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.08
描  述:	使用样式表自定义界面
备  注:
修改记录:

  1.  日期: 2024.11.08
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QFile>
#include <QMessageBox>

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
    this->setWindowFlag(Qt::SplashScreen);

    ui->lineEdit->setProperty("required", "true");

    QFile cFile("uiDesign.css");

    if(!cFile.open(QIODeviceBase::OpenModeFlag::ReadOnly | QIODeviceBase::OpenModeFlag::Text))
    {
        QMessageBox::warning(this, tr("警告窗口"), tr("界面设计文件加载失败"));
        exit(0);
    }

    this->setStyleSheet(QString::fromLatin1(cFile.readAll()));

    cFile.close();
}


void MainWindow::InitSignalSlots(void) noexcept
{

}
