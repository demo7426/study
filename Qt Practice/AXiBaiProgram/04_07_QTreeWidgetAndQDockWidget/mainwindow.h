/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.03
描  述:	实现当前的widget ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.03
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QLabel>
#include <QPixmap>
#include <QLayout>

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
    enum class COLUMNTYPE:char                          //TreeWidget每一行条目的列索引
    {
        VALUE = 0,
        TYPE = 1,
    };

    QVBoxLayout* m_pcVBoxLayout = nullptr;
    QLabel* m_pcLabel_Pixmap = nullptr;                  //用于显示图像
    QPixmap* m_pcPixmap = nullptr;                       //加载图片


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
    /// TreeWidget添加目录节点
    /// </summary>
    void TreeWidgetAddFolder(void) noexcept;

    /// <summary>
    /// TreeWidget添加多文件节点
    /// </summary>
    void TreeWidgetAddFiles(void) noexcept;

    /// <summary>
    /// TreeWidget遍历当前level及以下的节点
    /// </summary>
    void TreeWidgetTraversalItems(QTreeWidgetItem* _pCurTreeWidgetItem) noexcept;

    void CurrentItemChanged(QTreeWidgetItem *pCurrent, QTreeWidgetItem *_Previous);
};
#endif // MAINWINDOW_H
