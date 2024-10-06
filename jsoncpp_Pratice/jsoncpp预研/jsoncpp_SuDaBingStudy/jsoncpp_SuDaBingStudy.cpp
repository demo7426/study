
#include <iostream>
#include <fstream>
#include "json/json.h"

using namespace std;
using namespace Json;

/// <summary>
/// 向指定文件写入json格式的数据
/// </summary>
/// <param name="_FilePath">文件路径</param>
static void WriteJson(const string& _FilePath)
{
    if (_FilePath.empty())
        return;

    Value root;
    root.append("luffy");
    root.append(19);
    root.append(170);
    root.append(false);

    Value subArray;
    subArray.append("ace");
    subArray.append("sabo");
    root.append(subArray);

    Value subObj;
    subObj["sex"] = "man";
    subObj["girlFriend"] = "Hancock";
    root.append(subObj);
    
#if 1
    string strJson = root.toStyledString();         //带换行符的Json数据
#else
    FastWriter cFastWriter;
    string strJson = cFastWriter.write(root);       //不带换行符的Json数据
#endif // 1

    ofstream ofc(_FilePath);
    ofc << strJson;
    ofc.close();
}

/// <summary>
/// 解析指定文件json格式的数据
/// </summary>
/// <param name="_FilePath">文件路径</param>
static void ReadJson(const string& _FilePath)
{
    if (_FilePath.empty())
        return;

    ifstream ifs(_FilePath);
    Reader rd;
    Value root;
    rd.parse(ifs, root);

    if (root.isArray())
    {
        for (int i = 0; i < root.size(); i++)
        {
            Value item = root[i];

            if (item.isInt())
                cout << item.asInt() << ",\n";
            else if (item.isString())
                cout << item.asString() << ",\n";
            else if (item.isBool())
                cout << item.asBool() << ",\n";
            else if (item.isDouble())
                cout << item.asDouble() << ",\n";
            else if (item.isArray())
            {
                for (int i = 0; i < item.size(); i++)
                {
                    cout << item[i].asString() << ",\n";
                }
            }
            else if (item.isObject())
            {
                Value::Members vecKeys = item.getMemberNames();

                for (int i = 0; i < vecKeys.size(); i++)
                {
                    cout << vecKeys.at(i) << ":" << item[vecKeys.at(i)];

                    if(i != vecKeys.size() - 1)
                        cout << ",\n";
                }
            }


        }
    }
    else
    {
    }

}

int main()
{
    const string strFilePath = "Test.txt";

    WriteJson(strFilePath);
    ReadJson(strFilePath);

    return EXIT_SUCCESS;
}

