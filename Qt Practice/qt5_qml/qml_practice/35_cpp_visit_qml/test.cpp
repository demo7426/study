#include <QDebug>
#include "test.h"

CTest::CTest(QObject *parent) : QObject(parent)  // 初始化父对象
{

}

void CTest::Print()
{
    qDebug() << __func__ << "is called.";
}

qint32 CTest::nAge() const
{
    return m_nAge;
}

void CTest::setNAge(const qint32 &nAge)
{
    m_nAge = nAge;
    emit nAgeChanged();
}

QString CTest::strName() const
{
    return m_strName;
}

void CTest::setStrName(const QString &strName)
{
    m_strName = strName;
    emit strNameChanged();
}
