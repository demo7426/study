#include "mydialog.h"
#include "ui_mydialog.h"
#include <QPushButton>
#include <QDebug>

CMyDialog::CMyDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CMyDialog)
{
    ui->setupUi(this);

    Connect();
}

CMyDialog::~CMyDialog()
{
    delete ui;
}

void CMyDialog::Connect()
{
    connect(ui->acceptBtn, &QPushButton::clicked, this, [=](){
        this->accept();
    });

    connect(ui->rejectBtn, &QPushButton::clicked, this, [=](){
        this->reject();
    });

    connect(ui->doneBtn, &QPushButton::clicked, this, [=](){
        this->done(10);
    });

    //连接取消当前模态对话框发出的信号
    //发出什么信号只和形参有关系
    connect(this, &QDialog::accepted, this, [](){
        qDebug() << "检测到 CDialog::accepted 产生了。";
    });

    connect(this, &QDialog::rejected, this, [](){
        qDebug() << "检测到 CDialog::rejected 产生了。";
    });

    //关闭对话框即发出该信号QDialog::finished
    connect(this, &QDialog::finished, this, [](){
        qDebug() << "检测到 CDialog::finished 产生了。";
    });
}


