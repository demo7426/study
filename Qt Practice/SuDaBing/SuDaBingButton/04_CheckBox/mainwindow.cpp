#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->wallPaperLabel->setTristate(true);      //设置标签复选框为三态按钮

    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connect()
{
    connect(ui->folkSongCheckBox, &QCheckBox::stateChanged, this, [](int _State){
        if(_State == Qt::Checked)
            qDebug() << "选择了民谣风格";
        else if(_State == Qt::Unchecked)
            qDebug() << "取消了民谣风格";
    });


    connect(ui->wallPaperAbstract, &QCheckBox::stateChanged, this, &MainWindow::ChangeWallPaper_LabelState);
    connect(ui->wallPaperAnimation, &QCheckBox::stateChanged, this, &MainWindow::ChangeWallPaper_LabelState);
    connect(ui->wallPaperAnimal, &QCheckBox::stateChanged, this, &MainWindow::ChangeWallPaper_LabelState);
    connect(ui->wallPaperMiddleAges, &QCheckBox::stateChanged, this, &MainWindow::ChangeWallPaper_LabelState);
    connect(ui->wallPaperInterCelebrity, &QCheckBox::stateChanged, this, &MainWindow::ChangeWallPaper_LabelState);

    connect(ui->wallPaperLabel, &QCheckBox::clicked, this, [this](bool _State){
        Qt::CheckState eState = Qt::Unchecked;
        if(_State == true)
           eState = Qt::Checked;

        ui->wallPaperAbstract->setCheckState(eState);
        ui->wallPaperAnimation->setCheckState(eState);
        ui->wallPaperAnimal->setCheckState(eState);
        ui->wallPaperMiddleAges->setCheckState(eState);
        ui->wallPaperInterCelebrity->setCheckState(eState);
    });
}

void MainWindow::ChangeWallPaper_LabelState(int _State)
{
    if(_State == Qt::Checked)
        ++m_nWallPaper_LabelNum;
    else if(_State == Qt::Unchecked)
        --m_nWallPaper_LabelNum;

    if(m_nWallPaper_LabelNum == 5)
        ui->wallPaperLabel->setCheckState(Qt::Checked);
    else if(m_nWallPaper_LabelNum == 0)
        ui->wallPaperLabel->setCheckState(Qt::Unchecked);
    else
        ui->wallPaperLabel->setCheckState(Qt::PartiallyChecked);
}
