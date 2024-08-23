#include "widget.h"
#include "ui_widget.h"
#include<QFileDialog>
#include<QFile>
#include<QString>
#include<QDebug>
#include<QMessageBox>
#include<QTextCodec>
#include<QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
       QString filePath = QFileDialog::getOpenFileName(this, "打开文件", NULL);//打开项目下文件夹

       if(filePath.isEmpty())
       {
           QMessageBox::warning(this, "警告窗口", "文件路径不能为空");
       }
       else
       {
           ui->lineEdit->setText(filePath);

           //QTextCodec *codec = QTextCodec::codecForName("gbk");//文件编码格式类

           QFile file(filePath);

           //写文件
           file.open(QIODevice::Append);
           file.write("追加内容！！！");
           file.close();


           //读文件
           file.open(QIODevice::ReadOnly);//打开文件

           //读取文件默认为utf-8的格式
           QByteArray byteArray = file.readAll();//读取文件内容

           //ui->textEdit->setText(codec->toUnicode(byteArray));
           ui->textEdit->setText(byteArray);

           file.close();

           //读取文件信息
           QFileInfo info(filePath);

           qDebug() << "文件后缀名："<< info.suffix() << "文件大小：" << info.size() <<
                      "文件名：" << info.fileName() << "文件路径：" << info.filePath();
           qDebug() << "创建日期：" << info.created().toString("yyyy-MM-dd hh:mm:ss") <<
                     "最后修改日期：" << info.lastModified().toString("yyyy-MM-dd hh:mm:ss");
       }

    });
}

Widget::~Widget()
{
    delete ui;
}

