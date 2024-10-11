/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.10
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.10
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QTreeWidget>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QChartView>

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
    void on_spinHoleSize_valueChanged(double arg1);

    void on_spinPieSize_valueChanged(double arg1);

    void on_cBoxCourse_currentIndexChanged(int index);

    void on_cBoxTheme_currentIndexChanged(int index);

private:
    QStandardItemModel* m_pcStandardItemModel = nullptr;
    QItemSelectionModel* m_pcItemSelectionModel = nullptr;

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
    /// \brief 初始化QTableView数据
    /// \param _pTableView--源数据地址
    ///
    void InitTableViewData(QTableView* _pTableView);

    ///
    /// \brief 刷新QTableView数据
    /// \param _pTableView--源数据地址
    ///
    void RefreshTableViewData(QTableView* _pTableView);

    ///
    /// \brief 调查QTableView的数据并且显示到QTreeWidget上
    /// \param _pTableView--源数据地址
    /// \param _pTreeWidget--目的数据地址
    ///
    void SurveyTableViewDataToTreeWidget(QTableView* _pTableView, QTreeWidget* _pTreeWidget);

    ///
    /// \brief 初始化柱状图相关信息
    /// \param _pChartView
    ///
    void InitBarChart(QChartView* _pChartView);

    ///
    /// \brief 刷新柱状图数据
    /// \param _pChartView
    ///
    void RefreshBarChartData(QChartView* _pChartView);

    ///
    /// \brief 初始化饼图相关信息
    /// \param _pChartView
    ///
    void InitPieChart(QChartView* _pChartView);

    ///
    /// \brief 刷新饼图数据
    /// \param _pChartView
    ///
    void RefreshPieChartData(QChartView* _pChartView);
};
#endif // MAINWINDOW_H
