#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    ui->normalBtn->setIcon(QIcon(":/new/prefix1/favicon"));
    ui->normalBtn->setText("normalBtn");
    ui->normalBtn->setIconSize(QSize(12, 12));

    ui->checkBtn->setCheckable(true);

    QMenu *pcQMenu = new QMenu(this);
    m_pQAction_MenuBtn01 = pcQMenu->addAction("哈密瓜");
    pcQMenu->addAction("西瓜");
    pcQMenu->addAction("凤梨");
    pcQMenu->addAction("水蜜桃");
    ui->menuBtn->setMenu(pcQMenu);
}

void MainWindow::Connect()
{
    connect(ui->normalBtn, &QPushButton::clicked, this, [](){
        qDebug() << "普通按钮进行了点击操作";
    });

    connect(ui->checkBtn, &QPushButton::toggled, this, [](bool _Checked){
        qDebug() << "check按钮进行了点击操作，当前按钮状态为" << _Checked;
    });

    connect(m_pQAction_MenuBtn01, &QAction::triggered, this, [=](){
        qDebug() << QString("您选择了%1水果").arg(m_pQAction_MenuBtn01->text());
    });
}
