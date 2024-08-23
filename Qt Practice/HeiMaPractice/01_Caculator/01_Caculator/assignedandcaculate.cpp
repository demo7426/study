#include "assignedandcaculate.h"

AssignedAndCaculate::AssignedAndCaculate(QObject *parent) : QObject(parent)
{

}

void AssignedAndCaculate::Assignment()
{
    QString btnObj= ((QPushButton*)sender())->text(); //获取按钮txt文字

    this->m_strBuf += btnObj;
    m_pLCDNumber->setText(m_strBuf);
}

void AssignedAndCaculate::Clear()
{
    m_strBuf.clear();
    m_pLCDNumber->setText(m_strBuf);
}

void AssignedAndCaculate::Caculate()
{
    double dbMinuend = 0;			//被操作数
    double dbResults = 0;			//中间计算结果

    QList<QString> ListStr;

    ParsingString_Into_ListContainer(m_strBuf, &ListStr);

    if(ListStr.size() == 1)
        dbResults = ListStr.front().toDouble();
    else
    {
        dbMinuend = ListStr.front().toDouble();
        ListStr.pop_front();
        if(ListStr.front() == "+")
        {
            ListStr.pop_front();
            dbResults = dbMinuend + ListStr.front().toDouble();
        }
        else if(ListStr.front() == "-")
        {
            ListStr.pop_front();
            dbResults = dbMinuend - ListStr.front().toDouble();
        }
        else if(ListStr.front() == "*")
        {
            ListStr.pop_front();
            dbResults = dbMinuend * ListStr.front().toDouble();
        }
        else if(ListStr.front() == "/")
        {
            ListStr.pop_front();
            dbResults = dbMinuend * ListStr.front().toDouble();
        }

        ListStr.pop_front();
    }
    m_dbResults = dbResults;

    m_pLCDNumber->setText(QString::number(m_dbResults, 10, 8));
    m_strBuf.clear();
}

AssignedAndCaculate::~AssignedAndCaculate()
{
}

bool AssignedAndCaculate::Is_Isdent(QChar c)
{
    int nRtn = 0;
    (c == '.' || (c >= '0' && c <= '9')) ? nRtn = true : nRtn = false;
    return nRtn;
}

int AssignedAndCaculate::ParsingString_Into_ListContainer(const QString TargetStr, QList<QString>* ListStr)
{
    QString StrInfixEx = TargetStr;
    QList<QString> ListStr_Data;		//将字符串拆分后未排序放入的容器
    QString StrTemp;					//暂存字符串
    QChar chTemp;					//暂存字符
    int j;

    //将字符串中的数据解析出来放入List容器中
    for (int i = 0; i < StrInfixEx.length(); i++)
    {
        j = 1;
        chTemp = StrInfixEx[i + j - 1];

        StrTemp+=StrInfixEx[i];

        if ((i + j) < StrInfixEx.length() &&
            (chTemp == '.' || chTemp == '0' || chTemp == '1' || chTemp == '2' || chTemp == '3' || chTemp == '4' ||
                chTemp == '5' || chTemp == '6' || chTemp == '7' || chTemp == '8' || chTemp == '9'))//防止数据越界
        {
            chTemp = StrInfixEx[i + j];
            while (Is_Isdent(chTemp))//取出具体数字
            {
                StrTemp += StrInfixEx[i + j];

                j++;
                chTemp = StrInfixEx[i + j];
            }

            i += (StrTemp.length() - 1);
        }

        ListStr_Data.push_back(StrTemp);
        StrTemp.clear();
    }

    *ListStr = ListStr_Data;
    return EXIT_SUCCESS;
}
