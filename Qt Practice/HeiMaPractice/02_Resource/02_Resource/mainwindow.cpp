#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDialog>
#include<QMessageBox>
#include<QDebug>
#include<QColorDialog>
#include<QFileDialog>
#include<QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //资源文件添加 语法 ": + 前缀名 + 文件名称"
    ui->actionnew->setIcon(QIcon(":/new/prefix1/icon/1.png"));
    ui->actionopen->setIcon(QIcon(":/new/prefix1/icon/2.png"));

    //模态窗口
    connect(ui->actionnew, &QAction::triggered, this, [=](){

        QDialog dlg;
        dlg.resize(300, 200);
        dlg.exec();
    });

    //非模态对话框
    connect(ui->actionopen, &QAction::triggered, this,[=](){
        QDialog* dlg = new QDialog(this);
        dlg->resize(300, 200);
        dlg->show();

        //在关闭对话框时销毁创建的对象
        dlg->setAttribute(Qt::WA_DeleteOnClose);
    });

    //QMessageBox对话框
    //错误提示对话框
    connect(ui->actionerror, &QAction::triggered, this, [=](){

        QMessageBox::critical(this, "错误", "输入信息错误");
    });

    //信息提示对话框
    connect(ui->actioninfomation, &QAction::triggered, this, [=](){

        QMessageBox::information(this, "信息", "信息有误");
    });

    //询问提示对话框
    connect(ui->actionquestion, &QAction::triggered, this, [=](){

        if(QMessageBox::Save == QMessageBox::question(this, "询问", "是否打印信息", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Save))
        {
            qDebug()<<"点击的是保存";
        }
        else
        {
            qDebug()<<"点击的是取消";
        }
    });

    //警告提示对话框
    connect(ui->actionwarning, &QAction::triggered, this, [=](){

        QMessageBox::warning(this, "警告", "warning");
    });

    //颜色对话框
    connect(ui->actioncolorDialog, &QAction::triggered, this, [=](){

        QColor color = QColorDialog::getColor(Qt::red);
        qDebug() << color.red() << color.green() << color.blue();
    });

    //文件对话框
    connect(ui->actionfileDialog, &QAction::triggered, this, [=](){

        QString fileName = QFileDialog::getOpenFileName(this, "打开文件", "C:/");
        qDebug() << fileName.toUtf8().data();
    });

    //字体对话框
    connect(ui->actionfontDialog, &QAction::triggered, this, [=](){

        bool bflag;
        QFont font = QFontDialog::getFont(&bflag, QFont("华文彩云", 36));
        qDebug() << "字体" <<font.family().toUtf8().data() <<
                    "字号" << font.pointSize() <<
                    "是否加粗" << font.bold() << "是否倾斜" << font.italic();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

