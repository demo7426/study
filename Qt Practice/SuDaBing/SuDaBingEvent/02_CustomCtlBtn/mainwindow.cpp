#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

#include "MyButton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->myBtn01, &CMyButton::Pressed, this, [=](){
        QMessageBox::information(this, "提示信息", "按钮被点击");
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
