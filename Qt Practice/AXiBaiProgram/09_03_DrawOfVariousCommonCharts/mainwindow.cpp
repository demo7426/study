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

#include <QTime>
#include <QtMath>

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
    InitTreeWidgetData(ui->treeWidget);

    ui->tableView->setAlternatingRowColors(true);
    // ui->tableView->resizeColumnsToContents();
    ui->treeWidget->resizeColumnToContents(0);

    for (int i = 0; i < ui->treeWidget->columnCount(); ++i) {
        ui->treeWidget->headerItem()->setTextAlignment(i, Qt::AlignHCenter);
    }
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->actGenData, &QAction::triggered, this, [this](){
        RefreshTableViewData(ui->tableView);
    });

    connect(ui->actTongJi, &QAction::triggered, this, [this](){
        SurveyTableViewDataToTreeWidget(ui->tableView, ui->treeWidget);
    });
}

void MainWindow::InitTableViewData(QTableView *_pTableView)
{
    if(_pTableView == nullptr)
        return;

    constexpr qint32 nRowCount = 10;                //行数
    constexpr qint32 nColumnCount = 5;              //列数
    QList<QString> clistHorizontalHeaderData;

    QStandardItem* pcStandardItem = nullptr;

    m_pcStandardItemModel = new QStandardItemModel(this);
    m_pcItemSelectionModel = new QItemSelectionModel(m_pcStandardItemModel);

    _pTableView->setModel(m_pcStandardItemModel);
    _pTableView->setSelectionModel(m_pcItemSelectionModel);

    srand(QTime::currentTime().msec());

    clistHorizontalHeaderData.clear();
    clistHorizontalHeaderData.append(tr("姓名"));
    clistHorizontalHeaderData.append(tr("数学"));
    clistHorizontalHeaderData.append(tr("语文"));
    clistHorizontalHeaderData.append(tr("英语"));
    clistHorizontalHeaderData.append(tr("平均分"));

    m_pcStandardItemModel->setRowCount(nRowCount);
    m_pcStandardItemModel->setColumnCount(nColumnCount);

    for (quint32 i = 0; i < clistHorizontalHeaderData.size(); ++i)
        m_pcStandardItemModel->setHeaderData(i, Qt::Horizontal, clistHorizontalHeaderData[i], Qt::DisplayRole);

    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i) {
        qint32 nColumnNo = 0;               //列序号
        qreal dbAverageScore = 0;           //平均分
        qreal dbSumScore = 0;               //总分

        pcStandardItem = new QStandardItem(QString::asprintf("学生 %03d", i + 1));
        pcStandardItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_pcStandardItemModel->setItem(i, nColumnNo++, pcStandardItem);

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        pcStandardItem = new QStandardItem(QString::asprintf("%.0f", dbAverageScore));
        pcStandardItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_pcStandardItemModel->setItem(i, nColumnNo++, pcStandardItem);

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        pcStandardItem = new QStandardItem(QString::asprintf("%.0f", dbAverageScore));
        pcStandardItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_pcStandardItemModel->setItem(i, nColumnNo++, pcStandardItem);

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        pcStandardItem = new QStandardItem(QString::asprintf("%.0f", dbAverageScore));
        pcStandardItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_pcStandardItemModel->setItem(i, nColumnNo++, pcStandardItem);

        dbAverageScore = dbSumScore / 3.0;
        pcStandardItem = new QStandardItem(QString::asprintf("%.2f", dbAverageScore));
        pcStandardItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        m_pcStandardItemModel->setItem(i, nColumnNo++, pcStandardItem);
    }
}

