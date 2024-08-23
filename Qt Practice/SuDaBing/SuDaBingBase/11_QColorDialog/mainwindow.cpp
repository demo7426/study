#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->selectColorBtn, &QPushButton::clicked, this, [=](){
        QColor cQColor = QColorDialog::getColor();
        ui->colorLabel->setText(QString("r = %1, g = %2, b = %3, alpha = %4").
                                arg(cQColor.red()).arg(cQColor.green()).arg(cQColor.blue()).arg(cQColor.alpha()));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
