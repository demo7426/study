#ifndef CBOYFRIEND_H
#define CBOYFRIEND_H

#include <QObject>

class CBoyFriend : public QObject
{
    Q_OBJECT
public:
    explicit CBoyFriend(QObject *parent = nullptr);

public slots:
    void Eat();
    void Eat(QString _FoodName);

signals:
};

#endif // CBOYFRIEND_H
