/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.18
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.10.18
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Q3DSurface>

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
    void on_btnBarColor_clicked();

    void on_btnGrad1_clicked();

    void on_btnGrad2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value);

    void on_sliderV_valueChanged(int value);

    void on_sliderZoom_valueChanged(int value);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_cBoxBarStyle_currentIndexChanged(int index);

    void on_cBoxSelectionMode_currentIndexChanged(int index);

    void on_spinFontSize_valueChanged(int arg1);

    void on_comboDrawMode_currentIndexChanged(int index);

    void on_chkBoxBackground_stateChanged(int arg1);

    void on_chkBoxGrid_stateChanged(int arg1);

    void on_chkBoxShadow_stateChanged(int arg1);

    void on_chkBoxReflection_stateChanged(int arg1);

    void on_chkBoxSmooth_stateChanged(int arg1);

    void on_chkBoxReverse_stateChanged(int arg1);

    void on_chkBoxItemLabel_stateChanged(int arg1);

    void on_chkBoxAxisTitle_stateChanged(int arg1);

    void on_chkBoxAxisBackground_stateChanged(int arg1);

private:
    Q3DSurface *m_pc3DSurface = nullptr;

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
    /// \brief Init3DData--初始化3D数据
    ///
    void Init3DData(void);
};
#endif // MAINWINDOW_H
