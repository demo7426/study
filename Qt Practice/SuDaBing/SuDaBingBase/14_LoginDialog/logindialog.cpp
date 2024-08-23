#include "logindialog.h"
#include "ui_logindialog.h"

CLoginDialog::CLoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CLoginDialog)
{
    ui->setupUi(this);
}

CLoginDialog::~CLoginDialog()
{
    delete ui;
}
