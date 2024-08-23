#include "testwidget.h"
#include "ui_testwidget.h"

CTestWidget::CTestWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CTestWidget)
{
    ui->setupUi(this);
}

CTestWidget::~CTestWidget()
{
    delete ui;
}
