#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThreadPool>
#include <QThread>

#include"Generate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "主线程Id为： " << QThread::currentThreadId();

    CGenerate* pcGenerate = new CGenerate();
    QThreadPool::globalInstance()->start(pcGenerate);
}

MainWindow::~MainWindow()
{
    delete ui;
}
