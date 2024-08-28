#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_29_clicked()
{
    QString str01, str02;

    str01 = ui->comboBoxStr01->currentText();
    str02 = ui->comboBoxStr02->currentText();

    ui->lineEditEndResult->setText(str01.append(str02));
}


void Widget::on_pushButton_30_clicked()
{
    QString str01, str02;

    str01 = ui->comboBoxStr01->currentText();
    str02 = ui->comboBoxStr02->currentText();

    ui->lineEditEndResult->setText(str01.prepend(str02));
}


void Widget::on_pushButton_31_clicked(bool checked)
{
    Q_UNUSED(checked)

    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.toUpper());
}


void Widget::on_pushButton_32_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.toLower());
}


void Widget::on_pushButton_33_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.left(3));
}


void Widget::on_pushButton_34_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.right(3));
}


void Widget::on_pushButton_28_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.section('\\', 1, 2));      //按照字符分割字符串,1--代表第二个开始，取出2个分割出的字符串
}


void Widget::on_pushButton_35_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.simplified());             //删除字符串的头尾空格符，将内部连续的空格符缩减为单独的1个
}


void Widget::on_pushButton_36_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(str01.trimmed());                //删除字符串的头尾空格符
}

