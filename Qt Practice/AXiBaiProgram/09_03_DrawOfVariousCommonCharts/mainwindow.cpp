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
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLineSeries>
#include <QPieSeries>
#include <QPieSlice>
#include <QStackedBarSeries>
#include <QPercentBarSeries>
#include <QScatterSeries>
#include <QSplineSeries>

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
    //初始化
    InitTableViewData(ui->tableView);
    InitBarChart(ui->chartViewBar);
    InitPieChart(ui->chartViewPie);
    InitStackBarChart(ui->chartViewStackedBar);
    InitPercentBarChart(ui->chartViewPercentBar);
    InitScatterBarChart(ui->chartViewScatter);

    SurveyTableViewDataToTreeWidget(ui->tableView, ui->treeWidget);

    ui->tableView->setAlternatingRowColors(true);
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

    connect(ui->btnBuildBarChart, &QPushButton::clicked, this, [this](){
        RefreshBarChartData(ui->chartViewBar);
    });

    connect(ui->btnDrawPieChart, &QPushButton::clicked, this, [this](){
        RefreshPieChartData(ui->chartViewPie);
    });
}

void MainWindow::InitTableViewData(QTableView *_pTableView)
{
    if(_pTableView == nullptr)
        return;

    constexpr qint32 nRowCount = 20;                //行数
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

void MainWindow::InitBarChart(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = new QChart();
    QBarSeries *pcBarSeries = new QBarSeries(this);
    QLineSeries *pcLineSeries = new QLineSeries(this);
    QBarCategoryAxis *pcBarCategoryAxis_X = new QBarCategoryAxis(this);
    QValueAxis *pcValueAxis_Y = new QValueAxis(this);
    QList<QBarSet*> cListBarSet = { new QBarSet("数学"), new QBarSet("语文"), new QBarSet("英语") };      //柱状图用于用于存放数据的集合

    pcChart->setTitle(tr("学生-分数(柱状图)"));
    pcChart->setAnimationOptions(QChart::AllAnimations);
    _pChartView->setChart(pcChart);

    pcBarSeries->append(cListBarSet);
    pcLineSeries->setName(tr("平均分"));

    pcChart->addSeries(pcBarSeries);
    pcChart->addSeries(pcLineSeries);

    pcValueAxis_Y->setTitleText(tr("分数"));

    pcChart->setAxisX(pcBarCategoryAxis_X, pcBarSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcBarSeries);
    pcChart->setAxisX(pcBarCategoryAxis_X, pcLineSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcLineSeries);

    _pChartView->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::RefreshBarChartData(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = _pChartView->chart();
    QBarSeries *pcBarSeries = dynamic_cast<QBarSeries*>((pcChart->series())[0]);
    QLineSeries *pcLineSeries = dynamic_cast<QLineSeries*>((pcChart->series())[1]);
    QBarCategoryAxis *pcBarCategoryAxis_X = dynamic_cast<QBarCategoryAxis*>((pcChart->axes(Qt::Horizontal))[0]);
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Vertical))[0]);
    QList<QBarSet*> cListBarSet;
    QStringList cStrListName;

    //清空饼图数据
    cStrListName.clear();
    pcLineSeries->clear();
    cListBarSet.clear();
    cListBarSet = pcBarSeries->barSets();
    foreach (auto item, cListBarSet) {
        item->remove(0, item->count());
    }

    //取出数据
    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i)
    {
        QModelIndex cModelIndex = m_pcStandardItemModel->index(i, 0);
        cStrListName.append(cModelIndex.data(Qt::DisplayRole).toString());

        cModelIndex = m_pcStandardItemModel->index(i, 1);
        cListBarSet[0]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 2);
        cListBarSet[1]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 3);
        cListBarSet[2]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 4);
        pcLineSeries->append(i, cModelIndex.data(Qt::DisplayRole).toFloat());
    }

    //设置坐标轴
    pcBarCategoryAxis_X->setCategories(cStrListName);
    pcValueAxis_Y->setRange(0, 100);
}

void MainWindow::InitPieChart(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = new QChart();
    QPieSeries *pcPieSeries = new QPieSeries(this);

    pcChart->setTitle(tr("饼图"));
    pcChart->setAnimationOptions(QChart::AllAnimations);

    _pChartView->setChart(pcChart);
    pcChart->addSeries(pcPieSeries);

    _pChartView->setRenderHints(QPainter::Antialiasing);
    pcChart->legend()->setAlignment(Qt::AlignRight);
    pcChart->setTheme((QChart::ChartTheme)ui->cBoxTheme->currentText().toInt());
}

