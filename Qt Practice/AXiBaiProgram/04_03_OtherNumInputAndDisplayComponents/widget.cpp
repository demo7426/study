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
    QPalette cPalette = ui->textEditColor->palette();
    QColor cBackgroundColor = cPalette.color(QPalette::Base);

    ui->horizontalSliderRed->setValue(cBackgroundColor.red());
    ui->horizontalSliderGreen->setValue(cBackgroundColor.green());
    ui->horizontalSliderBlue->setValue(cBackgroundColor.blue());
    ui->horizontalSliderAlpha->setValue(cBackgroundColor.alpha());
}

void Widget::InitSignalSlots() noexcept
{
    connect(ui->horizontalSliderRed, &QSlider::valueChanged, this, &Widget::SetTextEditBackgroundColor);
    connect(ui->horizontalSliderGreen, &QSlider::valueChanged, this, &Widget::SetTextEditBackgroundColor);
    connect(ui->horizontalSliderBlue, &QSlider::valueChanged, this, &Widget::SetTextEditBackgroundColor);
    connect(ui->horizontalSliderAlpha, &QSlider::valueChanged, this, &Widget::SetTextEditBackgroundColor);

    connect(ui->horizontalSliderValue, &QSlider::valueChanged, this, &Widget::HorizontalValueChanged);
    connect(ui->horizontalScrollBarValue, &QScrollBar::valueChanged, this, &Widget::HorizontalValueChanged);

    connect(ui->verticalSliderValue, &QScrollBar::valueChanged, this, &Widget::VerticalValueChanged);
    connect(ui->verticalScrollBarValue, &QScrollBar::valueChanged, this, &Widget::VerticalValueChanged);

    connect(ui->dialNum, &QDial::valueChanged, this, &Widget::SetLCDNum);

    connect(ui->radioBtnDec, &QRadioButton::clicked, this, [=](){
        ui->lcdNumber->setDecMode();
    });

    connect(ui->radioBtnBin, &QRadioButton::clicked, this, [=](){
        ui->lcdNumber->setBinMode();
    });

    connect(ui->radioBtnOct, &QRadioButton::clicked, this, [=](){
        ui->lcdNumber->setOctMode();
    });

    connect(ui->radioBtnHex, &QRadioButton::clicked, this, [=](){
        ui->lcdNumber->setHexMode();
    });
}

void Widget::SetTextEditBackgroundColor(int _Value)
{
    Q_UNUSED(_Value);

    qint32 nRedValue, nGreenValue, nBlueValue, nAlphaValue;         //r,g,b,@的值
    QColor* pcBackgroundColor = nullptr;                            //背景色
    QPalette cPalette;                                              //调色板

    nRedValue = ui->horizontalSliderRed->value();
    nGreenValue = ui->horizontalSliderGreen->value();
    nBlueValue = ui->horizontalSliderBlue->value();
    nAlphaValue = ui->horizontalSliderAlpha->value();

    qDebug() << QString::asprintf("%d %d %d %d", nRedValue, nGreenValue, nBlueValue, nAlphaValue);

    pcBackgroundColor = new QColor(qRgba(nRedValue, nGreenValue, nBlueValue, nAlphaValue));
    cPalette.setColor(QPalette::Base, *pcBackgroundColor);

    ui->textEditColor->setPalette(cPalette);

    delete pcBackgroundColor;
    pcBackgroundColor = nullptr;
}

void Widget::HorizontalValueChanged(int _Value)
{
    ui->horizontalSliderValue->setValue(_Value);
    ui->horizontalScrollBarValue->setValue(_Value);
    ui->horizontalProgressBarValue->setValue(_Value);
}

void Widget::VerticalValueChanged(int _Value)
{
    ui->verticalSliderValue->setValue(_Value);
    ui->verticalScrollBarValue->setValue(_Value);
    ui->verticalProgressBarValue->setValue(_Value);
}

void Widget::SetLCDNum(int _Value)
{
    ui->lcdNumber->display(_Value);
}
