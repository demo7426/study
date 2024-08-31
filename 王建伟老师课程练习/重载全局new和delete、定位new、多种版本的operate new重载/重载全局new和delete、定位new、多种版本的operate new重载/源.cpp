#include<iostream>
#include<string>

#include"Overload_GlobalNewAndDelete.h"

int main(int argc, char* argv[])
{
	int* pnValue = new int[10];
	
	std::cout << *pnValue;
	return EXIT_SUCCESS;
}