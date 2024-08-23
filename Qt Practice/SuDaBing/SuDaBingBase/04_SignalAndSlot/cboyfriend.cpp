#include "cboyfriend.h"
#include <QDebug>

CBoyFriend::CBoyFriend(QObject *parent)
    : QObject{parent}
{}

void CBoyFriend::Eat()
{
    qDebug() << "带你去吃麻辣烫";
}


void CBoyFriend::Eat(QString _FoodName)
{
    qDebug() << "带你去吃" << _FoodName;
}

