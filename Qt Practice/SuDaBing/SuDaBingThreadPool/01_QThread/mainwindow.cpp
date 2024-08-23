#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>

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
    CGenerate* pcGenerate = new CGenerate(new CQuickDataSort(this), this);

    connect(this, &MainWindow::SetRandomNum, pcGenerate, &CGenerate::SetGenerateNum);

    connect(ui->startBtn, &QPushButton::clicked, this, [=]() noexcept {
        emit SetRandomNum(20000);

        pcGenerate->start();
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
        pcGenerate->quit();
        pcGenerate->wait();
        pcGenerate->deleteLater();
    });
}


