#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::InitUi() noexcept
{
    CalTotalPrice();
}


void Widget::InitSignalSlots(void) noexcept
{
    connect(ui->pushBtnCal, SIGNAL(clicked(void)), this, SLOT(CalTotalPrice(void)));
    connect(ui->spinBoxNum, &QSpinBox::valueChanged, this, &Widget::CalTotalPrice);
    connect(ui->doubleSpinBoxUnitPrice, &QDoubleSpinBox::valueChanged, this, &Widget::CalTotalPrice);

    connect(ui->pushBtnDec, &QPushButton::clicked, this, &Widget::ConverNum);
    connect(ui->pushBtnBin, &QPushButton::clicked, this, &Widget::ConverNum);
    connect(ui->pushBtnHex, &QPushButton::clicked, this, &Widget::ConverNum);
}

void Widget::CalTotalPrice(void)
{
    int nNum = ui->spinBoxNum->value();
    double dbUnitPrice = ui->doubleSpinBoxUnitPrice->value();

    ui->lineEditTotalPrice->setText(QString::asprintf("%.02f", nNum * dbUnitPrice));
}

void Widget::ConverNum()
{
    try
    {
        QPushButton* pcPushBtn = qobject_cast<QPushButton*>(sender());

        if(pcPushBtn == ui->pushBtnDec)     //十进制数转换
        {
            int nDecNum = ui->spinBoxDecNum->value();
            ui->spinBoxBinNum->setValue(nDecNum);
            ui->spinBoxHexNum->setValue(nDecNum);
        }
        else if(pcPushBtn == ui->pushBtnBin)
        {
            int nBinNum = ui->spinBoxBinNum->value();
            ui->spinBoxDecNum->setValue(nBinNum);
            ui->spinBoxHexNum->setValue(nBinNum);
        }
        else if(pcPushBtn == ui->pushBtnHex)
        {
            int nHexNum = ui->spinBoxHexNum->value();
            ui->spinBoxDecNum->setValue(nHexNum);
            ui->spinBoxBinNum->setValue(nHexNum);
        }
        else
        {
            qDebug() << "ConverNum sender is unrecognition.\n";
        }
    }
    catch (const std::exception& e)
    {
        qWarning() << "ConverNum is err.\n"<< e.what();
    }

}
