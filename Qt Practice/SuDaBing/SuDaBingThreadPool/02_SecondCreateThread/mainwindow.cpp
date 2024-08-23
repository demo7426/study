#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QThread>

#include "Generate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{

}

void MainWindow::Connect()
{
    QThread *pcQThread = new QThread;

    CGenerate* pcGenerate = new CGenerate(new CBubbleDataSort());

    connect(this, &MainWindow::SetRandomNum, pcGenerate, &CGenerate::Run);

    connect(ui->startBtn, &QPushButton::clicked, this, [=]() noexcept {
        pcGenerate->moveToThread(pcQThread);
        pcQThread->start();

        emit SetRandomNum(20000);
    });

    connect(pcGenerate, &CGenerate::sendRandomNum, this, [=](QVector<int> cQVecInfo) noexcept {
        for(auto item : cQVecInfo)
            ui->randomListWidget->addItem(QString::number(item));
    });

    connect(pcGenerate, &CGenerate::sendSortNum, this, [=](QVector<int> cQVecInfo) noexcept {
        for(auto item : cQVecInfo)
            ui->sortListWidget->addItem(QString::number(item));
    });

    connect(this, &MainWindow::destroyed, this, [=](){
        pcQThread->quit();
        pcQThread->wait();
        pcQThread->deleteLater();

        pcGenerate->deleteLater();
    });
}


