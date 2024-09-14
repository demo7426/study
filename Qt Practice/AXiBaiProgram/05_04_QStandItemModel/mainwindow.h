/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.12
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.12
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
#include <QLabel>

#include "SpinIntDelegate.h"

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
    QStyledItemDelegate* m_pcStyledItemDelegate = nullptr;                  //tableView代理
    QStandardItemModel* m_pcStandardItemModel = nullptr;                    //tableView数据模型
    QItemSelectionModel* m_pcItemSelectionModel = nullptr;                  //tableView选择模型

    QLabel* m_pcLabel_FilePath = nullptr;
    QLabel* m_pcLabel_Pos = nullptr;
    QLabel* m_pcLabel_Text = nullptr;

    constexpr static quint32 m_unRowCount = 10;                             //行数
    constexpr static quint32 m_unColumnCount = 8;                           //列数
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
    void CurrentChanged(const QModelIndex &_Current, const QModelIndex &_Previous);

    /// <summary>
    /// 加载文件数据
    /// </summary>
    void LoadFileData(void);

    /// <summary>
    /// 保存数据到文件
    /// </summary>
    void SaveDataToFile(void);

    /// <summary>
    /// 模型数据预览
    /// </summary>
    void ModelDataPreview(void);

    /// <summary>
    /// 向QStandardItemModel插入一行数据
    /// </summary>
    void InsertRow(QStandardItemModel* _pStandardItemModel, const QModelIndex &_Current);

    /// <summary>
    /// 向QStandardItemModel添加一行数据
    /// </summary>
    void AppendRow(QStandardItemModel* _pStandardItemModel, const QModelIndex &_Current);

    /// <summary>
    /// 向QStandardItemModel删除一行数据
    /// </summary>
    inline void DeleteRow(QStandardItemModel* _pStandardItemModel, const QModelIndex &_Current);
};
#endif // MAINWINDOW_H
