#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

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
    void Init();
    void Connect();

private:
    Ui::MainWindow *ui;

    QAction *m_pQAction_MenuBtn01 = nullptr;
};
#endif // MAINWINDOW_H
