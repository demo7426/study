#pragma once
#include<iostream>

//namespace Overload_GlobalNewAndDelete
void* operator new(size_t _Size);
void operator delete(void* _Head);

void* operator new[](size_t _Size);
void operator delete[](void* _Head);
