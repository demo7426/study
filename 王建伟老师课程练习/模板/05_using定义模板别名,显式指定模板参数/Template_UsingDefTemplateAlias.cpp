#include"Template_UsingDefTemplateAlias.h"

namespace Template_UsingDefTemplateAlias_NameSpace 
{
	double Add(int _X, int _Y)
	{
		return _X + _Y;
	}

	void Test01()
	{
		//C++98й╣ож:
		_MapStr_T<int>::mapStr_T map01;
		map01.insert({ "MeiXi", 35 });

		for(auto var : map01)
		{
			cout << "Name:" << var.first <<"\t" << "	Age:" << var.second << endl;
		}

		mapT01_T02<string, unsigned short> map02;
		map02.insert({ "Lewandowski", 34 });

		putchar('\n');
		for (auto var : map02)
		{
			cout << "Name:" << var.first << "	Age:" << var.second << endl;
		}

		FuncPtr02<decltype(10.0), int, int> funcPtr02;
		funcPtr02 = Add;
		cout << funcPtr02(10, 20) << endl;
	}

}

