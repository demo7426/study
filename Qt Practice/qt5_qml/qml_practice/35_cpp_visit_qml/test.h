#ifndef CTEST_H
#define CTEST_H

#include <QObject>

class CTest: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString strName READ strName WRITE setStrName NOTIFY strNameChanged FINAL)
    Q_PROPERTY(qint32 nAge READ nAge WRITE setNAge NOTIFY nAgeChanged FINAL)
public:
    explicit CTest(QObject *parent = nullptr);  // 推荐添加父对象参数

    Q_INVOKABLE QString strName() const;
    Q_INVOKABLE void setStrName(const QString &strName);

    Q_INVOKABLE qint32 nAge() const;
    Q_INVOKABLE void setNAge(const qint32 &nAge);

signals:
    void strNameChanged();
    void nAgeChanged();

public slots:
    void Print();

private:
    QString m_strName = "xxx";
    qint32 m_nAge = 0;

};

#endif // CTEST_H
