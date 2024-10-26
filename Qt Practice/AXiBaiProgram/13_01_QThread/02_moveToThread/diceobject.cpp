#include <QThread>
#include <thread>
#include <QDebug>

#include "diceobject.h"

#define USER_EXIR_SUCCESS 0
#define USER_EXIR_FAILURE -2

CDiceObject::CDiceObject(QObject *parent)
    : QObject{parent}
{}
void CDiceObject::StartThread(void)
{
    m_bStop = false;
}

int CDiceObject::StartThrowDice()
{
    m_bPause = false;

    return USER_EXIR_SUCCESS;
}

int CDiceObject::StopThrowDice()
{
    m_bPause = true;

    return USER_EXIR_SUCCESS;
}

void CDiceObject::StopThread()
{
    m_bStop = true;
    m_unCurFreq = 0;
}

void CDiceObject::Run()
{
    while (!m_bStop)
    {
        if(m_bPause)
            continue;

        m_unCurFreq++;
        emit SendCurMsg(m_unCurFreq, rand() % 6 + 1);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
