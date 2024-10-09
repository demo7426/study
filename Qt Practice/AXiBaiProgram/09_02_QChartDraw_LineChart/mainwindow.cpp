/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.07
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QChart>
#include <QtMath>
#include <QFontDialog>
#include <QColorDialog>
#include <QSlider>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pendialog.h"

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
    InitChartView();
    RefreshChartViewData();
    RefreshDataStatus();
}

void MainWindow::InitSignalSlots(void) noexcept
{

}

void MainWindow::InitChartView() noexcept
{
    QChart *pcChart = new QChart();

    pcChart->setTitle(tr("简单函数曲线"));

    ui->chartView->setChart(pcChart);

    QLineSeries *pcLineSeries01 = new QLineSeries(this);
    QLineSeries *pcLineSeries02 = new QLineSeries(this);

    pcLineSeries01->setName(tr("sin近似曲线"));
    pcLineSeries02->setName(tr("cos近似曲线"));

    pcChart->addSeries(pcLineSeries01);
    pcChart->addSeries(pcLineSeries02);

    QValueAxis *pcValueAxis_X = new QValueAxis(this);
    QValueAxis *pcValueAxis_Y = new QValueAxis(this);

    pcValueAxis_X->setTitleText(tr("time(secs)"));
    pcValueAxis_Y->setTitleText(tr("Value(Dec)"));

    pcChart->setAxisX(pcValueAxis_X, pcLineSeries01);
    pcChart->setAxisX(pcValueAxis_X, pcLineSeries02);
    pcChart->setAxisY(pcValueAxis_Y, pcLineSeries01);
    pcChart->setAxisY(pcValueAxis_Y, pcLineSeries02);


    ui->chartView->setViewportUpdateMode(QChartView::FullViewportUpdate);           //避免折线图数据点缩放时留下的残留
}

void MainWindow::RefreshChartViewData() noexcept
{
    constexpr qreal dbMaxValue = 10;

    QLineSeries *pcLineSeries01 = dynamic_cast<QLineSeries*>(ui->chartView->chart()->series().at(0));
    QLineSeries *pcLineSeries02 = dynamic_cast<QLineSeries*>(ui->chartView->chart()->series().at(1));

    pcLineSeries01->clear();
    pcLineSeries02->clear();

    for (qreal i = 0; i < dbMaxValue; i+=0.1)
    {
        pcLineSeries01->append(i, rand() % 5 * 0.1 + sin(i));
        pcLineSeries02->append(i, rand() % 5 * 0.1 + cos(i));
    }

    QValueAxis *pcValueAxis_X = dynamic_cast<QValueAxis*>((ui->chartView->chart()->axes(Qt::Horizontal))[0]);
    QValueAxis *pcValueAxis_Y = dynamic_cast<QValueAxis*>((ui->chartView->chart()->axes(Qt::Vertical))[0]);

    pcValueAxis_X->setRange(0, dbMaxValue);
    pcValueAxis_Y->setRange(-2, 2);
}

void MainWindow::RefreshDataStatus()
{
    QChart *pcChart = ui->chartView->chart();
    QMargins cMargins = pcChart->margins();

    ui->editTitle->setText(pcChart->title());

    ui->spinMarginLeft->setValue(cMargins.left());
    ui->spinMarginRight->setValue(cMargins.right());
    ui->spinMarginTop->setValue(cMargins.top());
    ui->spinMarginBottom->setValue(cMargins.bottom());

    if(ui->radioSeries0->isChecked())
        m_pcCurLineSeries = dynamic_cast<QLineSeries*>((pcChart->series())[0]);
    else
        m_pcCurLineSeries = dynamic_cast<QLineSeries*>((pcChart->series())[1]);

    if(ui->radioX->isChecked())
    {
        m_pcCurValueAxis = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Horizontal))[0]);
        qDebug() << m_pcCurValueAxis->max();
        qDebug() << "X";
    }
    else
    {
        m_pcCurValueAxis = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Vertical))[0]);
        qDebug() << m_pcCurValueAxis->max();
        qDebug() << "Y";
    }

    ui->spinAxisMin->setValue(m_pcCurValueAxis->min());
    ui->spinAxisMax->setValue(m_pcCurValueAxis->max());
}


