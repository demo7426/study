/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.05
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.05
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_graphicsview.h"


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
    this->setPalette(QPalette(Qt::GlobalColor::white));
    this->setAutoFillBackground(true);
    this->resize(800, 600);

    this->setCentralWidget(ui->graphicsView);

    for (quint32 i = 0; i < sizeof(m_pcLabel_Status) / sizeof(m_pcLabel_Status[0]); ++i)
    {
        m_pcLabel_Status[i] = new QLabel(this);
        ui->statusbar->addWidget(m_pcLabel_Status[i], 1);
    }

}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->actItem_Rect, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Rect);
    });

    connect(ui->actItem_Ellipse, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Ellipse);
    });

    connect(ui->actItem_Circle, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Circle);
    });

    connect(ui->actItem_Triangle, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Triangle);
    });

    connect(ui->actItem_Polygon, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Trapezium);
    });

    connect(ui->actItem_Line, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Line);
    });

    connect(ui->actItem_Text, &QAction::triggered, ui->graphicsView, [this](){
        ui->graphicsView->NewAndShowGraph(CMy_GraphicsView::GRAPH_TYPE::Text);
    });

    connect(ui->graphicsView, &CMy_GraphicsView::SendMouseMoveSignal, this, [this](QPoint _Point){
        QPointF cPointF_Scene = ui->graphicsView->mapToScene(_Point);

        m_pcLabel_Status[0]->setText(QString::asprintf("View坐标: (%d, %d)", _Point.x(), _Point.y()));
        m_pcLabel_Status[1]->setText(QString::asprintf("Scene坐标: (%.0f, %.0f)", cPointF_Scene.x(), cPointF_Scene.y()));
    });

    connect(ui->graphicsView, &CMy_GraphicsView::SendMouseLeftClickSignal, this, [this](QPointF _Point){
        m_pcLabel_Status[2]->setText(QString::asprintf("Item坐标: (%.0f, %.0f)", _Point.x(), _Point.y()));
    });

    connect(ui->graphicsView, &CMy_GraphicsView::SendItemMsg, this, [this](QString _Msg){
        m_pcLabel_Status[3]->setText(_Msg);
    });

    connect(ui->actZoomIn, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::ZoomInItems);
    connect(ui->actZoomOut, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::ZoomOutItems);
    connect(ui->actRestore, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::ZoomResetItems);
    connect(ui->actRotateLeft, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::RotateLeftItems);
    connect(ui->actRotateRight, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::RotateRightItems);
    connect(ui->actEdit_Front, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::PreposItems);
    connect(ui->actEdit_Back, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::PostItems);
    connect(ui->actGroup, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::CompositeItems);
    connect(ui->actGroupBreak, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::SplitItems);
    connect(ui->actEdit_Delete, &QAction::triggered, ui->graphicsView, &CMy_GraphicsView::DeleteItems);

}


