#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "testwidget.h"
#include "testdialog.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //基于QWidget类的ui显示有无边框、有边框两种模式
#if 1
    //有边框（为独立ui时，需要调用show方法）
    CTestWidget* pcTestWidget = new CTestWidget();
    pcTestWidget->show();
#else
    //无边框（内嵌到父类窗口中，推测父类会主动调用子类的show方法）
    CTestWidget* pcTestWidget = new CTestWidget(this);
#endif

    //基于QDialog类的ui没有内嵌功能
#if 1
    CTestDialog* pcTestDialog = new CTestDialog();
    pcTestDialog->show();                           //非模态显示
#else
    CTestDialog* pcTestDialog = new CTestDialog();
    pcTestDialog->exec();                           //模态显示
#endif

    qDebug() << "第一条日志" << ": 1000.";

    QString strMsg = QString("%1是个%2,%3").arg("赵子龙").arg("将军").arg("毫无疑问。");
    qDebug() << strMsg;
}

MainWindow::~MainWindow()
{
    delete ui;
}
