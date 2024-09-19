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
