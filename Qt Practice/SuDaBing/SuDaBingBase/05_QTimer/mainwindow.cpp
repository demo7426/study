#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QTime>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //测试QTimer定时器类

    QTimer* pcQTimer = new QTimer(this);
    pcQTimer->setTimerType(Qt::PreciseTimer);

    connect(ui->loopBtn, &QPushButton::clicked, this, [=](){
        if(pcQTimer->isActive())
        {
            ui->loopBtn->setText("start");
            pcQTimer->stop();
        }
        else
        {
            ui->loopBtn->setText("stop");
            pcQTimer->start(1000);      //启动定时器，每隔一段时间发出timeout延时信号
        }
    });

    connect(pcQTimer, &QTimer::timeout, this, [=](){
        QTime cQTime = QTime::currentTime();
        QString cQString = cQTime.toString("hh:mm:ss.zzz AP");
        ui->timeLabel->setText(cQString);
    });



    connect(ui->loopBtn_2, &QPushButton::clicked, this, [&](){
        //定时器只发出一次延时延时信号
        QTimer::singleShot(2000, this, [&](){
            QTime cQTime = QTime::currentTime();
            QString cQString = cQTime.toString("hh:mm:ss.zzz AP");
            ui->timeLabel_2->setText(cQString);
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
