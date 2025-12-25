#include "xviewer.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CXViewer window;

    QFile style(":/qss/style.qss");
    if (style.open(QIODevice::ReadOnly))
    {
        app.setStyleSheet(style.readAll());
    }

    window.show();
    return app.exec();
}
