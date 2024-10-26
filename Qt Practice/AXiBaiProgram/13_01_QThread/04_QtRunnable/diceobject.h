#ifndef DICEOBJECT_H
#define DICEOBJECT_H

#include <QObject>
#include <QRunnable>

class CDiceObject : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit CDiceObject(QObject *parent = nullptr);

private:
    bool m_bPause = true;           //暂停标志
    bool m_bStop = false;           //停止标志
    quint32 m_unCurFreq = 0;        //次数

public:

    void StartThread(void);

    ///
    /// \brief StartThrowDice--开始投掷骰子
    /// \return
    ///
    int StartThrowDice(void);

    ///
    /// \brief StopThrowDice--停止投掷骰子
    /// \return
    ///
    int StopThrowDice(void);

    void StopThread(void);

protected:
    void run() override;

signals:
    ///
    /// \brief SendCurMsg--发送当前投掷骰子相关信息
    /// \param _CurFreq--当前投掷骰子次数
    /// \param _CurDiceRoll--当前投掷骰子点数
    ///
    void SendCurMsg(quint32 _CurFreq, quint8 _CurDiceRoll);
};

#endif // DICEOBJECT_H
