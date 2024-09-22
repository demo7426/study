/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.23
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "userwidget.h"

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
    this->setCentralWidget(ui->tabWidget);
    ui->tabWidget->setVisible(false);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->actWidgetInsite, &QAction::triggered, this, &MainWindow::AddEmbeddedWidget);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::ResponseTabClose);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter cPainter(this);
    cPainter.drawPixmap(QRect(0, ui->toolBar->height(), this->width(), this->height() - ui->toolBar->height() - ui->statusbar->height()),
                        QPixmap(":/images/images/png/preview.jpg"));
}

void MainWindow::AddEmbeddedWidget()
{
    CUserWidget *pcUserWidget = new CUserWidget(this);

    qint32 nCurIndex = ui->tabWidget->addTab(pcUserWidget, QString::asprintf("嵌入式widget:%u", m_unWidgetIndex++));
    ui->tabWidget->setVisible(true);
    ui->tabWidget->setCurrentIndex(nCurIndex);
}

void MainWindow::ResponseTabClose(int index)
{
    QWidget *pcWidget = nullptr;

    if(ui->tabWidget->count() == 1) //保证删除所有的嵌入式窗体后显示图片
    {
        ui->tabWidget->setVisible(false);
    }

    pcWidget = ui->tabWidget->widget(index);
    ui->tabWidget->removeTab(index);

    delete pcWidget;
    pcWidget = nullptr;

    m_unWidgetIndex = 0;
}
