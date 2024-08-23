#ifndef CGENERATE_H
#define CGENERATE_H

#include <QObject>
#include <QRunnable>

class CGenerate : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit CGenerate(QObject *parent = nullptr);

    void run() final;

signals:
};

#endif // CGENERATE_H
