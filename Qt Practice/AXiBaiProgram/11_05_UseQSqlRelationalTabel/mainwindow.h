/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.24
描  述:	实现关系型数据库的使用
备  注:
修改记录:

  1.  日期: 2024.10.24
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QItemSelectionModel>
#include <QSqlRecord>
#include <QSqlQuery>

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

private slots:
    void on_actFields_triggered();

    void on_actRecAppend_triggered();

    void on_actRecInsert_triggered();

    void on_actRecDelete_triggered();

    void on_actSubmit_triggered();

    void on_actRevert_triggered();

private:
    QSqlDatabase m_cSqlDatabase;                                            //数据库
    QSqlRelationalTableModel *m_pcSqlRelationalTableModel = nullptr;
    QItemSelectionModel *m_pcItemSelectionModel = nullptr;

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

    ///
    /// \brief OpenSQLiteFile--打开SQLite文件
    ///
    void OpenSQLiteFile(void);

    void On_CurrentChanged(const QModelIndex &current, const QModelIndex &previous);


    ///
    /// \brief InsertDataToSqlTableModel--插入一行数据
    /// \param _RowNo--行号
    ///
    void InsertDataToSqlTableModel(quint32 _RowNo);
};
#endif // MAINWINDOW_H
