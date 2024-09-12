/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.12
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.12
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

    if(m_pcStandardItemModel != nullptr)
        delete m_pcStandardItemModel;

    if(m_pcItemSelectionModel != nullptr)
        delete m_pcItemSelectionModel;

    if(m_pcLabel_FilePath != nullptr)
        delete m_pcLabel_FilePath;

    if(m_pcLabel_Pos != nullptr)
        delete m_pcLabel_Pos;

    if(m_pcLabel_Text != nullptr)
        delete m_pcLabel_Text;
}

void MainWindow::InitUi() noexcept
{
    m_pcStandardItemModel = new QStandardItemModel(10, 6, this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel);                //将QItemSelectionModel和QStandardItemModel联系起来

    ui->tableView->setModel(m_pcStandardItemModel);
    ui->tableView->setSelectionModel(m_pcItemSelectionModel);

    m_pcLabel_FilePath = new QLabel("当前路径:", this);
    m_pcLabel_Pos = new QLabel("当前位置:", this);
    m_pcLabel_Text = new QLabel("当前内容:", this);

    ui->statusbar->addWidget(m_pcLabel_FilePath, 1);
    ui->statusbar->addWidget(m_pcLabel_Pos, 1);
    ui->statusbar->addWidget(m_pcLabel_Text, 1);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(m_pcItemSelectionModel, &QItemSelectionModel::currentChanged, this, &MainWindow::CurrentChanged);
}

void MainWindow::CurrentChanged(const QModelIndex &_Current, const QModelIndex &_Previous)
{
    Q_UNUSED(_Previous);

    if(!_Current.isValid())
        return;

    QStandardItem* pcStandardItem = m_pcStandardItemModel->itemFromIndex(_Current);
    QFont cFont = pcStandardItem->font();

    cFont.setBold(true);
    pcStandardItem->setFont(cFont);
    ui->actFontBold->setChecked(true);

    m_pcLabel_Pos->setText(QString::asprintf("当前位置: %d行 %d列", _Current.row(), _Current.column()));
}