void MainWindow::on_actDraw_triggered()
{
    RefreshChartViewData();
}


void MainWindow::on_actZoomIn_triggered()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->zoom(1.1);
    // pcChart->setScale(pcChart->scale() + 0.1);
}


void MainWindow::on_actZoomOut_triggered()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->zoom(0.9);
    // pcChart->setScale(pcChart->scale() - 0.1);
}


void MainWindow::on_actZoomReset_triggered()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->zoomReset();
}


void MainWindow::on_btnSetTitle_clicked()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->setTitle(ui->editTitle->text());
}


void MainWindow::on_btnSetTitleFont_clicked()
{
    bool bIsOK = false;
    QChart *pcChart = ui->chartView->chart();

    QFont cFont = QFontDialog::getFont(&bIsOK, pcChart->titleFont(), this);

    if(bIsOK)
        pcChart->setTitleFont(cFont);
}


void MainWindow::on_radioButton_clicked()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setAlignment(Qt::AlignTop);
}


void MainWindow::on_radioButton_2_clicked()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setAlignment(Qt::AlignBottom);
}


void MainWindow::on_radioButton_3_clicked()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setAlignment(Qt::AlignLeft);
}


void MainWindow::on_radioButton_4_clicked()
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setAlignment(Qt::AlignRight);
}


void MainWindow::on_chkLegendVisible_stateChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setVisible(arg1);
}


void MainWindow::on_chkBoxLegendBackground_stateChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->legend()->setBackgroundVisible(arg1);
}


void MainWindow::on_btnLegendFont_clicked()
{
    bool bIsOK = false;
    QChart *pcChart = ui->chartView->chart();

    QFont cFont = QFontDialog::getFont(&bIsOK, pcChart->legend()->font(), this);

    if(bIsOK)
        pcChart->legend()->setFont(cFont);
}


void MainWindow::on_btnLegendlabelColor_clicked()
{
    QChart *pcChart = ui->chartView->chart();

    QColor cColor = QColorDialog::getColor(pcChart->legend()->labelColor());

    if(cColor.isValid())
        pcChart->legend()->setLabelColor(cColor);
}


void MainWindow::on_spinMarginLeft_valueChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    QMargins cMargins = pcChart->margins();

    cMargins.setLeft(arg1);
    pcChart->setMargins(cMargins);
}


void MainWindow::on_spinMarginRight_valueChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    QMargins cMargins = pcChart->margins();

    cMargins.setRight(arg1);
    pcChart->setMargins(cMargins);
}


void MainWindow::on_spinMarginTop_valueChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    QMargins cMargins = pcChart->margins();

    cMargins.setTop(arg1);
    pcChart->setMargins(cMargins);
}


void MainWindow::on_spinMarginBottom_valueChanged(int arg1)
{
    QChart *pcChart = ui->chartView->chart();
    QMargins cMargins = pcChart->margins();

    cMargins.setBottom(arg1);
    pcChart->setMargins(cMargins);
}


void MainWindow::on_cBoxAnimation_currentIndexChanged(int index)
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->setAnimationOptions((QChart::AnimationOptions)index);
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    QChart *pcChart = ui->chartView->chart();
    pcChart->setTheme((QChart::ChartTheme)index);
}


void MainWindow::on_radioSeries0_clicked()
{
    QChart *pcChart = ui->chartView->chart();

    m_pcCurLineSeries = dynamic_cast<QLineSeries*>((pcChart->series())[0]);
    ui->editSeriesName->setText(m_pcCurLineSeries->name());

    RefreshDataStatus();
}


void MainWindow::on_radioSeries1_clicked()
{
    QChart *pcChart = ui->chartView->chart();

    m_pcCurLineSeries = dynamic_cast<QLineSeries*>((pcChart->series())[1]);
    ui->editSeriesName->setText(m_pcCurLineSeries->name());

    RefreshDataStatus();
}


