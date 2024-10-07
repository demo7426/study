#ifndef PENDIALOG_H
#define PENDIALOG_H

#include <QDialog>
#include <QPen>

namespace Ui {
class CPenDialog;
}

class CPenDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CPenDialog(QWidget *parent = nullptr);
    ~CPenDialog();

    ///
    /// \brief 获取画笔对象
    /// \param _IsOk--是否成功;true--成功;false--失败;
    /// \param _InitialPen--初始化画笔对象
    /// \param _pParent--父类指针对象
    /// \return
    ///
    static QPen GetPen(bool& _IsOk, const QPen& _InitialPen, QWidget *_pParent = nullptr) noexcept;
private:
    QPen m_cCurPen;
    Ui::CPenDialog *ui;


private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

    ///
    /// \brief 初始化Ui的Data
    /// \param _InitialPen
    ///
    int InitUiData(const QPen& _InitialPen);

    inline QPen GetCurPen(void) noexcept
    {
        return m_cCurPen;
    }
};

#endif // PENDIALOG_H
