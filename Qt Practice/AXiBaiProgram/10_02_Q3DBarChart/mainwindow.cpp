/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.16
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.16
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QSplitter>
#include <Q3DBars>
#include <QValue3DAxis>
#include <QCategory3DAxis>
#include <QBar3DSeries>
#include <QFont>
#include <QColor>
#include <QColorDialog>

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
    QSplitter *pcSplitter = new QSplitter(Qt::Horizontal);

    m_pc3DBars = new Q3DBars();

    pcSplitter->addWidget(ui->groupBox);
    pcSplitter->addWidget(createWindowContainer(m_pc3DBars));
    this->setCentralWidget(pcSplitter);
}

void MainWindow::InitSignalSlots(void) noexcept
{
    //设置三维坐标轴

    QCategory3DAxis *pcCategory3DAxis_X = new QCategory3DAxis(this);
    QCategory3DAxis *pcCategory3DAxis_Y = new QCategory3DAxis(this);
    QValue3DAxis *pcQValue3DAxis_Z = new QValue3DAxis(this);

    QStringList cListStrRowTitle = { tr("Row01"), tr("Row02"), tr("Row03") };
    QStringList cListStrColumnTitle = { tr("Column01"), tr("Column02"), tr("Column03"), tr("Column04"), tr("Column05") };

    pcCategory3DAxis_X->setTitle(tr("Row"));
    pcCategory3DAxis_Y->setTitle(tr("Column"));
    pcQValue3DAxis_Z->setTitle(tr("Value"));

    pcCategory3DAxis_X->setTitleVisible(true);
    pcCategory3DAxis_Y->setTitleVisible(true);
    pcQValue3DAxis_Z->setTitleVisible(true);

    pcCategory3DAxis_X->setLabels(cListStrRowTitle);
    pcCategory3DAxis_Y->setLabels(cListStrColumnTitle);
    pcQValue3DAxis_Z->setRange(0, 10);

    m_pc3DBars->setRowAxis(pcCategory3DAxis_X);
    m_pc3DBars->setColumnAxis(pcCategory3DAxis_Y);
    m_pc3DBars->setValueAxis(pcQValue3DAxis_Z);

    //添加数据
    QBar3DSeries *pcBar3DSeries = new QBar3DSeries(this);
    QBarDataArray* pcQBarDataArray = new QBarDataArray();
    QBarDataRow *pcBarDataRow[] = { new QBarDataRow(), new QBarDataRow(), new QBarDataRow() };

    *(pcBarDataRow[0]) << 1 << 2 << 3 << 4 << 5;
    *(pcBarDataRow[1]) << 5 << 4 << 3 << 2 << 1;
    *(pcBarDataRow[2]) << 5 << 4 << 3 << 4 << 5;

    pcQBarDataArray->append(pcBarDataRow[0]);
    pcQBarDataArray->append(pcBarDataRow[1]);
    pcQBarDataArray->append(pcBarDataRow[2]);

    pcBar3DSeries->dataProxy()->resetArray(pcQBarDataArray);

    m_pc3DBars->addSeries(pcBar3DSeries);
}

void MainWindow::on_comboCamera_currentIndexChanged(int index)
{
    m_pc3DBars->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value)

    float horizontal = ui->sliderH->value();
    float vertical = ui->sliderV->value();
    float zoom = ui->sliderZoom->value();

    m_pc3DBars->scene()->activeCamera()->setCameraPosition(horizontal, vertical, zoom);
}


void MainWindow::on_sliderV_valueChanged(int value)
{
    Q_UNUSED(value)

    on_sliderH_valueChanged(0);
}


void MainWindow::on_sliderZoom_valueChanged(int value)
{
    Q_UNUSED(value)

    on_sliderH_valueChanged(0);
}


void MainWindow::on_cBoxTheme_currentIndexChanged(int index)
{
    m_pc3DBars->activeTheme()->setType(Q3DTheme::Theme(index));
}


void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QBar3DSeries *pcBar3DSeries = m_pc3DBars->seriesList()[0];
    pcBar3DSeries->setMesh(QAbstract3DSeries::Mesh(index));
}


void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    m_pc3DBars->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}


void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont cFont = m_pc3DBars->activeTheme()->font();
    cFont.setPointSize(arg1);
    m_pc3DBars->activeTheme()->setFont(cFont);
}


void MainWindow::on_btnBarColor_clicked()
{
    QBar3DSeries *pcBar3DSeries = m_pc3DBars->seriesList()[0];
    QColor cColor = pcBar3DSeries->baseColor();

    cColor = QColorDialog::getColor(cColor);
    if(cColor.isValid())
        pcBar3DSeries->setBaseColor(cColor);
}


void MainWindow::on_chkBoxBackground_stateChanged(int arg1)
{
    m_pc3DBars->activeTheme()->setBackgroundEnabled(arg1);
}


void MainWindow::on_chkBoxGrid_stateChanged(int arg1)
{
    m_pc3DBars->activeTheme()->setGridEnabled(arg1);
}


void MainWindow::on_chkBoxSmooth_stateChanged(int arg1)
{
    QBar3DSeries *pcBar3DSeries = m_pc3DBars->seriesList()[0];
    pcBar3DSeries->setMeshSmooth(arg1);
}


void MainWindow::on_chkBoxReflection_stateChanged(int arg1)
{
    m_pc3DBars->setReflection(arg1);
}


void MainWindow::on_chkBoxReverse_stateChanged(int arg1)
{
    m_pc3DBars->valueAxis()->setReversed(arg1);
}


void MainWindow::on_chkBoxItemLabel_stateChanged(int arg1)
{
    QBar3DSeries *pcBar3DSeries = m_pc3DBars->seriesList()[0];

    pcBar3DSeries->setItemLabelFormat("(@rowLabel, @colLabel):%.1f");
    pcBar3DSeries->setItemLabelVisible(arg1);
}


void MainWindow::on_chkBoxAxisTitle_stateChanged(int arg1)
{
    m_pc3DBars->rowAxis()->setTitleVisible(arg1);
    m_pc3DBars->columnAxis()->setTitleVisible(arg1);
    m_pc3DBars->valueAxis()->setTitleVisible(arg1);
}


void MainWindow::on_chkBoxAxisBackground_stateChanged(int arg1)
{
    m_pc3DBars->activeTheme()->setLabelBackgroundEnabled(arg1);
}

