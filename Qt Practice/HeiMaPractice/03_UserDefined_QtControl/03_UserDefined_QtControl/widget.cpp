#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        ui->widget->SetData(50);
    });

    connect(ui->pushButton_2, &QPushButton::clicked, this, [=](){
        qDebug() << ui->widget->GetData();
    });
}

Widget::~Widget()
{
    delete ui;
}

