#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

typedef struct _PERSON_INFO
{
    int Age;
    QString Name;
}PERSON_INFO, *PPERSON_INFO;

//声明METATYPE数据类型内部有 struct _PERSON_INFO 数据类型
Q_DECLARE_METATYPE(struct _PERSON_INFO);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QVariant PlusData(QVariant _X, QVariant _Y);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
