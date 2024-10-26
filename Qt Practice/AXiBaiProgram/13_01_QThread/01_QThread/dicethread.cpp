/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	mythread.cpp
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

#include <QtMath>
#include <QTime>

#include "dicethread.h"

#define USER_EXIR_SUCCESS 0
#define USER_EXIR_FAILURE -2

CDiceThread::CDiceThread(QObject *parent)
    : QThread{parent}
{
    srand(QTime::currentTime().msec());     //设置随机数种子
}

void CDiceThread::StartThread(void)
{
    m_bStop = false;

    this->start();
}

int CDiceThread::StartThrowDice()
{
    m_bPause = false;

    return USER_EXIR_SUCCESS;
}

int CDiceThread::StopThrowDice()
{
    m_bPause = true;

    return USER_EXIR_SUCCESS;
}

void CDiceThread::StopThread()
{
    m_bStop = true;
    m_unCurFreq = 0;

    this->wait();
}

void CDiceThread::run()
{
    while (!m_bStop)
    {
        if(m_bPause)
        {
            this->yieldCurrentThread();
            continue;
        }

        m_unCurFreq++;
        emit SendCurMsg(m_unCurFreq, rand() % 6 + 1);
        msleep(200);
    }

    this->quit();           //相当于调用exit(0);
}
