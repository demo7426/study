/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.20
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

    if(m_pcDialogSetSize != nullptr)
        delete m_pcDialogSetSize;

    if(m_pcStandardItemModel != nullptr)
        delete m_pcStandardItemModel;

    if(m_pcItemSelectionModel != nullptr)
        delete m_pcItemSelectionModel;
}

void MainWindow::InitUi() noexcept
{
    this->setCentralWidget(ui->tableView);

    m_pcDialogSetSize = new CDialogSetSize(this);
    m_pcStandardItemModel = new QStandardItemModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel);

    ui->tableView->setModel(m_pcStandardItemModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->actTab_SetSize, &QAction::triggered, this, &MainWindow::ShowDialogSetSize);

    connect(m_pcDialogSetSize, &CDialogSetSize::RowAndColumnChanged, this, &MainWindow::SetTableViewSize);
}

void MainWindow::ShowDialogSetSize()
{
    m_pcDialogSetSize->SetRowAndColumnCount(m_pcStandardItemModel->rowCount(), m_pcStandardItemModel->columnCount());

    ui->actTab_SetSize->setEnabled(false);
    m_pcDialogSetSize->show();
}

void MainWindow::SetTableViewSize(quint32 _RowCount, quint32 _ColumnCount, bool _IsFlag)
{
    if(_IsFlag)
    {
        m_pcStandardItemModel->setRowCount(_RowCount);
        m_pcStandardItemModel->setColumnCount(_ColumnCount);
    }

    ui->actTab_SetSize->setEnabled(true);
}
