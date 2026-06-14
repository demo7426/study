#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFile style(":/style/qss/stylesheet.qss");
    if (style.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(style.readAll());
    }

    w.show();
    return a.exec();
}
