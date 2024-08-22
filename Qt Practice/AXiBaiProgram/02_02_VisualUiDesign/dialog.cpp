#include <QFont>
#include <QColor>

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    Connected();
}

Dialog::~Dialog()
{
    delete ui;
}

int Dialog::Connected() noexcept
{
    //qt5之前的用法
    connect(ui->radioBtnRed, SIGNAL(clicked()), this, SLOT(SetPlainTextEditColor()));

    //qt5之后的用法
    connect(ui->radioBtnGreen, &QRadioButton::clicked, this, &Dialog::SetPlainTextEditColor);
    connect(ui->radioBtnBlue, &QRadioButton::clicked, this, &Dialog::SetPlainTextEditColor);

    return 0;
}

void Dialog::on_checkBoxUnderline_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setUnderline(checked);
    ui->plainTextEdit->setFont(cFont);
}


void Dialog::on_checkBoxItalic_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setItalic(checked);
    ui->plainTextEdit->setFont(cFont);
}


void Dialog::on_checkBoxBold_clicked(bool checked)
{
    QFont cFont = ui->plainTextEdit->font();

    cFont.setBold(checked);
    ui->plainTextEdit->setFont(cFont);
}

void Dialog::SetPlainTextEditColor()
{
    QPalette cPalette = ui->plainTextEdit->palette();

    if(ui->radioBtnRed->isChecked())
        cPalette.setColor(QPalette::Text, Qt::red);
    else if(ui->radioBtnBlue->isChecked())
        cPalette.setColor(QPalette::Text, Qt::blue);
    else if(ui->radioBtnGreen->isChecked())
        cPalette.setColor(QPalette::Text, Qt::green);
    else
        cPalette.setColor(QPalette::Text, Qt::black);

    ui->plainTextEdit->setPalette(cPalette);
}

