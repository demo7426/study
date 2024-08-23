#include "mainwindow.h"
#include<QMenuBar>
#include<QToolBar>
#include<QStatusBar>
#include<QLabel>
#include<QDockWidget>
#include<QTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 400);
    this->setFixedSize(600, 400);

    //1、创建菜单栏 只能创建一个
    QMenuBar *bar = menuBar();
    setMenuBar(bar);

    //创建菜单
    QMenu *fileMenu = bar->addMenu("文件");
    QMenu *editMenu = bar->addMenu("编辑");

    //创建菜单项
    QAction *newAction =  fileMenu->addAction("新建");

    //添加分割线
    fileMenu->addSeparator();

    QAction *openAction =  fileMenu->addAction("打开");

    //2、工具栏 可以有多个
    QToolBar *toolbar = new QToolBar(this);
    addToolBar(Qt::LeftToolBarArea, toolbar);

    //设置只允许左右停靠
    toolbar->setAllowedAreas(Qt::LeftToolBarArea | Qt::RightToolBarArea);

    //设置浮动
    toolbar->setFloatable(false);

    //设置移动（总开关）
    toolbar->setMovable(false);

    //在工具栏中放入小部件
    toolbar->addAction(newAction);
    //添加分割线
    toolbar->addSeparator();
    toolbar->addAction(openAction);

    //状态栏 只能有一个
    QStatusBar *staBar = statusBar();
    setStatusBar(staBar);

    QLabel *label_1 = new QLabel("左侧提示信息", this);
    staBar->addWidget(label_1);

    QLabel *label_2 = new QLabel("右侧提示信息", this);
    staBar->addPermanentWidget(label_2);

    //铆接部件（浮动窗口） 可以有多个
    QDockWidget *dock = new QDockWidget("浮动窗口", this);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    //只允许左右停靠
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    //核心部件 只能有一个
    QTextEdit *edit = new QTextEdit(this);
    setCentralWidget(edit);
}

MainWindow::~MainWindow()
{
}

