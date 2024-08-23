#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Connect()
{
    connect(ui->saveBtn, &QPushButton::clicked, this, [=](){
        QString cQStrSelecterFilter("Text files (*.txt)");

        QString cQStrSaveFileName = QFileDialog::getSaveFileName(this, "保存文件", QString(),
                                     tr( "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"), &cQStrSelecterFilter);
        QMessageBox::information(this, "保存的文件路径", cQStrSaveFileName);
    });

    connect(ui->openFileBtn, &QPushButton::clicked, this, [=](){
        QString cQStrSelecterFilter("Text files (*.txt)");

        QString cQStrSaveFileName = QFileDialog::getOpenFileName(this, "打开文件", QString(),
                                                                 tr( "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"), &cQStrSelecterFilter);
        QMessageBox::information(this, "打开的文件路径", cQStrSaveFileName);
    });

    connect(ui->openFilesBtn, &QPushButton::clicked, this, [=](){
        QString cQStrSelecterFilter("Text files (*.txt)");

        QStringList cQStrSaveFileNames = QFileDialog::getOpenFileNames(this, "打开多个文件", QString(),
                                                                 tr( "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"), &cQStrSelecterFilter);

        QString cQStrInfo = QString();
        for (int i = 0; i < cQStrSaveFileNames.size(); ++i) {
            cQStrInfo.append(" " + cQStrSaveFileNames.at(i));
        }

        QMessageBox::information(this, "打开的文件路径", cQStrInfo);
    });

    connect(ui->openDirBtn, &QPushButton::clicked, this, [=](){
        QString cQStrSaveFileName = QFileDialog::getExistingDirectory(this, "打开文件夹", QString());
        QMessageBox::information(this, "打开的文件夹路径", cQStrSaveFileName);
    });

}
