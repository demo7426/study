#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTabWidget>
#include <QDebug>
#include <QPushButton>

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

int MainWindow::Init()
{
    ui->addBtn->setDisabled(true);
    return 0;
}

void MainWindow::Connect()
{
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, [=](int _Index){
        qDebug() << QString("索引为 %1, 标签名为 %2 的标签界面被单击了").arg(_Index).arg(ui->tabWidget->tabText(_Index));
    });

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, [=](int _Index){
        qDebug() << QString("切换到了索引为 %1, 标签名为 %2 的标签界面\n").arg(_Index).arg(ui->tabWidget->tabText(_Index));
    });

    //连接TabWidget删除标签事件
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, [&](int _Index){
        m_queTabWidget.enqueue(ui->tabWidget->widget(_Index));
        m_queTabTitle.enqueue(ui->tabWidget->tabText(_Index));

        ui->addBtn->setDisabled(false);

        ui->tabWidget->removeTab(_Index);       //只是被移除，但标签界面指针对象没有被释放
    });

    connect(ui->addBtn, &QPushButton::clicked, this, [&](){
        ui->tabWidget->addTab(m_queTabWidget.dequeue(), m_queTabTitle.dequeue());

        //防止按钮被无效点击
        if(m_queTabWidget.empty())
            ui->addBtn->setDisabled(true);
    });
}

