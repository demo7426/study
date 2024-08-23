#include "userdifinedqtcontrol_widget.h"
#include "ui_userdifinedqtcontrol_widget.h"

UserDifinedQtControl_Widget::UserDifinedQtControl_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDifinedQtControl_Widget)
{
    ui->setupUi(this);

    void (QSpinBox::*pvalueChanged)(int) = &QSpinBox::valueChanged;

    connect(ui->spinBox, pvalueChanged, this, [=](int value){
        ui->horizontalSlider->setValue(value);
    });

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [=](int value){
        ui->spinBox->setValue(value);
    });
}

UserDifinedQtControl_Widget::~UserDifinedQtControl_Widget()
{
    delete ui;
}

void UserDifinedQtControl_Widget::SetData(int Value)
{
    ui->spinBox->setValue(Value);
}

int UserDifinedQtControl_Widget::GetData()
{
    return ui->spinBox->value();
}
