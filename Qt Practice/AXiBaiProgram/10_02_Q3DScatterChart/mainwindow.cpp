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

    m_pc3DScatter = new Q3DScatter();

    pcSplitter->addWidget(ui->groupBox);
    pcSplitter->addWidget(createWindowContainer(m_pc3DScatter));
    this->setCentralWidget(pcSplitter);

    //使用默认坐标轴

    //设置数据显示效果
    constexpr qint32 nCount = 41;
    QScatter3DSeries *pcScatter3DSeries = new QScatter3DSeries(this);
    QScatterDataArray * pcScatterDataArray = new QScatterDataArray();

    pcScatter3DSeries->setItemSize(0.2);
    pcScatter3DSeries->setMesh(QAbstract3DSeries::MeshSphere);
    pcScatter3DSeries->setBaseColor(QColor(Qt::GlobalColor::green));
    pcScatter3DSeries->setMeshSmooth(true);
    pcScatter3DSeries->setItemLabelFormat("(@xLabel @yLabel @zLabel)");

    pcScatterDataArray->resize(nCount * nCount);

    QScatterDataItem *pcScatterDataItem = &((*pcScatterDataArray)[0]);

    //添加数据
    //墨西哥草帽,-10:0.5:10， nCount=41
    float x,y,z;
    int i,j;

    x=-10;
    for (i=1 ; i <=nCount; i++)
    {
        y=-10;
        for ( j =1; j <=nCount; j++)
        {
            z=qSqrt(x*x+y*y);
            if (z!=0)
                z=10*qSin(z)/z;
            else
                z=10;

            pcScatterDataItem->setPosition(QVector3D(x,z,y));
            pcScatterDataItem++;
            y+=0.5;
        }
        x+=0.5;
    }

    pcScatter3DSeries->dataProxy()->resetArray(pcScatterDataArray);

    m_pc3DScatter->addSeries(pcScatter3DSeries);
}

void MainWindow::InitSignalSlots(void) noexcept
{

}

void MainWindow::on_comboCamera_currentIndexChanged(int index)
{
    m_pc3DScatter->scene()->activeCamera()->setCameraPreset(Q3DCamera::CameraPreset(index));
}

void MainWindow::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value)

    float horizontal = ui->sliderH->value();
    float vertical = ui->sliderV->value();
    float zoom = ui->sliderZoom->value();

    m_pc3DScatter->scene()->activeCamera()->setCameraPosition(horizontal, vertical, zoom);
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
    m_pc3DScatter->activeTheme()->setType(Q3DTheme::Theme(index));
}


void MainWindow::on_cBoxBarStyle_currentIndexChanged(int index)
{
    QScatter3DSeries *pcBar3DSeries = m_pc3DScatter->seriesList()[0];
    pcBar3DSeries->setMesh(QAbstract3DSeries::Mesh(index));
}


void MainWindow::on_cBoxSelectionMode_currentIndexChanged(int index)
{
    m_pc3DScatter->setSelectionMode(QAbstract3DGraph::SelectionFlags(index));
}


void MainWindow::on_spinFontSize_valueChanged(int arg1)
{
    QFont cFont = m_pc3DScatter->activeTheme()->font();
    cFont.setPointSize(arg1);
    m_pc3DScatter->activeTheme()->setFont(cFont);
}


void MainWindow::on_btnBarColor_clicked()
{
    QScatter3DSeries *pcBar3DSeries = m_pc3DScatter->seriesList()[0];
    QColor cColor = pcBar3DSeries->baseColor();

    cColor = QColorDialog::getColor(cColor);
    if(cColor.isValid())
        pcBar3DSeries->setBaseColor(cColor);
}


void MainWindow::on_chkBoxBackground_stateChanged(int arg1)
{
    m_pc3DScatter->activeTheme()->setBackgroundEnabled(arg1);
}


void MainWindow::on_chkBoxGrid_stateChanged(int arg1)
{
    m_pc3DScatter->activeTheme()->setGridEnabled(arg1);
}


void MainWindow::on_chkBoxSmooth_stateChanged(int arg1)
{
    QScatter3DSeries *pcBar3DSeries = m_pc3DScatter->seriesList()[0];
    pcBar3DSeries->setMeshSmooth(arg1);
}


void MainWindow::on_chkBoxReflection_stateChanged(int arg1)
{
    m_pc3DScatter->setReflection(arg1);
}


void MainWindow::on_chkBoxReverse_stateChanged(int arg1)
{
    m_pc3DScatter->axisY()->setReversed(arg1);
}


void MainWindow::on_chkBoxItemLabel_stateChanged(int arg1)
{
    QScatter3DSeries *pcBar3DSeries = m_pc3DScatter->seriesList()[0];

    pcBar3DSeries->setItemLabelFormat("(@xLabel @yLabel @zLabel)");
    pcBar3DSeries->setItemLabelVisible(arg1);
}


void MainWindow::on_chkBoxAxisTitle_stateChanged(int arg1)
{
    m_pc3DScatter->axisX()->setTitleVisible(arg1);
    m_pc3DScatter->axisY()->setTitleVisible(arg1);
    m_pc3DScatter->axisZ()->setTitleVisible(arg1);
}


void MainWindow::on_chkBoxAxisBackground_stateChanged(int arg1)
{
    m_pc3DScatter->activeTheme()->setLabelBackgroundEnabled(arg1);
}

