#include "dialogsetsize.h"
#include "ui_dialogsetsize.h"

CDialogSetSize::CDialogSetSize(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CDialogSetSize)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CDialogSetSize::~CDialogSetSize()
{
    delete ui;
}

void CDialogSetSize::SetRowAndColumnCount(quint32 _RowCount, quint32 _ColumnCount)
{
    ui->spinBoxRow->setMinimum(0);
    ui->spinBoxRow->setMaximum(9999);
    ui->spinBoxColumn->setMaximum(0);
    ui->spinBoxColumn->setMaximum(9999);

    ui->spinBoxRow->setValue(_RowCount);
    ui->spinBoxColumn->setValue(_ColumnCount);
}

void CDialogSetSize::InitUi() noexcept
{

}

void CDialogSetSize::InitSignalSlots() noexcept
{
    connect(ui->btnOK, &QPushButton::clicked, this, [=](){
        this->hide();
        emit RowAndColumnChanged(ui->spinBoxRow->value(), ui->spinBoxColumn->value());
    });
    connect(ui->btnCancel, &QPushButton::clicked, this, [=](){
        this->hide();
        emit RowAndColumnChanged(ui->spinBoxRow->value(), ui->spinBoxColumn->value(), false);
    });
}
