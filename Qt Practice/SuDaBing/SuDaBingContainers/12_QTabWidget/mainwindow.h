#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQueue>

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
    //初始化函数
    int Init();

    //连接
    void Connect();

private:
    Ui::MainWindow *ui;

    QQueue<QWidget*> m_queTabWidget;        //保存被移除的标签界面
    QQueue<QString> m_queTabTitle;           //保存被移除的标签标题
};
#endif // MAINWINDOW_H
