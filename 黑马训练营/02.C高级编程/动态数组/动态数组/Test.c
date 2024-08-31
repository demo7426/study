#include"Test.h"

/// <summary>
/// ²âÊÔº¯Êý
/// </summary>
void TestFunc()
{
	DYNAMICARRAY* ptDynamicArray;

	ptDynamicArray = DynamicArry_Init(4);

	int nValue[5] = {10, 20, 30, 40, 50};
	DynamicArry_Insert(ptDynamicArray, 1, nValue);
	DynamicArry_Insert(ptDynamicArray, 2, &nValue[1]);
	DynamicArry_Insert(ptDynamicArray, 3, &nValue[2]);
	DynamicArry_Insert(ptDynamicArray, 4, &nValue[3]);
	//DynamicArry_Insert(ptDynamicArray, 5, &nValue[4]);

	int nValue1;
	for (size_t i = 1; i < 6; i++)
	{
		nValue1 = *(int*)(ptDynamicArray->pAddres[i]);
	}
	/*if (!ptDynamicArray)
	{
		free(ptDynamicArray);
		ptDynamicArray = NULL;
	}*/

}

int main(void)
{
	TestFunc();

	//system("pause");
	return EXIT_SUCCESS;
}