/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.11.07
描  述:	实现多语言界面支持
备  注:
修改记录:

  1.  日期: 2024.11.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QSettings>

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

void MainWindow::InitUi() noexcept
{

}

void MainWindow::InitSignalSlots() noexcept
{

}

void MainWindow::on_actLang_CN_triggered()
{
    //中文界面
    qApp->removeTranslator(m_pcTrans);
    delete m_pcTrans;

    m_pcTrans=new QTranslator;
    m_pcTrans->load("16_01_QtLinguist_cn.qm");
    qApp->installTranslator(m_pcTrans);
    ui->retranslateUi(this);

    QSettings settings("WWB-Qt","16_01_QtLinguist"); //注册表键组
    settings.setValue("Language","CN"); //界面语言，汉语
}


void MainWindow::on_actLang_EN_triggered()
{
    //英文界面
    qApp->removeTranslator(m_pcTrans);
    delete m_pcTrans;

    m_pcTrans=new QTranslator;
    m_pcTrans->load("16_01_QtLinguist_en.qm");
    qApp->installTranslator(m_pcTrans);
    ui->retranslateUi(this);

    QSettings   settings("WWB-Qt","16_01_QtLinguist"); //注册表键组
    settings.setValue("Language","EN"); //界面语言，英语
}

