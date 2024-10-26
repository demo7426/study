/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mythread.h
作  者:	钱锐      版本: V0.1.0     新建日期: 2024.10.26
描  述:	继承QThread实现线程
备  注:
修改记录:

  1.  日期: 2024.10.26
      作者: 钱锐
      内容:
          1) 此为模板第一个版本；
      版本:V0.1.0

*************************************************/

#ifndef DICETHREAD_H
#define DICETHREAD_H

#include <QObject>
#include <QThread>

class CDiceThread : public QThread
{
    Q_OBJECT
public:
    explicit CDiceThread(QObject *parent = nullptr);

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

#endif // DICETHREAD_H
