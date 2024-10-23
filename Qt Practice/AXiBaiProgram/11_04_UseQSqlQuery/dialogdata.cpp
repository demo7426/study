/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogdata.cpp
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.23
描  述:	实现自定义数据库记录ui的交互
备  注:
修改记录:

  1.  日期: 2024.10.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/
#include <QPixmap>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>

#include "dialogdata.h"
#include "ui_dialogdata.h"

CDialogData::CDialogData(QSqlRecord _SqlRecord, SQLRECORD_FLAG _Flag, QWidget *parent)
    : QDialog(parent)
    , m_cSqlRecord(_SqlRecord), m_eFlag(_Flag), ui(new Ui::CDialogData)
{
    ui->setupUi(this);

    InitUi();
    InitSignalSlots();
}

CDialogData::~CDialogData()
{
    delete ui;
}

void CDialogData::InitUi(void) noexcept
{
    switch (m_eFlag) {
    case SQLRECORD_FLAG::INSERT:                //插入信息
    {
        ui->spinEmpNo->setValue(m_cSqlRecord.value("empNo").toInt());
        ui->spinEmpNo->setEnabled(false);

        setWindowTitle(tr("插入信息窗口"));
    }
    break;
    case SQLRECORD_FLAG::EDIT:                  //编辑信息
    {
        QByteArray cByteArray;
        QPixmap cPixmap;

        //根据m_cSqlRecord的数据更新界面显示
        ui->spinEmpNo->setValue(m_cSqlRecord.value("empNo").toInt());
        ui->editName->setText(m_cSqlRecord.value("Name").toString());
        ui->comboSex->setCurrentText(m_cSqlRecord.value("Gender").toString());
        ui->spinHeight->setValue(m_cSqlRecord.value("Height").toFloat());
        ui->editBirth->setDate(m_cSqlRecord.value("Birthday").toDate());
        ui->editMobile->setText(m_cSqlRecord.value("Mobile").toString());
        ui->comboProvince->setCurrentText(m_cSqlRecord.value("Province").toString());
        ui->editCity->setText(m_cSqlRecord.value("City").toString());
        ui->comboDep->setCurrentText(m_cSqlRecord.value("Department").toString());
        ui->comboEdu->setCurrentText(m_cSqlRecord.value("Education").toString());
        ui->spinSalary->setValue(m_cSqlRecord.value("Salary").toInt());
        ui->editMemo->setPlainText(m_cSqlRecord.value("Memo").toString());

        cByteArray = m_cSqlRecord.value("Photo").toByteArray();
        if(!cByteArray.isEmpty())
        {
            cPixmap.loadFromData(cByteArray);
            ui->LabPhoto->setPixmap(cPixmap.scaledToWidth(ui->LabPhoto->width()));
        }

        setWindowTitle(tr("编辑信息窗口"));
    }
    break;
    default:
        break;
    }

    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
}

void CDialogData::InitSignalSlots(void) noexcept
{

}

void CDialogData::on_btnOK_clicked()
{
    //"确定"按钮后，界面数据保存到记录mRecord
    m_cSqlRecord.setValue("empNo",ui->spinEmpNo->value());
    m_cSqlRecord.setValue("Name",ui->editName->text());
    m_cSqlRecord.setValue("Gender",ui->comboSex->currentText());
    m_cSqlRecord.setValue("Height",ui->spinHeight->value());
    m_cSqlRecord.setValue("Birthday",ui->editBirth->date());
    m_cSqlRecord.setValue("Mobile",ui->editMobile->text());

    m_cSqlRecord.setValue("Province",ui->comboProvince->currentText());
    m_cSqlRecord.setValue("City",ui->editCity->text());
    m_cSqlRecord.setValue("Department",ui->comboDep->currentText());

    m_cSqlRecord.setValue("Education",ui->comboEdu->currentText());
    m_cSqlRecord.setValue("Salary",ui->spinSalary->value());
    m_cSqlRecord.setValue("Memo",ui->editMemo->toPlainText());

    //照片编辑时已经修改了mRecord的photo字段的值

    emit this->accepted();
    this->accept();
}

void CDialogData::on_btnSetPhoto_clicked()
{
    QString strFilePath = QFileDialog::getOpenFileName(this, tr("打开单个图片文件"), QDir::currentPath(), tr("图片文件(*.jpg *png)"));
    QByteArray cByteArray;
    QFile cFile;
    QPixmap cPixmap;

    if(strFilePath.isEmpty())
        return;

    cFile.setFileName(strFilePath);
    if(!cFile.open(QIODeviceBase::ReadOnly))
    {
        QMessageBox::critical(this, tr("错误窗口"), tr("打开图片文件错误"));
        return;
    }

    cByteArray = cFile.readAll();
    if(!cByteArray.isEmpty())
    {
        cPixmap.loadFromData(cByteArray);
        ui->LabPhoto->setPixmap(cPixmap.scaledToWidth(ui->LabPhoto->width()));

        m_cSqlRecord.setValue("Photo", cByteArray);
    }

    cFile.close();
}

void CDialogData::on_btnClearPhoto_clicked()
{
    ui->LabPhoto->clear();
    m_cSqlRecord.setNull("Photo");
}

