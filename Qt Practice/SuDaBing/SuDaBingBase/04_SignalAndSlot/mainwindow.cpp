#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //标准信号槽的使用
    connect(ui->closeBtn, &QPushButton::clicked, this, &QMainWindow::close);

    //自定义信号、槽函数
    m_pcBoyFriend = new CBoyFriend;
    m_pcGirlFriend = new CGirlFriend;

    connect(ui->hungryBtn, &QPushButton::clicked, this, &MainWindow::HungryBtnSlot);

#if 0//Qt 5写法
    void (CGirlFriend::*girlFun01)() = &CGirlFriend::Hungry;
    void (CGirlFriend::*girlFun02)(QString) = &CGirlFriend::Hungry;
    void (CBoyFriend::*boyFunc01)() = &CBoyFriend::Eat;
    void (CBoyFriend::*boyFunc02)(QString) = &CBoyFriend::Eat;

    connect(m_pcGirlFriend, girlFun01, m_pcBoyFriend, boyFunc01);
    connect(m_pcGirlFriend, girlFun02, m_pcBoyFriend, boyFunc02);
#else//Qt 4之前的写法
    connect(m_pcGirlFriend, SIGNAL(Hungry()), m_pcBoyFriend, SLOT(Eat()));
    connect(m_pcGirlFriend, SIGNAL(Hungry(QString)), m_pcBoyFriend, SLOT(Eat(QString)));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HungryBtnSlot()
{
    emit m_pcGirlFriend->Hungry();
    emit m_pcGirlFriend->Hungry("海底捞");
}
