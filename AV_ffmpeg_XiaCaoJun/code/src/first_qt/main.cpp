#include "firstqt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstQt w;
    w.show();
    return a.exec();
}
