#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#define MyAddFunc(tx, ty) (tx + ty)//ºêº¯Êý

int main()
{
	Assert.AreEqual(0, LtMci6_1112.LMC_SetLinearMotionInfo(1, 2, nAxes));
    Assert.AreEqual(0, LtMci6_1112.LMC_SetLinearMotionProfile(1, 0, 0, 1000000, 100000, 100000, 0));
	Assert.AreEqual(0, LtMci6_1112.LMC_CT_Start(0));
	
	return EXIT_SUCCESS;
}
