#include<iostream>
#include<ctime>

#include"Overload_NewAndDeleteOperators.h"
#include"OverloadsClassOperators_GreaterThan4Bytes.h"

using namespace std;

//减少了大量的内存浪费，malloc速度大概提升9倍(只针对Overload_NewAndDeleteOperators::CTeacher类)
void Test01()
{
	clock_t lStartTime =  clock();

	for (size_t i = 0; i < 5000'000; i++)
	{
		Overload_NewAndDeleteOperators::CTeacher* cTeaher = new Overload_NewAndDeleteOperators::CTeacher();
	}
	
	cout << "new次数：" << Overload_NewAndDeleteOperators::CTeacher::m_unNewCount << 
		"	malloc次数：" << Overload_NewAndDeleteOperators::CTeacher::m_unMallocCount << 
		"	new的时间为：" << clock() - lStartTime << "ms"  << endl;
}

//(针对大小大于4字节的类)
void Test02()
{
	OverloadsClassOperators_GreaterThan4Bytes::Test02();
}

int main(int argc, char* argv[])
{
	Test01();
	Test02();

	return EXIT_SUCCESS;
}

