#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QStringList m_cStringList;
    QStringListModel* m_pcStringListModel = nullptr;

private:
    Ui::Widget *ui;

private:
    /// <summary>
    /// 初始化ui界面
    /// </summary>
    void InitUi(void) noexcept;

    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitSignalSlots(void) noexcept;

private slots:
    /// <summary>
    /// 初始化信号槽
    /// </summary>
    void InitListView(void) noexcept;

    /// <summary>
    /// 插入一行数据
    /// </summary>
    void InsertModelIndexToListView(quint32 _Row) noexcept;
};
#endif // WIDGET_H
