#include <QFile>
#include <QFont>
#include <QFontDialog>

#include "form.h"
#include "ui_form.h"

CForm::CForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CForm)
{
    ui->setupUi(this);
    InitUi();
    InitSignalSlots();
}

CForm::~CForm()
{
    delete ui;
}

void CForm::InitUi() noexcept
{
    ui->plainTextEdit->clear();
    m_strLoadFilePath.clear();
}

void CForm::InitSignalSlots() noexcept
{

}

void CForm::LoadFileToText(QString _FilePath)
{
    QFile cFile(_FilePath);
    cFile.open(QIODeviceBase::OpenModeFlag::ReadOnly | QIODeviceBase::OpenModeFlag::Text);

    QTextStream cTextStream(&cFile);

    ui->plainTextEdit->setPlainText(cTextStream.readAll());
    cFile.close();

    m_strLoadFilePath = _FilePath;
}

void CForm::TextCopy()
{
    ui->plainTextEdit->copy();
}

void CForm::TextPaste()
{
    ui->plainTextEdit->paste();
}

void CForm::TextCut()
{
    ui->plainTextEdit->cut();
}

void CForm::SetTextFont()
{
    QFont cFont;
    bool bOk = false;

    cFont = ui->plainTextEdit->font();

    cFont = QFontDialog::getFont(&bOk, cFont, this);

    ui->plainTextEdit->setFont(cFont);
}
