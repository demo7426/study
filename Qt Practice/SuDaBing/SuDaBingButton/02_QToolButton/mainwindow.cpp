#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolButton>
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
    delete this->m_pQAction_MenuBtn01;
    delete this->m_pQAction_ActionBtn;
}

void MainWindow::Init()
{
    ui->normalBtn->setIcon(QIcon(":/new/prefix1/img/apple-touch-icon.png"));
    ui->normalBtn->setText("normalBtn");
    ui->normalBtn->setIconSize(QSize(50, 50));
    ui->normalBtn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    ui->checkBtn->setCheckable(true);

    QMenu *pcQMenu = new QMenu(this);
    m_pQAction_MenuBtn01 = pcQMenu->addAction("哈密瓜");
    pcQMenu->addAction("西瓜");
    pcQMenu->addAction("凤梨");
    pcQMenu->addAction("水蜜桃");
    ui->menuBtn->setMenu(pcQMenu);

    m_pQAction_ActionBtn = new QAction(QIcon(":/new/prefix1/img/android-chrome-192x192.png"), "普通按钮", this);
    ui->actionBtn->setDefaultAction(m_pQAction_ActionBtn);
    ui->actionBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->arrowBtn->setArrowType(Qt::UpArrow);
    ui->arrowBtn->setText("向上小箭头按钮");

    ui->popMenuBtn->setMenu(pcQMenu);
    ui->popMenuBtn->setPopupMode(QToolButton::MenuButtonPopup);
}

void MainWindow::Connect()
{
    connect(ui->normalBtn, &QToolButton::clicked, this, [](){
        qDebug() << "普通按钮进行了点击操作";
    });

    connect(ui->checkBtn, &QToolButton::toggled, this, [](bool _Checked){
        qDebug() << "check按钮进行了点击操作，当前按钮状态为" << _Checked;
    });

    connect(m_pQAction_MenuBtn01, &QAction::triggered, this, [=](){
        qDebug() << QString("您选择了%1水果").arg(m_pQAction_MenuBtn01->text());
    });

    connect(ui->actionBtn, &QToolButton::triggered, this, [](QAction* _pQAction){
        _pQAction->setText("被点击一次");
        _pQAction->setIcon(QIcon(":/new/prefix1/img/apple-touch-icon.png"));
    });

    connect(ui->popMenuBtn, &QToolButton::clicked, this, [](){
        qDebug() << "popMenuBtn 发出clicked信号";
    });
}
