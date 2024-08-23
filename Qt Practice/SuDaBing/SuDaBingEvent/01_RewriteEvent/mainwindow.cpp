#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* ev)
{
    QMessageBox::StandardButton eRtnStatus = QMessageBox::question(this, "询问窗口", "是否关闭当前窗口");

    if(eRtnStatus == QMessageBox::Yes)
        ev->accept();
    else if(eRtnStatus == QMessageBox::No)
        ev->ignore();
}

void MainWindow::resizeEvent(QResizeEvent* ev)
{
    qDebug() << "oldSize: " << ev->oldSize() << "curSize: " << ev->size();
}


