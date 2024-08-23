#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ButterFly.h"
#include <QRandomGenerator>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    QScreen* pcQScreen = QGuiApplication::primaryScreen();      //获取主屏幕边界信息

    // 去边框
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    // 设置窗口透明
    setAttribute(Qt::WA_TranslucentBackground);

    // 窗口最大化显示
    showMaximized();

    for(int i = 0; i < 100; ++i)
    {
        CButterFly* pcButterFly = new CButterFly(this);
        pcButterFly->move(QRandomGenerator::global()->bounded(pcQScreen->geometry().right() - pcQScreen->geometry().left()),
                          QRandomGenerator::global()->bounded(pcQScreen->geometry().bottom() - pcQScreen->geometry().top()));

        pcButterFly->show();            //因为窗口透明，所以需要手动显示
    }
}



