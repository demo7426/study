#ifndef DIALOGLOCATE_H
#define DIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class CDialogLocate;
}

class CDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit CDialogLocate(QWidget *parent = nullptr);
    ~CDialogLocate();

    //设置显示内容
    void SetShowContent(const quint32 _Row, const quint32 _Column, const QString _Context);

private:
    Ui::CDialogLocate *ui;

signals:
    void ContentChanged(const quint32 _Row, const quint32 _Column, const QString _Context);

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

#endif // DIALOGLOCATE_H
