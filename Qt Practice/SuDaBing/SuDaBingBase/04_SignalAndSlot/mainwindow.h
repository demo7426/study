#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cboyfriend.h"
#include "cgirlfriend.h"

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
    void HungryBtnSlot();

private:
    Ui::MainWindow *ui;

    CBoyFriend* m_pcBoyFriend = nullptr;
    CGirlFriend* m_pcGirlFriend = nullptr;
};
#endif // MAINWINDOW_H
