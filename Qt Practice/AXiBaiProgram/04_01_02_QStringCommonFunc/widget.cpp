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


void Widget::on_pushButton_24_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(QString::asprintf("%lld", str01.count()));
}


void Widget::on_pushButton_25_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(QString::asprintf("%llu", str01.size()));
}


void Widget::on_pushButton_26_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(QString::asprintf("%llu", str01.indexOf('Q')));
}


void Widget::on_pushButton_27_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->lineEditEndResult->setText(QString::asprintf("%llu", str01.lastIndexOf('Q')));
}


void Widget::on_pushButton_19_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->checkBox->setChecked(str01.endsWith("cpp"));
}


void Widget::on_pushButton_20_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->checkBox->setChecked(str01.startsWith("G"));
}


void Widget::on_pushButton_21_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->checkBox->setChecked(str01.contains("Study"));
}


void Widget::on_pushButton_22_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->checkBox->setChecked(str01.isNull());
}


void Widget::on_pushButton_23_clicked()
{
    QString str01;

    str01 = ui->comboBoxStr01->currentText();
    ui->checkBox->setChecked(str01.isEmpty());
}

