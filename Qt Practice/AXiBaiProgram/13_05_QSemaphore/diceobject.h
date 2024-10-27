#ifndef DICEOBJECT_H
#define DICEOBJECT_H

#include <QObject>
#include <QVector>
#include <QThread>

class CDiceProducer : public QThread
{
    Q_OBJECT
public:
    explicit CDiceProducer(QObject *parent = nullptr);

    enum class STATE:qint8
    {
        RUN = 1,
        WAIT,
    };

public:
    void StartThread(void);

    void StopThread(void);

protected:
    void run() override;

signals:
    ///
    /// \brief SendCurState--run函数当前内部运行状态
    /// \param _State
    ///
    void SendCurState(STATE _State);
};

class CDiceConsumer : public QThread
{
    Q_OBJECT
public:
    explicit CDiceConsumer(QObject *parent = nullptr);

    enum class STATE:qint8
    {
        RUN = 1,
        WAIT,
    };
public:
    void StartThread(void);

    void StopThread(void);

protected:
    void run() override;

signals:
    ///
    /// \brief SendCurMsg--发送当前投掷骰子相关信息
    /// \param _CurFreq--当前投掷骰子次数
    /// \param _CurData--当前数据
    ///
    void SendCurMsg(quint32 _CurFreq, QVector<quint32> _CurData);

    ///
    /// \brief SendCurState--run函数当前内部运行状态
    /// \param _State
    ///
    void SendCurState(STATE _State);
};

#endif // DICEOBJECT_H
