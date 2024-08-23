#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitMainWindow();
    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MoveCurMainWindow(int _X, int _Y)
{
    QRect cQRect = geometry();

    cQRect.moveTo(cQRect.x() + _X, cQRect.y() + _Y);

    setGeometry(cQRect);
}

void MainWindow::PrintfCurMainWindowInfo()
{
    QRect cQRect = geometry();

    qDebug() << QString("X = %1; Y = %2; Width = %3; Height = %4").
                arg(cQRect.x()).arg(cQRect.y()).arg(cQRect.width()).arg(cQRect.height());
}

void MainWindow::RandomModifyCurMainWindowInfo()
{
    srand(time(NULL));

    QRect cQRect = geometry();

    cQRect.setRect(100 + rand() % 400, 100 + rand() % 400, 400 + rand() % 400, 200 + rand() % 400);
    setGeometry(cQRect);
}

void MainWindow::ModifyIconOrTitle()
{
    static int nfreq = 0;
    //设置窗口图标
    QIcon cQIcon(R"(../06_QWidget/favicon.ico)");
    setWindowIcon(cQIcon);

    //设置窗口标题
    setWindowTitle(QString("06_QWidget_第%1次").arg(++nfreq));
}

void MainWindow::InitMainWindow()
{
#if 0
    //设置当前窗口缩放范围
    setMinimumSize(100, 100);
    setMaximumSize(800, 600);
#else
    //设置当前窗口固定大小
    //setFixedSize(400, 300);
#endif

    //设置窗口图标
    QIcon cQIcon(R"(../06_QWidget/favicon.ico)");
    setWindowIcon(cQIcon);

    //设置窗口标题
    setWindowTitle("06_QWidget");

    //设置当前窗口菜单栏显示策略
    setContextMenuPolicy(Qt::CustomContextMenu);
}

void MainWindow::Connect() noexcept
{
    connect(ui->moveBtn, &QPushButton::clicked, this, [=](){
        this->MoveCurMainWindow(10,10);
    });

    connect(ui->getWindowInfoBtn, &QPushButton::clicked, this, [=](){
        this->PrintfCurMainWindowInfo();
    });

    connect(ui->modifyBtn, &QPushButton::clicked, this, [=](){
        this->RandomModifyCurMainWindowInfo();
    });

    connect(ui->modifyIconOrTitleBtn, &QPushButton::clicked, this, &MainWindow::ModifyIconOrTitle);

    connect(this, &QWidget::windowTitleChanged, this, [](){
        qDebug() << "通过QWidget自带的图标或标题修改信号表明MainWindow 当前图标或标题被修改了";
    });

    connect(this, &QWidget::customContextMenuRequested, this, [](){
        //仅供显示，不做保存
        QMenu cQMenu;
        cQMenu.addMenu("新建文件");
        cQMenu.addMenu("打开文件");
        cQMenu.addMenu("添加文件");
        cQMenu.exec(QCursor::pos());
    });
}
