/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2026.05.21
描  述:	实现主窗口的数据交互和ui显示
备  注:
修改记录:

  1.  日期: 2026.05.21
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

    this->InitUi();
    this->InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUi() noexcept
{
    m_pcLogin_Form = new CLogin_Form(this);
    m_pcRegister_Dialog = new CRegister_Dialog(this);

    this->setCentralWidget(m_pcLogin_Form);

    this->setWindowTitle("登陆界面");
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(m_pcLogin_Form, &CLogin_Form::Clicked_Register, this, [=](){
        m_pcRegister_Dialog->show();
        this->hide();
    });

    connect(m_pcRegister_Dialog, &CRegister_Dialog::Clicked_Cancel, this, [=](){
        m_pcRegister_Dialog->hide();
        this->show();
    });
}

