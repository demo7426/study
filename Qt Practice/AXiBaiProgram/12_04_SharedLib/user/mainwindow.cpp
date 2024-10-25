/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.25
描  述:	实现主界面显示
备  注:
修改记录:

  1.  日期: 2024.10.25
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sharedlib.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMessageBox::information(this, tr("计算结果"), QString::asprintf("%d", CSharedLib::Add(1, 2)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
