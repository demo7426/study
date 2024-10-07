#include <QPalette>
#include "pendialog.h"
#include "ui_pendialog.h"

CPenDialog::CPenDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CPenDialog)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CPenDialog::~CPenDialog()
{
    delete ui;
}

QPen CPenDialog::GetPen(bool& _IsOk, const QPen &_InitialPen, QWidget *_pParent) noexcept
{
    Q_UNUSED(_pParent);

    CPenDialog cPenDialog;

    _IsOk = cPenDialog.InitUiData(_InitialPen) == 0? true: false;

    if(_IsOk == false)
        return _InitialPen;

    return cPenDialog.GetCurPen();
}

void CPenDialog::InitUi() noexcept
{
    QStringList strList = { "NoPen",
                           "SolidLine",
                           "DashLine",
                           "DotLine",
                           "DashDotLine",
                           "DashDotDotLine",
                           "CustomDashLine",
                           "MPenStyle" };

    ui->comboPenStyle->addItems(strList);
}

void CPenDialog::InitSignalSlots() noexcept
{
}

int CPenDialog::InitUiData(const QPen &_InitialPen)
{
    QString strStyleSheet = QString::asprintf("QPushButton{background-color: rgba(%d, %d, %d, %d)}",
                                              _InitialPen.color().red(), _InitialPen.color().green(), _InitialPen.color().blue(), _InitialPen.color().alpha());

    ui->comboPenStyle->setCurrentIndex(_InitialPen.style());
    ui->spinWidth->setValue(_InitialPen.width());
    ui->btnColor->setStyleSheet(strStyleSheet);

    if(this->exec() == QDialog::Accepted)
    {
        QColor cColorCurBtn = ui->btnColor->palette().color(QPalette::Button);

        m_cCurPen.setStyle((Qt::PenStyle)ui->comboPenStyle->currentIndex());
        m_cCurPen.setWidth(ui->spinWidth->value());
        m_cCurPen.setColor(cColorCurBtn);
    }
    else
        return -2;

    return 0;
}
