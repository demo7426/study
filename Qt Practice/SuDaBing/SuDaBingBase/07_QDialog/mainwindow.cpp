#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>

#include"mydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connect()
{
    connect(ui->showModalDialogBtn, &QPushButton::clicked, this, [](){
        CMyDialog cMyDialog;
        int nRet = cMyDialog.exec();
        qDebug() << QString("取消模态对话框的返回值 = %1。").arg(nRet);
    });

}
