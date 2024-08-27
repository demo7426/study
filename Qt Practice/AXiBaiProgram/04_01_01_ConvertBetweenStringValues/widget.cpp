#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitSignalSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitSignalSlots() noexcept
{
    connect(ui->pushBtnCal, &QPushButton::clicked, this, &Widget::CalTotalPrice);
    connect(ui->pushBtnDec, &QPushButton::clicked, this, &Widget::NumConversion);
    connect(ui->pushBtnBin, &QPushButton::clicked, this, &Widget::NumConversion);
    connect(ui->pushBtnHex, &QPushButton::clicked, this, &Widget::NumConversion);
}

void Widget::CalTotalPrice()
{
    quint32 unUnitPrice = 0;
    quint32 unNum = 0;
    quint32 unTotalPrice = 0;

    try
    {
        unUnitPrice = ui->lineEditUnitPrice->text().toUInt();
        unNum = ui->lineEditNum->text().toUInt();
        unTotalPrice = unUnitPrice * unNum;
    }
    catch (const std::exception& e)
    {
        qDebug() << e.what();
        exit(0);
    }

    ui->lineEditTotalPrice->setText(QString::asprintf("%u", unTotalPrice));
}

void Widget::NumConversion()
{
    QPushButton* pcPushBtn = qobject_cast<QPushButton*>(sender());
    bool bOK = false;
    qint32 nValue = 0;
    QString strValue = "";

    if(pcPushBtn == ui->pushBtnDec)
    {
        nValue = ui->lineEditDecNum->text().toInt(&bOK, 10);

        if(bOK == false)
        {
            qDebug() << "NumConversion is failure.";
            return;
        }

        ui->lineEditBinNum->setText(strValue.setNum(nValue, 2));        //数值转换
        ui->lineEditHexNum->setText(strValue.setNum(nValue, 16));
    }
    else if(pcPushBtn == ui->pushBtnBin)
    {
        nValue = ui->lineEditBinNum->text().toInt(&bOK, 2);

        if(bOK == false)
        {
            qDebug() << "NumConversion is failure.";
            return;
        }

        ui->lineEditDecNum->setText(strValue.setNum(nValue, 10));
        ui->lineEditHexNum->setText(strValue.setNum(nValue, 16));
    }
    else if(pcPushBtn == ui->pushBtnHex)
    {
        nValue = ui->lineEditHexNum->text().toInt(&bOK, 16);

        if(bOK == false)
        {
            qDebug() << "NumConversion is failure.";
            return;
        }

        ui->lineEditDecNum->setText(strValue.setNum(nValue, 10));
        ui->lineEditBinNum->setText(strValue.setNum(nValue, 2));
    }
    else
    {
        qDebug() << "NumConversion sender is err.";
    }
}
