#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QIcon cQIcon(R"(../08_QMessageBox/favicon.ico)");
    setWindowIcon(cQIcon);

    connect(ui->messageBtn, &QPushButton::clicked, this, [=](){
        QMessageBox::about(this, "提示窗口", "这是一个简易窗口");

        QMessageBox::critical(this, "错误窗口", "程序出现错误");
        QMessageBox::information(this, "提示信息", "程序出现一些提示");
        QMessageBox::question(this, "问题窗口", "是否保存文件", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save);
        QMessageBox::warning(this, "警告窗口", "程序出现警告错误");
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