void MainWindow::RefreshPieChartData(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = _pChartView->chart();
    QPieSeries *pcPieSeries = dynamic_cast<QPieSeries*>((pcChart->series())[0]);
    QPieSlice* pcPieSlice = nullptr;
    QTreeWidgetItem *pcTreeWidgetItem = nullptr;
    qint32 nCurSubjectType = 0;                     //当前学科
    constexpr qint32 nPieSlicesCount = 5;           //饼图块数量

    nCurSubjectType = ui->cBoxCourse->currentIndex() + 1;

    pcPieSeries->clear();
    pcPieSeries->setHoleSize(ui->spinHoleSize->value());
    pcPieSeries->setPieSize(ui->spinPieSize->value());

    //向饼图添加数据
    for (int i = 0; i < nPieSlicesCount; ++i)
    {
        qint32 nCurPersonCount = 0;         //当前人数

        pcTreeWidgetItem = ui->treeWidget->topLevelItem(i);
        nCurPersonCount = pcTreeWidgetItem->data(nCurSubjectType, Qt::DisplayRole).toReal();

        //向饼图添加数据，饼图会自动生成块
        pcPieSeries->append(tr(""), nCurPersonCount);
    }

    //设置饼图中的块属性
    for (int i = 0; i < nPieSlicesCount; ++i)
    {
        pcTreeWidgetItem = ui->treeWidget->topLevelItem(i);

        pcPieSlice = pcPieSeries->slices()[i];
        pcPieSlice->setLabelVisible(true);
        pcPieSlice->setLabel(QString::asprintf("%s: %0.0f人, %0.1f%", pcTreeWidgetItem->text(0).toStdString().data(), pcPieSlice->value(), pcPieSlice->percentage() * 100));
        connect(pcPieSlice, &QPieSlice::hovered, pcPieSlice, &QPieSlice::setExploded);
    }
}

void MainWindow::InitStackBarChart(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = new QChart();
    QStackedBarSeries *pcBarSeries = new QStackedBarSeries(this);
    QBarCategoryAxis *pcBarCategoryAxis_X = new QBarCategoryAxis(this);
    QValueAxis *pcValueAxis_Y = new QValueAxis(this);
    QList<QBarSet*> cListBarSet = { new QBarSet("数学"), new QBarSet("语文"), new QBarSet("英语") };      //柱状图用于用于存放数据的集合

    pcChart->setTitle(tr("学生-分数(栈柱状图)"));
    pcChart->setAnimationOptions(QChart::AllAnimations);
    _pChartView->setChart(pcChart);

    pcBarSeries->append(cListBarSet);

    pcChart->addSeries(pcBarSeries);

    pcValueAxis_Y->setTitleText(tr("分数"));

    pcChart->setAxisX(pcBarCategoryAxis_X, pcBarSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcBarSeries);

    _pChartView->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::RefreshStackBarChartData(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = _pChartView->chart();
    QStackedBarSeries *pcBarSeries = dynamic_cast<QStackedBarSeries*>((pcChart->series())[0]);
    QBarCategoryAxis *pcBarCategoryAxis_X = dynamic_cast<QBarCategoryAxis*>((pcChart->axes(Qt::Horizontal))[0]);
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Vertical))[0]);
    QList<QBarSet*> cListBarSet;
    QStringList cStrListName;

    //清空饼图数据
    cStrListName.clear();
    cListBarSet.clear();
    cListBarSet = pcBarSeries->barSets();
    foreach (auto item, cListBarSet) {
        item->remove(0, item->count());
    }

    pcBarSeries->setLabelsVisible(true);            //设置百分比

    //取出数据
    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i)
    {
        QModelIndex cModelIndex = m_pcStandardItemModel->index(i, 0);
        cStrListName.append(cModelIndex.data(Qt::DisplayRole).toString());

        cModelIndex = m_pcStandardItemModel->index(i, 1);
        cListBarSet[0]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 2);
        cListBarSet[1]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 3);
        cListBarSet[2]->append(cModelIndex.data(Qt::DisplayRole).toFloat());
    }

    //设置坐标轴
    pcBarCategoryAxis_X->setCategories(cStrListName);
    pcValueAxis_Y->setRange(0, 300);
}

void MainWindow::InitPercentBarChart(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = new QChart();
    QPercentBarSeries *pcBarSeries = new QPercentBarSeries(this);
    QBarCategoryAxis *pcBarCategoryAxis_X = new QBarCategoryAxis(this);
    QValueAxis *pcValueAxis_Y = new QValueAxis(this);
    QList<QBarSet*> cListBarSet = { new QBarSet("数学"), new QBarSet("语文"), new QBarSet("英语") };      //柱状图用于用于存放数据的集合

    pcChart->setTitle(tr("学生-分数(百分比柱状图)"));
    pcChart->setAnimationOptions(QChart::AllAnimations);
    _pChartView->setChart(pcChart);

    pcBarSeries->append(cListBarSet);

    pcChart->addSeries(pcBarSeries);

    pcValueAxis_Y->setTitleText(tr("分数"));

    pcChart->setAxisX(pcBarCategoryAxis_X, pcBarSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcBarSeries);

    _pChartView->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::RefreshPercentBarChartData(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = _pChartView->chart();
    QPercentBarSeries *pcBarSeries = dynamic_cast<QPercentBarSeries*>((pcChart->series())[0]);
    QBarCategoryAxis *pcBarCategoryAxis_X = dynamic_cast<QBarCategoryAxis*>((pcChart->axes(Qt::Horizontal))[0]);
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Vertical))[0]);
    QList<QBarSet*> cListBarSet;
    QStringList cStrListName;

    //清空饼图数据
    cStrListName.clear();
    cListBarSet.clear();
    cListBarSet = pcBarSeries->barSets();
    foreach (auto item, cListBarSet) {
        item->remove(0, item->count());
    }

    pcBarSeries->setLabelsVisible(true);            //设置百分比

    //取出数据
    for (int i = 0; i < m_pcStandardItemModel->rowCount(); ++i)
    {
        QModelIndex cModelIndex = m_pcStandardItemModel->index(i, 0);
        cStrListName.append(cModelIndex.data(Qt::DisplayRole).toString());

        cModelIndex = m_pcStandardItemModel->index(i, 1);
        cListBarSet[0]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 2);
        cListBarSet[1]->append(cModelIndex.data(Qt::DisplayRole).toFloat());

        cModelIndex = m_pcStandardItemModel->index(i, 3);
        cListBarSet[2]->append(cModelIndex.data(Qt::DisplayRole).toFloat());
    }

    //设置坐标轴
    pcBarCategoryAxis_X->setCategories(cStrListName);
    pcValueAxis_Y->setRange(0, 100);
}

