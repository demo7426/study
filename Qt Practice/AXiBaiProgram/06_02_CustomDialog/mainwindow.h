/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.20
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.20
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "dialogsetsize.h"

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
    CDialogSetSize *m_pcDialogSetSize = nullptr;

    QStandardItemModel *m_pcStandardItemModel = nullptr;
    QItemSelectionModel *m_pcItemSelectionModel = nullptr;
private:
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

    /// <summary>
    /// 显示设置行数列数对话框
    /// </summary>
    void ShowDialogSetSize(void);

    /// <summary>
    /// 设置tableView的行数、列数
    /// </summary>
    void SetTableViewSize(quint32 _RowCount, quint32 _ColumnCount, bool _IsFlag = true);
};
#endif // MAINWINDOW_H
