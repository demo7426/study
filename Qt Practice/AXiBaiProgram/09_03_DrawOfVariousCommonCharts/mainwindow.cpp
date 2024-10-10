/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.10
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.10
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

void MainWindow::InitUi() noexcept
{
    InitTableViewData(ui->tableView);
    RefreshTableViewData(ui->tableView);
}

void MainWindow::InitSignalSlots() noexcept
{

}

void MainWindow::InitTableViewData(QTableView *_pTableView)
{
    if(_pTableView == nullptr)
        return;

    m_pcStandardItemModel = new QStandardItemModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel);

    _pTableView->setModel(m_pcStandardItemModel);
    _pTableView->setSelectionModel(m_pcItemSelectionModel);


}

void MainWindow::RefreshTableViewData(QTableView *_pTableView)
{

}
