/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogdata.h
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

#ifndef DIALOGDATA_H
#define DIALOGDATA_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class CDialogData;
}

class CDialogData : public QDialog
{
    Q_OBJECT

public:
    enum class SQLRECORD_FLAG:qint8
    {
        INSERT = 1,         //插入信息
        EDIT,               //修改信息
    };

    ///
    /// \brief CDialogData--带参唯一构造函数
    /// \param _SqlRecord--初始化信息
    /// \param _Flag--标志位;
    /// \param parent
    ///
    explicit CDialogData(QSqlRecord _SqlRecord, SQLRECORD_FLAG _Flag, QWidget *parent = nullptr);
    ~CDialogData();

    ///
    /// \brief GetCurSqlRecord--获取当前的sql记录
    /// \return
    ///
    inline QSqlRecord GetCurSqlRecord(void)
    {
        return m_cSqlRecord;
    }

private slots:
    void on_btnOK_clicked();

    void on_btnSetPhoto_clicked();

    void on_btnClearPhoto_clicked();

private:
    QSqlRecord m_cSqlRecord;
    SQLRECORD_FLAG m_eFlag;

    Ui::CDialogData *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;
};

#endif // DIALOGDATA_H
