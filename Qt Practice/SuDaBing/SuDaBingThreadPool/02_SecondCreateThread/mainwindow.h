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

private:
    void Init();                        //初始化
    void Connect();                     //信号槽连接

private:
    Ui::MainWindow *ui;

signals:
    void SetRandomNum(int _Num);        //设置随机数个数信号
};
#endif // MAINWINDOW_H
