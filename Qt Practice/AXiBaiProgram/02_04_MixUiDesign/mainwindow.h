/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.08.23
描  述:	使用ui设计界面和code混合设计ui
备  注:
修改记录:

  1.  日期: 2024.08.23
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QFontComboBox>
#include <QProgressBar>

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
    void on_textEdit_copyAvailable(bool b);

    void on_textEdit_selectionChanged();

private:
    QSpinBox* m_pcSpinBox_FontSize = nullptr;                   //字体大小旋转框
    QFontComboBox* m_pcFontComboBox = nullptr;                  //字体选择框
    QProgressBar* m_pcProgressBar = nullptr;                    //字体大小进度条

private:
    Ui::MainWindow *ui;

private:
    //初始化ui界面
    void InitUi(void) noexcept;

    //初始化信号槽
    void InitSignalSlots(void) noexcept;

private slots:
    //设置加粗
    void SetTextEditBold(bool _Checked) noexcept;

    //设置斜体
    void SetTextEditItalic(bool _Checked) noexcept;

    //设置下划线
    void SetTextEditUnderline(bool _Checked) noexcept;

    //设置字体大小
    void SetTextEditPointSize(int _Value) noexcept;

    //设置字体格式
    void SetTextEditFont(const QFont &_Font);
};
#endif // MAINWINDOW_H