void MainWindow::on_chkSeriesVisible_stateChanged(int arg1)
{
    m_pcCurLineSeries->setVisible(arg1);
}


void MainWindow::on_chkPointVisible_stateChanged(int arg1)
{
    m_pcCurLineSeries->setPointsVisible(arg1);
}


void MainWindow::on_btnSeriesColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurLineSeries->color());

    if(cColor.isValid())
        m_pcCurLineSeries->setColor(cColor);
}


void MainWindow::on_chkPointLabelVisible_stateChanged(int arg1)
{
    if(ui->radioSeriesLabFormat0->isChecked())
        m_pcCurLineSeries->setPointLabelsFormat("@index: (@yPoint)");
    else if(ui->radioSeriesLabFormat1->isChecked())
        m_pcCurLineSeries->setPointLabelsFormat("@index: (@xPoint, @yPoint)");
    else
        m_pcCurLineSeries->setPointLabelsFormat("");

    m_pcCurLineSeries->setPointLabelsVisible(arg1);
}


void MainWindow::on_btnSeriesLabColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurLineSeries->pointLabelsColor());

    if(cColor.isValid())
        m_pcCurLineSeries->setPointLabelsColor(cColor);
}


void MainWindow::on_btnSeriesLabFont_clicked()
{
    bool bIsOK = false;
    QFont cFont = QFontDialog::getFont(&bIsOK, m_pcCurLineSeries->pointLabelsFont(), this);

    if(bIsOK)
        m_pcCurLineSeries->setPointLabelsFont(cFont);
}


void MainWindow::on_sliderSeriesOpacity_valueChanged(int value)
{
    QSlider* pcSlider = qobject_cast<QSlider*>(sender());

    m_pcCurLineSeries->setOpacity(value * 1.0 / (pcSlider->maximum() - pcSlider->minimum()));
}


void MainWindow::on_radioSeriesLabFormat0_clicked()
{
    on_chkPointLabelVisible_stateChanged(ui->chkPointLabelVisible->isChecked() ? 1: 0);
}


void MainWindow::on_radioSeriesLabFormat1_clicked()
{
    on_chkPointLabelVisible_stateChanged(ui->chkPointLabelVisible->isChecked() ? 1: 0);
}


void MainWindow::on_btnSeriesPen_clicked()
{
    bool bIsOk = false;
    QPen cPenCur;

    cPenCur = CPenDialog::GetPen(bIsOk, m_pcCurLineSeries->pen(), this);

    if(bIsOk)
        m_pcCurLineSeries->setPen(cPenCur);
}


void MainWindow::on_radioX_clicked()
{
    QChart *pcChart = ui->chartView->chart();

    m_pcCurValueAxis = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Horizontal))[0]);


    ui->spinAxisMin->setValue(m_pcCurValueAxis->min());
    ui->spinAxisMax->setValue(m_pcCurValueAxis->max());

    qDebug() << "X:" << m_pcCurValueAxis->min();
    qDebug() << "X:" << m_pcCurValueAxis->max();
}


void MainWindow::on_radioY_clicked()
{
    QChart *pcChart = ui->chartView->chart();

    m_pcCurValueAxis = dynamic_cast<QValueAxis*>((pcChart->axes(Qt::Vertical))[0]);

    ui->spinAxisMin->setValue(m_pcCurValueAxis->min());
    ui->spinAxisMax->setValue(m_pcCurValueAxis->max());

    qDebug() << "Y:" << m_pcCurValueAxis->min();
    qDebug() << "Y:" << m_pcCurValueAxis->max();
}


void MainWindow::on_spinAxisMin_valueChanged(double arg1)
{
    Q_UNUSED(arg1)

    if(m_pcCurValueAxis != nullptr)
        m_pcCurValueAxis->setRange(ui->spinAxisMin->value(), ui->spinAxisMax->value());
}


void MainWindow::on_spinAxisMax_valueChanged(double arg1)
{
    Q_UNUSED(arg1)

    on_spinAxisMin_valueChanged(0);
}

