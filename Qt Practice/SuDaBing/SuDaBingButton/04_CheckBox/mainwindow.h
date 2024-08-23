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

    void Connect();
    void ChangeWallPaper_LabelState(int _State);

private:
    Ui::MainWindow *ui;
    int m_nWallPaper_LabelNum = 0;      //壁纸标签数量
};
#endif // MAINWINDOW_H
