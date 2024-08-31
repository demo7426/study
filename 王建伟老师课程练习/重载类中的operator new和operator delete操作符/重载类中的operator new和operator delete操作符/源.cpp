#include<iostream>
#include<ctime>

#include"Overload_NewAndDeleteOperators.h"
#include"OverloadsClassOperators_GreaterThan4Bytes.h"

using namespace std;

//�����˴������ڴ��˷ѣ�malloc�ٶȴ������9��(ֻ���Overload_NewAndDeleteOperators::CTeacher��)
void Test01()
{
	clock_t lStartTime =  clock();

	for (size_t i = 0; i < 5000'000; i++)
	{
		Overload_NewAndDeleteOperators::CTeacher* cTeaher = new Overload_NewAndDeleteOperators::CTeacher();
	}
	
	cout << "new������" << Overload_NewAndDeleteOperators::CTeacher::m_unNewCount << 
		"	malloc������" << Overload_NewAndDeleteOperators::CTeacher::m_unMallocCount << 
		"	new��ʱ��Ϊ��" << clock() - lStartTime << "ms"  << endl;
}

//(��Դ�С����4�ֽڵ���)
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

