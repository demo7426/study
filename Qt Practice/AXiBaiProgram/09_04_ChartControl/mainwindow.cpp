/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.14
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.14
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QtMath>
#include <QTime>
#include <QLegendMarker>

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
    srand(QTime::currentTime().msec());

    this->setCentralWidget(ui->chartView);

    InitChartView_Line(ui->chartView);
    RefreshChartView_Line(ui->chartView);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    QList<QLegendMarker *> cListLegendMarker = ui->chartView->chart()->legend()->markers();

    foreach (auto item, cListLegendMarker) {
        connect(item, &QLegendMarker::clicked, this, [this](){
            QLegendMarker *pcLegendMarker = qobject_cast<QLegendMarker*>(sender());
            QBrush cBrush = pcLegendMarker->labelBrush();
            QColor cColor = cBrush.color();

            if(pcLegendMarker->series()->isVisible())
                cColor.setAlphaF(0.7);
            else
                cColor.setAlphaF(1);
            cBrush.setColor(cColor);
            pcLegendMarker->setLabelBrush(cBrush);

            pcLegendMarker->series()->setVisible(!pcLegendMarker->series()->isVisible());
            pcLegendMarker->setVisible(true);

        });
    }
}

void MainWindow::InitChartView_Line(QChartView *pcChartView)
{
    QChart *pcChart = new QChart();
    QLineSeries *pcLineSeries_Sin = new QLineSeries(this);
    QLineSeries *pcLineSeries_Cos = new QLineSeries(this);
    QValueAxis *pcValueAxis_X = new QValueAxis(this);
    QValueAxis *pcValueAxis_Y = new QValueAxis(this);

    pcChart->setTitle(tr("函数曲线图"));

    pcChartView->setChart(pcChart);
    pcChart->addSeries(pcLineSeries_Sin);
    pcChart->addSeries(pcLineSeries_Cos);

    pcChart->setAxisX(pcValueAxis_X, pcLineSeries_Sin);
    pcChart->setAxisY(pcValueAxis_Y, pcLineSeries_Sin);
    pcChart->setAxisX(pcValueAxis_X, pcLineSeries_Cos);
    pcChart->setAxisY(pcValueAxis_Y, pcLineSeries_Cos);

    pcChartView->setRenderHints(QPainter::Antialiasing);
}

void MainWindow::RefreshChartView_Line(QChartView *pcChartView)
{
    QChart *pcChart = pcChartView->chart();
    QLineSeries *pcLineSeries_Sin = dynamic_cast<QLineSeries*>(pcChart->series().at(0));
    QLineSeries *pcLineSeries_Cos = dynamic_cast<QLineSeries*>(pcChart->series().at(1));
    QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>(pcChart->axes(Qt::Horizontal).at(0));
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>(pcChart->axes(Qt::Vertical).at(0));

    for (qreal i = 0; i < 10; i+=0.1) {
        pcLineSeries_Sin->append(QPointF(i, qSin(i) + rand() % 2 * 0.1 - 0.1));
        pcLineSeries_Cos->append(QPointF(i, qCos(i) + rand() % 2 * 0.1 - 0.1));
    }

    pcLineSeries_Sin->setName(tr("Sin类似曲线"));
    pcLineSeries_Cos->setName(tr("Cos类似曲线"));

    pcValueAxis_X->setTitleText(tr("横轴"));
    pcValueAxis_Y->setTitleText(tr("纵轴"));

    pcValueAxis_X->setRange(0, 10);
    pcValueAxis_Y->setRange(-2, 2);
}
