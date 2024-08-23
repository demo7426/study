#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //测试QDateTime类
    QDateTime cQDateTime = QDateTime::currentDateTime();
    qDebug() << cQDateTime.toString("yyyy/MM/dd hh/mm/ss.zzz ap");

    QString qStrDate = cQDateTime.date().toString("yyyy-MM-dd");
    qDebug() << "DateQString: " << qStrDate;

    qDebug() << cQDateTime.time().toString("HH:mm:ss.zzz AP");
}

MainWindow::~MainWindow()
{
    delete ui;
}
