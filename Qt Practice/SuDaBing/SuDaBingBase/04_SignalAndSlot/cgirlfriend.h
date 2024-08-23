#ifndef CGIRLFRIEND_H
#define CGIRLFRIEND_H

#include <QObject>

class CGirlFriend : public QObject
{
    Q_OBJECT
public:
    explicit CGirlFriend(QObject *parent = nullptr);

signals:
    void Hungry();
    void Hungry(QString _FoodName);
};

#endif // CGIRLFRIEND_H
