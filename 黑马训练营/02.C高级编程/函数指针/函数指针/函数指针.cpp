#include <iostream>
#include<string>
using namespace std;

string LengthCompare(const string &ts,const string &ts2)
{
    return ts.size() > ts2.size() ? ts : ts2;
}

string(*pointer)(const string& ts, const string& ts2);

void test()
{
    pointer = LengthCompare;//等价于pointer = &LengthCompare;
    cout << pointer("Hello World", "Hello") << endl;
    cout << (*pointer)("Hello World", "Hello") << endl;
    cout << LengthCompare("Hello World", "Hello") << endl;
}

int main()
{
    test();
    return 0;
}