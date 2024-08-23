#include "Generate.h"
#include <QDebug>
#include <QThread>

CGenerate::CGenerate(QObject *parent)
    : QObject{parent}
{
    setAutoDelete(true);
}

void CGenerate::run()
{
    qDebug() << "子线程Id为： " << QThread::currentThreadId();

    for (int i = 0; i < 10; ++i) {
        qDebug() << "i = " << i;
    }
}

