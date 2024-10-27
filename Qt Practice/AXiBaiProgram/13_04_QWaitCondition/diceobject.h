#ifndef DICEOBJECT_H
#define DICEOBJECT_H

#include <QObject>

class CDiceProducer : public QObject
{
    Q_OBJECT
public:
    explicit CDiceProducer(QObject *parent = nullptr);

private:
    bool m_bStop = false;           //停止标志

public:
    void StartThread(void);

    void StopThread(void);

public slots:
    void Run();
};

class CDiceConsumer : public QObject
{
    Q_OBJECT
public:
    explicit CDiceConsumer(QObject *parent = nullptr);

private:
    bool m_bStop = false;           //停止标志

public:
    void StartThread(void);

    void StopThread(void);

public slots:
    void Run();

signals:
    ///
    /// \brief SendCurMsg--发送当前投掷骰子相关信息
    /// \param _CurFreq--当前投掷骰子次数
    /// \param _CurDiceRoll--当前投掷骰子点数
    ///
    void SendCurMsg(quint32 _CurFreq, quint8 _CurDiceRoll);

};

#endif // DICEOBJECT_H
