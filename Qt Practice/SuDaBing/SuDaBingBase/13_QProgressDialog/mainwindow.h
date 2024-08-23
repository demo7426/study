#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressDialog>
#include <QTimer>

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
    QTimer* m_pcQTimer = nullptr;
    QProgressDialog* m_pcQProgressDialog = nullptr;

};
#endif // MAINWINDOW_H
