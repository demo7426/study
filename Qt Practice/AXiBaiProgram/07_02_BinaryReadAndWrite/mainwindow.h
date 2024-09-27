/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.27
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.27
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

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
    QStandardItemModel *m_pcStandardItemModel = nullptr;
    QItemSelectionModel *m_pcItemSelectionModel = nullptr;

    constexpr static quint32 m_unRowCount = 3;                  //行数
    constexpr static quint32 m_unColumnCount = 4;               //列数

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
    /// \brief 设置对应的TabelView行数和列数
    /// \param _pStandardItemModel--Mode数据模型
    /// \param _RowCount--行数
    /// \param _ColumnCount--列数
    ///
    void SetTabelViewRowAndColumn(QStandardItemModel *_pStandardItemModel, quint32 _RowCount, quint32 _ColumnCount);

    ///
    /// \brief 加载*.stm文件
    ///
    void LoadStmFileToQStandardItemModel(void);

    ///
    /// \brief 保存数据到*.stm文件中
    ///
    void SaveQStandardItemModelDataToStmFile(void);

    ///
    /// \brief 加载*.dat文件
    ///
    void LoadDatFileToQStandardItemModel(void);

    ///
    /// \brief 保存数据到*.dat文件中
    ///
    void SaveQStandardItemModelDataToDatFile(void);
};
#endif // MAINWINDOW_H