void MainWindow::RefreshTableViewData(QTableView *_pTableView)
{
    if(_pTableView == nullptr)
        return;

    QModelIndex cModelIndex;
    QStandardItem* pcStandardItem = nullptr;

    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i) {
        qint32 nColumnNo = 1;               //列序号(只需要刷新分数，所以从1开始)
        qreal dbAverageScore = 0;           //平均分
        qreal dbSumScore = 0;               //总分

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnNo++);
        pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndex);
        pcStandardItem->setData(dbAverageScore, Qt::DisplayRole);

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnNo++);
        pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndex);
        pcStandardItem->setData(dbAverageScore, Qt::DisplayRole);

        dbAverageScore = rand() % 50 + 50;
        dbSumScore += dbAverageScore;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnNo++);
        pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndex);
        pcStandardItem->setData(dbAverageScore, Qt::DisplayRole);

        dbAverageScore = dbSumScore / 3.0;
        cModelIndex = m_pcStandardItemModel->index(i, nColumnNo++);
        pcStandardItem = m_pcStandardItemModel->itemFromIndex(cModelIndex);
        pcStandardItem->setData(QString::asprintf("%.2f", dbAverageScore), Qt::DisplayRole);
    }
}

void MainWindow::InitTreeWidgetData(QTreeWidget *_pTreeWidget)
{
    if(_pTreeWidget == nullptr)
        return;

}

void MainWindow::SurveyTableViewDataToTreeWidget(QTableView *_pTableView, QTreeWidget *_pTreeWidget)
{
    if(_pTableView == nullptr || _pTreeWidget == nullptr)
        return;

    QModelIndex cModelIndex;
    QTreeWidgetItem * pcCurTreeWidgetItem = nullptr;

    for (int i = 1; i < m_pcStandardItemModel->columnCount(); ++i) {
        qint32 nRowNo = 0;
        qreal dbAverageScore = 0;               //平均分
        qreal dbSumScore = 0;                   //总分
        qreal dbMinScore = 100, dbMaxScore = 0;
        qint32 nScoreRanges[5] = { 0 };         //分数区间,依次是60以下,60~69分,70~79分,80~89分,90分以上

        //计算数据
        for (int j = 0; j < m_pcStandardItemModel->rowCount(); ++j) {
            cModelIndex = m_pcStandardItemModel->index(j, i);
            dbAverageScore = cModelIndex.data(Qt::DisplayRole).toFloat();

            dbSumScore += dbAverageScore;
            dbMinScore = qMin(dbMinScore, dbAverageScore);
            dbMaxScore = qMax(dbMaxScore, dbAverageScore);

            dbAverageScore < 60? nScoreRanges[0] += 1: 0;
            dbAverageScore >= 60 && dbAverageScore < 70? nScoreRanges[1] += 1: 0;
            dbAverageScore >= 70 && dbAverageScore < 80? nScoreRanges[2] += 1: 0;
            dbAverageScore >= 80 && dbAverageScore < 90? nScoreRanges[3] += 1: 0;
            dbAverageScore >= 90? nScoreRanges[4] += 1: 0;
        }

        dbAverageScore = dbSumScore / m_pcStandardItemModel->rowCount();

        //显示数据
        for (quint32 j = 0; j < sizeof nScoreRanges / sizeof(nScoreRanges[0]); ++j)     //设置区间分数范围人数
        {
            pcCurTreeWidgetItem = _pTreeWidget->topLevelItem(nRowNo++);
            pcCurTreeWidgetItem->setData(i, Qt::DisplayRole, nScoreRanges[j]);
        }

        pcCurTreeWidgetItem = _pTreeWidget->topLevelItem(nRowNo++);
        pcCurTreeWidgetItem->setData(i, Qt::DisplayRole, QString::asprintf("%.2f", dbAverageScore));

        pcCurTreeWidgetItem = _pTreeWidget->topLevelItem(nRowNo++);
        pcCurTreeWidgetItem->setData(i, Qt::DisplayRole, dbMaxScore);

        pcCurTreeWidgetItem = _pTreeWidget->topLevelItem(nRowNo++);
        pcCurTreeWidgetItem->setData(i, Qt::DisplayRole, dbMinScore);
    }
}



















