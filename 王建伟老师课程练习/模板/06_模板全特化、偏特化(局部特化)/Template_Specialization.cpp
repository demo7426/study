#include "Template_Specialization.h"

using namespace Template_Specialization_NameSpace;

void Template_Specialization_NameSpace::Test01()
{
	CCaculator<double, int, int> cCaculator01;
	cCaculator01.Add<double>(10, 12);

	putchar('\n');
	CCaculator<int, int, int> cCaculator02;
	cCaculator02.Add(10, 12);

	putchar('\n');
	CCaculator<string, string, string> cCaculator03;
	cCaculator03.Add("I love", "China");

	putchar('\n');
	CCaculator<int, int&, int&> cCaculator04;
	cCaculator04.Add<int, int, int>(10, 12);

	putchar('\n');
	Mul<double>(2.1, 2);

	putchar('\n');
	Mul<int>(2.1f, 2.3f);
}
