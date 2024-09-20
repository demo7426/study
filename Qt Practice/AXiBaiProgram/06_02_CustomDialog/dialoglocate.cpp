#include "dialoglocate.h"
#include "ui_dialoglocate.h"

CDialogLocate::CDialogLocate(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDialogLocate)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CDialogLocate::~CDialogLocate()
{
    delete ui;
}

void CDialogLocate::SetShowContent(const quint32 _Row, const quint32 _Column, const QString _Context)
{
    ui->spinBoxRow->setValue(_Row);
    ui->spinBoxColumn->setValue(_Column);
    ui->edtCaption->setText(_Context);
}

void CDialogLocate::InitUi() noexcept
{

}

void CDialogLocate::InitSignalSlots() noexcept
{
    connect(ui->btnSetText, &QPushButton::clicked, this, [this](){
        emit ContentChanged(ui->spinBoxRow->value(), ui->spinBoxColumn->value(), ui->edtCaption->text());
        this->hide();
    });
}
