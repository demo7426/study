/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	dialogsetsize.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	用于设置QTableView的行数、列数
备  注:
修改记录:

  1.  日期: 2024.09.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef DIALOGSETSIZE_H
#define DIALOGSETSIZE_H

#include <QDialog>

namespace Ui {
class CDialogSetSize;
}

class CDialogSetSize : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogSetSize(QWidget *parent = nullptr);
    ~CDialogSetSize();

    void SetRowAndColumnCount(quint32 _RowCount, quint32 _ColumnCount); //设置显示的行数列数

signals:
    void RowAndColumnChanged(quint32 _RowCount, quint32 _ColumnCount, bool _IsFlag = true);


private:
    Ui::CDialogSetSize *ui;

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

#endif // DIALOGSETSIZE_H
