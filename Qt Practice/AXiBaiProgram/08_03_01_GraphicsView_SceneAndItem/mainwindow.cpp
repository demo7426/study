/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.01
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.01
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QGraphicsItem>
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
    this->resize(800, 600);
    setPalette(QPalette(Qt::GlobalColor::white));
    setAutoFillBackground(true);

    for (int i = 0; i < sizeof(m_pcLabels) / sizeof(m_pcLabels[0]); ++i) {
        m_pcLabels[i] = new QLabel(this);
    }

    ui->statusbar->addWidget(m_pcLabels[0], 1);
    ui->statusbar->addWidget(m_pcLabels[1], 1);
    ui->statusbar->addWidget(m_pcLabels[2], 1);
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->graphicsView, &CMy_GraphicsView::SendMouseMoveSignal, this, &MainWindow::PrintViewAndScenePoint);
    connect(ui->graphicsView, &CMy_GraphicsView::SendMouseLeftClickSignal, this, [this](QPoint _Point){
        QPointF cPointFScene = ui->graphicsView->mapToScene(_Point);
        QGraphicsItem* m_pcGraphicsItem = ui->graphicsView->itemAt(_Point);

        if(m_pcGraphicsItem == nullptr)
            return;

        QPointF cPointFItem = m_pcGraphicsItem->mapFromScene(cPointFScene);
        m_pcLabels[2]->setText(QString::asprintf("Item坐标:(%.0f, %.0f)", cPointFItem.x(), cPointFItem.y()));
    });
}

void MainWindow::PrintViewAndScenePoint(QPoint _Point)
{
    m_pcLabels[0]->setText(QString::asprintf("View坐标:(%d, %d)", _Point.x(), _Point.y()));
    m_pcLabels[1]->setText(QString::asprintf("Scene坐标:(%.0f, %.0f)", ui->graphicsView->mapToScene(_Point).x(),
                                             ui->graphicsView->mapToScene(_Point).y()));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    QRect cRectView = ui->graphicsView->rect();
    QRectF cRectFScene = ui->graphicsView->sceneRect();

    ui->labViewSize->setText(QString::asprintf("Graphics View坐标，左上角坐标总是（%d,%d），宽度= %d，长度= %d",
                                               cRectView.left(), cRectView.top(), cRectView.width(), cRectView.height()));

    ui->LabSceneRect->setText(QString::asprintf("QGraphicsView::sceneRect=(L, T, W, H) = (%.0f, %.0f, %.0f, %.0f)",
                                                cRectFScene.left(), cRectFScene.top(), cRectFScene.width(), cRectFScene.height()));

    QMainWindow::resizeEvent(event);
}
