/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.23
描  述:	使用ui设计界面和code混合设计ui
备  注:
修改记录:

  1.  日期: 2024.08.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#include <QLabel>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_pcSpinBox_FontSize;
    delete m_pcFontComboBox;
    delete m_pcProgressBar;

    m_pcSpinBox_FontSize = nullptr;
    m_pcFontComboBox = nullptr;
    m_pcProgressBar = nullptr;
}

void MainWindow::InitUi() noexcept
{
    constexpr int nFontSize = 20;                           //字体大小

    QLabel* pcLable01 = new QLabel(tr("字体大小 "), this);
    QLabel* pcLable02 = new QLabel(tr(" 字体 "), this);
    QLabel* pcLable03 = new QLabel(tr("进度条 "), this);

    m_pcSpinBox_FontSize = new QSpinBox();
    m_pcFontComboBox = new QFontComboBox();
    m_pcProgressBar = new QProgressBar();

    ui->toolBar->addWidget(pcLable01);
    ui->toolBar->addWidget(m_pcSpinBox_FontSize);
    ui->toolBar->addWidget(pcLable02);
    ui->toolBar->addWidget(m_pcFontComboBox);

    ui->statusbar->addWidget(pcLable03);
    ui->statusbar->addWidget(m_pcProgressBar);

    this->setCentralWidget(ui->textEdit);                   //设置textEdit居中显示

    ui->textEdit->setFontPointSize(nFontSize);
    m_pcSpinBox_FontSize->setValue(nFontSize);
    m_pcProgressBar->setValue(m_pcSpinBox_FontSize->value());
    m_pcFontComboBox->setCurrentFont(ui->textEdit->font());
}

void MainWindow::InitSignalSlots() noexcept
{
    connect(ui->actionBold, SIGNAL(triggered(bool)), this, SLOT(SetTextEditBold(bool)));
    connect(ui->actionItalic, SIGNAL(triggered(bool)), this, SLOT(SetTextEditItalic(bool)));
    connect(ui->actionUnderline, SIGNAL(triggered(bool)), this, SLOT(SetTextEditUnderline(bool)));

    connect(m_pcSpinBox_FontSize, &QSpinBox::valueChanged, this, &MainWindow::SetTextEditPointSize);
    connect(m_pcFontComboBox, &QFontComboBox::currentFontChanged, this, &MainWindow::SetTextEditFont);
}

void MainWindow::SetTextEditBold(bool _Checked) noexcept
{
    QTextCharFormat cTextCharFormat;

    if(_Checked)
        cTextCharFormat.setFontWeight(QFont::Bold);
    else
        cTextCharFormat.setFontWeight(QFont::Normal);

    ui->textEdit->mergeCurrentCharFormat(cTextCharFormat);          //设置当前选中字符的格式
}

void MainWindow::SetTextEditItalic(bool _Checked) noexcept
{
    QTextCharFormat cTextCharFormat;

    cTextCharFormat.setFontItalic(_Checked);

    ui->textEdit->mergeCurrentCharFormat(cTextCharFormat);          //设置当前选中字符的格式
}

void MainWindow::SetTextEditUnderline(bool _Checked) noexcept
{
    QTextCharFormat cTextCharFormat;

    cTextCharFormat.setFontUnderline(_Checked);

    ui->textEdit->mergeCurrentCharFormat(cTextCharFormat);          //设置当前选中字符的格式
}

void MainWindow::SetTextEditPointSize(int _Value) noexcept
{
    QFont cFont;
    QTextCharFormat cTextCharFormat;

    cFont.setPointSize(_Value);
    cTextCharFormat.setFont(cFont);

    ui->textEdit->mergeCurrentCharFormat(cTextCharFormat);          //设置当前选中字符的格式
    m_pcProgressBar->setValue(_Value);
}

void MainWindow::SetTextEditFont(const QFont &_Font)
{
    QTextCharFormat cTextCharFormat;

    cTextCharFormat.setFont(_Font);

    ui->textEdit->mergeCurrentCharFormat(cTextCharFormat);          //设置当前选中字符的格式
}

//当textEdit选择或者取消文本时会发出copyAvailable信号，调用该函数
void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
    ui->actionPaste->setEnabled(ui->textEdit->canPaste());
}


void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat cTextCharFormat;
    cTextCharFormat = ui->textEdit->currentCharFormat();

    ui->actionItalic->setChecked(cTextCharFormat.font().italic());
    ui->actionBold->setChecked(cTextCharFormat.font().bold());
    ui->actionUnderline->setChecked(cTextCharFormat.font().underline());
}

