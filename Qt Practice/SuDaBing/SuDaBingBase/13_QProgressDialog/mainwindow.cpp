#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->Init();
    this->Connect();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pcQProgressDialog;
}

void MainWindow::Init()
{
    m_pcQTimer = new QTimer(this);
    m_pcQProgressDialog = new QProgressDialog(tr("拷贝进度"), tr("取消拷贝"), 0, 100, this);
    this->m_pcQProgressDialog->cancel();

    QLineEdit *pcQLineEdit = new QLineEdit("请输入查询内容", this);
    QPushButton *pcQPushButton = new QPushButton(this);
    pcQPushButton->setText("搜索");

    ui->toolBar->addWidget(pcQLineEdit);
    ui->toolBar->addWidget(pcQPushButton);

    QLineEdit *pcQLineEdit02 = new QLineEdit("请输入查询内容", this);
    QPushButton *pcQPushButton02 = new QPushButton(this);
    pcQPushButton02->setText("搜索");

    ui->statusbar->showMessage("状态栏", 2000);
    ui->statusbar->addWidget(pcQLineEdit02);
    ui->statusbar->addWidget(pcQPushButton02);

    QTimer::singleShot(2000, this, [=](){
        pcQLineEdit02->show();
        pcQPushButton02->show();
    });

}

void MainWindow::Connect()
{
    static int nProgresss = 0;

    connect(m_pcQTimer, &QTimer::timeout, this, [&](){
        this->m_pcQProgressDialog->setValue(nProgresss);
        ++nProgresss;

        if(nProgresss > this->m_pcQProgressDialog->maximum())
        {
            nProgresss = 0;
            m_pcQTimer->stop();
        }
    });

    connect(ui->progressDialogBtn, &QPushButton::clicked, this, [&](){
        this->m_pcQProgressDialog->show();
        //m_pcQProgressDialog->setAutoClose(true);

        m_pcQTimer->start(100);
    });

    connect(m_pcQProgressDialog, &QProgressDialog::canceled, this, [&](){
        nProgresss = 0;
        m_pcQTimer->stop();
        //m_pcQProgressDialog->reset();
    });

    connect(ui->openFileAction, &QAction::triggered, this, [=](){
        QFileDialog::getOpenFileName(this, tr("Open File"));
    });
}
