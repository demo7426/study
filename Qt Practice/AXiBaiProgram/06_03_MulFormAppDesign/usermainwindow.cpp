#include "usermainwindow.h"
#include "ui_usermainwindow.h"

CUserMainWindow::CUserMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CUserMainWindow)
{
    ui->setupUi(this);
}

CUserMainWindow::~CUserMainWindow()
{
    delete ui;
}
