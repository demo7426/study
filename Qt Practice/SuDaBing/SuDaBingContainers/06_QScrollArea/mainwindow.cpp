#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qlabel.h"
#include "QBoxLayout"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    //显示较大的图片
    /*QLabel *pcQLabel = new QLabel(this);
    pcQLabel->setFixedWidth(400);
    pcQLabel->setPixmap(QPixmap(":/new/prefix1/img/1.jpg"));

    ui->scrollArea->setAlignment(Qt::AlignHCenter);
    ui->scrollArea->setWidget(pcQLabel);*/

    //显示多个窗口
    QBoxLayout *pcQBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    for (int i = 1; i < 4; ++i) {
        QLabel* pcQLabel = new QLabel(this);
        pcQLabel->setPixmap(QPixmap(QString(":/new/prefix1/img/%1.jpg").arg(i)));
        pcQBoxLayout->addWidget(pcQLabel, Qt::AlignLeft | Qt::AlignVCenter);
    }

    pcQBoxLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    QWidget *pcQWidget = new QWidget(this);
    pcQWidget->setLayout(pcQBoxLayout);

    ui->scrollArea->setWidget(pcQWidget);
}
