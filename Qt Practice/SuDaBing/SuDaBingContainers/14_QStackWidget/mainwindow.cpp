#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(1);

    connect(ui->calendarPageBtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentIndex(0);
    });

    connect(ui->dialPageBtn, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->pageDial);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
