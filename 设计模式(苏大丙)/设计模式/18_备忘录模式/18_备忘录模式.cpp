//文件描述：
//      实现一个备忘录模式（类似于数据保存、加载操作）
//作者：钱锐
//时间：2024/2/26
//修改记录：
//      2024/2/26     新建

#include <iostream>
#include <map>

using namespace std;

class CData
{
public:
    CData(string _Msg) : m_strMsg(_Msg)
    {}

    string GetMsg()
    {
        return m_strMsg;
    }

private:
    string m_strMsg = string();
};

class CGames
{
public:
    void SetGamesState(string _State)
    {
        m_strState = _State;
    }

    CData* GetGamesState()
    {
        return new CData(m_strState);
    }

    void LoadGamesState(CData* _pHistory)
    {
        cout << "------" << _pHistory->GetMsg() << endl;
    }

private:
    string m_strState = string();
};

class CRecoder
{
public:
    int Recoder(int _Index, CData* _pData)
    {
        if (m_mapDataInfo.find(_Index) != m_mapDataInfo.end())
            return -1;

        m_mapDataInfo.emplace(_Index, _pData);
        return 0;
    }

    CData* GetData(int _Index)
    {
        if (m_mapDataInfo.find(_Index) == m_mapDataInfo.end())
            return nullptr;

        return m_mapDataInfo[_Index];
    }

private:
    map<int, CData*> m_mapDataInfo;
};

int main()
{
    string strDatas[] = { "第一条数据信息","第二条数据信息","第三条数据信息","第四条数据信息","第五条数据信息" };
    CGames cGames; 
    CRecoder cRecoder;

    //记录数据
    for (int i = 0; i < sizeof(strDatas) / sizeof(strDatas[0]); i++)
    {
        cGames.SetGamesState(strDatas[i]);
        cRecoder.Recoder(i, cGames.GetGamesState());
    }

    //加载数据
    cout << "Load data." << endl;
    for (int i = 0; i < sizeof(strDatas) / sizeof(strDatas[0]); i++)
    {
        cGames.LoadGamesState(cRecoder.GetData(i));
    }

    return 0;
}


