#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QDebug>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //测试QTime类
#if 0
    QTime cQTime = QTime::currentTime();
    qDebug() << "hour: " << cQTime.hour() << " minute: " << cQTime.minute()
             << " second: " << cQTime.second() << " millisecond: " << cQTime.msec();

    qDebug() << cQTime.toString("hh:mm:ss.zzz AP");
#else
    QElapsedTimer cQElaTimer;
    cQElaTimer.start();

    for (int var = 0; var < 10000000; ++var) {
        int i = 0;
        i++;
    }

    qint64 llElapseTime = cQElaTimer.elapsed();
    qDebug() << "流逝的时间: " << llElapseTime << "ms";
#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}
