#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate qDate = QDate::currentDate();
    qDebug() << "Year: " << qDate.year() << "month: " << qDate.month() << "day: " << qDate.day();

    QString qStrDate = qDate.toString("yyyy-MM-dd");
    qDebug() << "DateQString: " << qStrDate;
}

MainWindow::~MainWindow()
{
    delete ui;
}
