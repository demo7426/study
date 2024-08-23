#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CLoginDialog cLoginDialog;

    cLoginDialog.setWindowTitle("登录窗口");
    cLoginDialog.setWindowIcon(QIcon(":/new/prefix1/img/android-chrome-512x512.png"));
    cLoginDialog.setFixedSize(258, 267);
    cLoginDialog.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
