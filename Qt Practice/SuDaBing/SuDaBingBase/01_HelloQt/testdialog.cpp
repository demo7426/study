#include "testdialog.h"
#include "ui_testdialog.h"

CTestDialog::CTestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CTestDialog)
{
    ui->setupUi(this);
}

CTestDialog::~CTestDialog()
{
    delete ui;
}
