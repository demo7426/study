#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openInputDialogBtn, &QPushButton::clicked, this, [this](){
        double dbSalary = QInputDialog::getDouble(this, tr("调查："), tr("期望工资为："), 5000, 0, 200000, 2);
        QMessageBox::information(this, tr("期望工资为："), QString::number(dbSalary));

        int nStationNum = QInputDialog::getInt(this, tr("工位参数："), tr("工位数量："), 4, 0, 16, 2);
        QMessageBox::about(this, tr("工位数量："), QString::number(nStationNum));

        QStringList cQStrList_Fruit  = {"苹果", "雪梨", "糯米蕉", "黄桃", "椰子"};
        QString cQStrFruit = QInputDialog::getItem(this, tr("水果信息："), tr("水果种类："), cQStrList_Fruit, 2, false);
        QMessageBox::information(this, tr("水果种类："), cQStrFruit);

        QString cQStrPassword = QInputDialog::getText(this, tr("设置密码："), tr("密码："), QLineEdit::Password, tr("123"));
        QMessageBox::information(this, tr("设置的密码为："), cQStrPassword);

        QString cQStrPosey = QInputDialog::getMultiLineText(this, tr("信息："), tr("一首诗歌："),"床前明月光\n疑是地上霜");
        QMessageBox::information(this, tr("诗歌为："), cQStrPosey);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
