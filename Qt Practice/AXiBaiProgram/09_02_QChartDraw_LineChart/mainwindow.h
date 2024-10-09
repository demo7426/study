/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.07
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.07
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineSeries>
#include <QValueAxis>

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
    void on_actDraw_triggered();

    void on_actZoomIn_triggered();

    void on_actZoomOut_triggered();

    void on_actZoomReset_triggered();

    void on_btnSetTitle_clicked();

    void on_btnSetTitleFont_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_chkLegendVisible_stateChanged(int arg1);

    void on_chkBoxLegendBackground_stateChanged(int arg1);

    void on_btnLegendFont_clicked();

    void on_btnLegendlabelColor_clicked();

    void on_spinMarginLeft_valueChanged(int arg1);

    void on_spinMarginRight_valueChanged(int arg1);

    void on_spinMarginTop_valueChanged(int arg1);

    void on_spinMarginBottom_valueChanged(int arg1);

    void on_cBoxAnimation_currentIndexChanged(int index);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_radioSeries0_clicked();

    void on_radioSeries1_clicked();

    void on_chkSeriesVisible_stateChanged(int arg1);

    void on_chkPointVisible_stateChanged(int arg1);

    void on_btnSeriesColor_clicked();

    void on_chkPointLabelVisible_stateChanged(int arg1);

    void on_btnSeriesLabColor_clicked();

    void on_btnSeriesLabFont_clicked();

    void on_sliderSeriesOpacity_valueChanged(int value);

    void on_radioSeriesLabFormat0_clicked();

    void on_radioSeriesLabFormat1_clicked();

    void on_btnSeriesPen_clicked();

    void on_radioX_clicked();

    void on_radioY_clicked();

    void on_spinAxisMin_valueChanged(double arg1);

    void on_spinAxisMax_valueChanged(double arg1);


    void on_chkBoxVisible_stateChanged(int arg1);

    void on_btnAxisSetTitle_clicked();

    void on_btnAxisSetTitleFont_clicked();

    void on_pushButton_clicked();

    void on_btnAxisLabelColor_clicked();

    void on_btnAxisLabelFont_clicked();

    void on_chkBoxLabelsVisible_stateChanged(int arg1);

    void on_chkGridLineVisible_stateChanged(int arg1);

    void on_btnGridLineColor_clicked();

    void on_pushButton_10_clicked();

    void on_spinTickCount_valueChanged(int arg1);

    void on_chkAxisLineVisible_stateChanged(int arg1);

    void on_btnAxisLinePen_clicked();

    void on_btnAxisLinePenColor_clicked();

    void on_spinMinorTickCount_valueChanged(int arg1);

    void on_chkMinorTickVisible_stateChanged(int arg1);

    void on_btnMinorColor_clicked();

    void on_btnMinorPen_clicked();

    void on_chkBoxAxisTitle_stateChanged(int arg1);

private:
    QLineSeries* m_pcCurLineSeries = nullptr;               //当前的选中的QLineSeries
    QValueAxis* m_pcCurValueAxis = nullptr;                 //当前的选中的QValueAxis

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
    /// \brief 初始化ChartView
    ///
    void InitChartView(void) noexcept;

    ///
    /// \brief 刷新ChartView的数据
    ///
    void RefreshChartViewData(void) noexcept;

    ///
    /// \brief 刷新数据状态
    ///
    void RefreshDataStatus(void);
};
#endif // MAINWINDOW_H
