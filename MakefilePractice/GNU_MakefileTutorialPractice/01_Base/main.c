#include <stdio.h>

int Add(int _X, int _Y);
int Minus(int _X, int _Y);

int main(int argc, char* argv[])
{
	int nValue[] = { 2, 1 };
	printf("%ld + %ld = %ld\n", nValue[0], nValue[1], Add(nValue[0], nValue[1]));
	printf("%ld - %ld = %ld\n", nValue[0], nValue[1], Minus(nValue[0], nValue[1]));
	return 0;
}
