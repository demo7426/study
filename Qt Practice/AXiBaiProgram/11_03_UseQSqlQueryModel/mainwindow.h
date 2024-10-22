/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.22
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.22
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSqlDatabase m_cSqlDatabase;
    QSqlQueryModel *m_pcSqlQueryModel = nullptr;
    QItemSelectionModel *m_pcItemSelectionModel = nullptr;
    QDataWidgetMapper *m_pcDataWidgetMapper = nullptr;

    Ui::MainWindow *ui;


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
    ///
    /// \brief OpenSQLiteFile--打开SQLite文件
    ///
    void OpenSQLiteFile(void) noexcept;

    void On_CurrentRowChanged(const QModelIndex &current, const QModelIndex &previous);

    ///
    /// \brief RefreshItemSelectionModel--刷新tabView选中位置
    ///
    void RefreshItemSelectionModel(void);

    void on_actRecFirst_triggered();
    void on_actRecPrevious_triggered();
    void on_actRecNext_triggered();
    void on_actRecLast_triggered();
};
#endif // MAINWINDOW_H
