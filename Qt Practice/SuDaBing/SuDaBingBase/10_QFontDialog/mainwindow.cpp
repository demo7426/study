#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFontDialog>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->selectFontBtn, &QPushButton::clicked, this, [=](){
        bool bOk = false;
        QFont cQFont("等线", 12, QFont::Bold);

#if 1
        QFont cQFont_Set = QFontDialog::getFont(&bOk, cQFont, this, "选择字体");
#else
        QFont cQFont_Set = QFontDialog::getFont(&bOk, this);
#endif

        //设置字体
        if(bOk)
            ui->fontLabel->setFont(cQFont_Set);// QApplication::setFont(cQFont_Set);该函数可以一次性设置程序全局字体

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