void MainWindow::on_chkBoxVisible_stateChanged(int arg1)
{
    m_pcCurValueAxis->setVisible(arg1);
}


void MainWindow::on_btnAxisSetTitle_clicked()
{
    m_pcCurValueAxis->setTitleText(ui->editAxisTitle->text());
}


void MainWindow::on_btnAxisSetTitleFont_clicked()
{
    bool bIsOK = false;
    QFont cFont = QFontDialog::getFont(&bIsOK, m_pcCurValueAxis->titleFont(), this);

    if(bIsOK)
        m_pcCurValueAxis->setTitleFont(cFont);
}


void MainWindow::on_pushButton_clicked()
{
    m_pcCurValueAxis->setLabelFormat(ui->editAxisLabelFormat->text());
}


void MainWindow::on_btnAxisLabelColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurValueAxis->labelsColor());

    if(cColor.isValid())
        m_pcCurValueAxis->setLabelsColor(cColor);
}


void MainWindow::on_btnAxisLabelFont_clicked()
{
    bool bIsOK = false;
    QFont cFont = QFontDialog::getFont(&bIsOK, m_pcCurValueAxis->labelsFont(), this);

    if(bIsOK)
        m_pcCurValueAxis->setLabelsFont(cFont);
}


void MainWindow::on_chkBoxLabelsVisible_stateChanged(int arg1)
{
    m_pcCurValueAxis->setLabelsVisible(arg1);
}


void MainWindow::on_chkGridLineVisible_stateChanged(int arg1)
{
    m_pcCurValueAxis->setGridLineVisible(arg1);
}


void MainWindow::on_btnGridLineColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurValueAxis->gridLineColor());

    if(cColor.isValid())
        m_pcCurValueAxis->setGridLineColor(cColor);
}


void MainWindow::on_pushButton_10_clicked()
{
    bool bIsOk = false;
    QPen cPenCur;

    cPenCur = CPenDialog::GetPen(bIsOk, m_pcCurValueAxis->gridLinePen(), this);

    if(bIsOk)
        m_pcCurValueAxis->setGridLinePen(cPenCur);
}


void MainWindow::on_spinTickCount_valueChanged(int arg1)
{
    m_pcCurValueAxis->setTickCount(arg1);
}


void MainWindow::on_chkAxisLineVisible_stateChanged(int arg1)
{
    m_pcCurValueAxis->setLineVisible(arg1);
}


void MainWindow::on_btnAxisLinePen_clicked()
{
    bool bIsOk = false;
    QPen cPenCur;

    cPenCur = CPenDialog::GetPen(bIsOk, m_pcCurValueAxis->linePen(), this);

    if(bIsOk)
        m_pcCurValueAxis->setLinePen(cPenCur);
}


void MainWindow::on_btnAxisLinePenColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurValueAxis->linePenColor());

    if(cColor.isValid())
        m_pcCurValueAxis->setLinePenColor(cColor);
}


void MainWindow::on_spinMinorTickCount_valueChanged(int arg1)
{
    m_pcCurValueAxis->setMinorTickCount(arg1);
}


void MainWindow::on_chkMinorTickVisible_stateChanged(int arg1)
{
    m_pcCurValueAxis->setMinorGridLineVisible(arg1);
}


void MainWindow::on_btnMinorColor_clicked()
{
    QColor cColor = QColorDialog::getColor(m_pcCurValueAxis->minorGridLineColor());

    if(cColor.isValid())
        m_pcCurValueAxis->setMinorGridLineColor(cColor);
}


void MainWindow::on_btnMinorPen_clicked()
{
    bool bIsOk = false;
    QPen cPenCur;

    cPenCur = CPenDialog::GetPen(bIsOk, m_pcCurValueAxis->minorGridLinePen(), this);

    if(bIsOk)
        m_pcCurValueAxis->setMinorGridLinePen(cPenCur);
}


void MainWindow::on_chkBoxAxisTitle_stateChanged(int arg1)
{
    m_pcCurValueAxis->setTitleVisible(arg1);
}