void MainWindow::InitScatterBarChart(QChartView *_pChartView)
{
    QChart *pcChart = new QChart();
    QScatterSeries *pcScatterSeries = new QScatterSeries(this);         //散点线条
    QSplineSeries* pcSplineSeries = new QSplineSeries(this);            //曲线线条
    QValueAxis* pcValueAxis_X = new QValueAxis(this);
    QValueAxis* pcValueAxis_Y = new QValueAxis(this);

    pcChart->setTitle(tr("散点图"));

    pcScatterSeries->setName(tr("散点数据"));
    pcSplineSeries->setName(tr("样条数据"));

    pcValueAxis_X->setTitleText(tr("横轴"));
    pcValueAxis_Y->setTitleText(tr("纵轴"));

    pcChart->setAnimationOptions(QChart::AllAnimations);

    _pChartView->setChart(pcChart);
    _pChartView->setRenderHints(QPainter::Antialiasing);

    pcChart->addSeries(pcScatterSeries);
    pcChart->addSeries(pcSplineSeries);

    pcChart->setAxisX(pcValueAxis_X, pcScatterSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcScatterSeries);
    pcChart->setAxisX(pcValueAxis_X, pcSplineSeries);
    pcChart->setAxisY(pcValueAxis_Y, pcSplineSeries);
}

void MainWindow::RefreshtScatterBarChartData(QChartView *_pChartView)
{
    if(_pChartView == nullptr)
        return;

    QChart *pcChart = _pChartView->chart();
    QScatterSeries *pcScatterSeries = dynamic_cast<QScatterSeries*>(pcChart->series().at(0));         //散点线条
    QSplineSeries* pcSplineSeries = dynamic_cast<QSplineSeries*>(pcChart->series().at(1));           //曲线线条
    QValueAxis* pcValueAxis_X = dynamic_cast<QValueAxis*>(pcChart->axes(Qt::Horizontal).at(0));
    QValueAxis* pcValueAxis_Y = dynamic_cast<QValueAxis*>(pcChart->axes(Qt::Vertical).at(0));

    pcScatterSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    pcScatterSeries->setBorderColor(Qt::GlobalColor::red);
    pcScatterSeries->setMarkerSize(6);

    pcScatterSeries->clear();
    pcSplineSeries->clear();

    for (int i = 0; i < 40; ++i)
    {
        qint32 nRandomNum = rand() % 10;
        pcScatterSeries->append(QPointF(i, nRandomNum));
        pcSplineSeries->append(QPointF(i, nRandomNum));
    }

    pcValueAxis_X->setRange(-2, 42);
    pcValueAxis_Y->setRange(-2, 12);
}

void MainWindow::on_spinHoleSize_valueChanged(double arg1)
{
    QChart *pcChart = ui->chartViewPie->chart();
    QPieSeries *pcPieSeries = dynamic_cast<QPieSeries*>((pcChart->series())[0]);
    pcPieSeries->setHoleSize(arg1);
}


void MainWindow::on_spinPieSize_valueChanged(double arg1)
{
    QChart *pcChart = ui->chartViewPie->chart();
    QPieSeries *pcPieSeries = dynamic_cast<QPieSeries*>((pcChart->series())[0]);
    pcPieSeries->setPieSize(arg1);
}


void MainWindow::on_cBoxCourse_currentIndexChanged(int index)
{
    RefreshPieChartData(ui->chartViewPie);
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    QChart *pcChart = ui->chartViewPie->chart();
    pcChart->setTheme((QChart::ChartTheme)index);
}


void MainWindow::on_btnBuildStackedBar_clicked()
{
    RefreshStackBarChartData(ui->chartViewStackedBar);
}


void MainWindow::on_btnPercentBar_clicked()
{
    RefreshPercentBarChartData(ui->chartViewPercentBar);
}


void MainWindow::on_btnScatter_clicked()
{
    RefreshtScatterBarChartData(ui->chartViewScatter);
}

