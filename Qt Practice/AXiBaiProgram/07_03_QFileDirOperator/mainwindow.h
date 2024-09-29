/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mainwindow.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.09.29
描  述:	实现当前的mainwindow ui界面和后台数据的交互
备  注:
修改记录:

  1.  日期: 2024.09.29
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QPlainTextEdit>
#include <QMainWindow>

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
    void on_pushBtnOpenFile_clicked();

    void on_pushBtnOpenDir_clicked();

    void on_pushBtnClearText_clicked();

    void on_pushButton_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_28_clicked();

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

    ///
    /// \brief 添加文本信息到PlainTextEdit中
    /// \param _pPushBtn--按钮指针对象
    /// \param _pPlainTextEdit
    ///
    void AppendMsgToplainTextEdit(QPushButton* _pPushBtn, QPlainTextEdit* _pPlainTextEdit);
};
#endif // MAINWINDOW_H
