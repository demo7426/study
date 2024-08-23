#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    //移动当前窗口位置
    void MoveCurMainWindow(int _X, int _Y);

    //打印当前窗口位置及尺寸信息
    void PrintfCurMainWindowInfo();

    //随机修改当前窗口位置及尺寸
    void RandomModifyCurMainWindowInfo();

    //修改当前窗口的图标或标题
    void ModifyIconOrTitle();

private:
    //初始化
    void InitMainWindow();

    //信号槽连接
    void Connect() noexcept;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
