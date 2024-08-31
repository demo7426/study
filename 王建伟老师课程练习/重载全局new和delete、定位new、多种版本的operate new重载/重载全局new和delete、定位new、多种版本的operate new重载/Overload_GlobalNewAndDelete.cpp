#include"Overload_GlobalNewAndDelete.h"

void* operator new(size_t _Size)
{
	void* pValue = malloc(_Size);
	return pValue;
}

void* operator new[](size_t _Size)
{
	void* pValue = malloc(_Size);
	return pValue;
}

void operator delete(void* _Head)
{
	free(_Head);
}

void operator delete[](void* _Head)
{
	free(_Head);
}