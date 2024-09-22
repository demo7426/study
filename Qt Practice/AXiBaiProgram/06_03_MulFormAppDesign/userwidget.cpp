#include "userwidget.h"
#include "ui_userwidget.h"

CUserWidget::CUserWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CUserWidget)
{
    ui->setupUi(this);
}

CUserWidget::~CUserWidget()
{
    delete ui;
}
