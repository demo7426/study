#ifndef USERMAINWINDOW_H
#define USERMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class CUserMainWindow;
}

class CUserMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CUserMainWindow(QWidget *parent = nullptr);
    ~CUserMainWindow();

private:
    Ui::CUserMainWindow *ui;
};

#endif // USERMAINWINDOW_H
