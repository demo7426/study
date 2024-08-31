#include"DynamicArray.h"

PDYNAMICARRAY DynamicArry_Init(UINT32 Capacity)
{
	PDYNAMICARRAY ptDynamicArray = malloc(sizeof(DYNAMICARRAY));
	if (!ptDynamicArray)
	{
		perror("DynamicArry_Init: malloc DYNAMICARRAY fail_1!!!");
		return EXIT_FAILURE;
	}

	ptDynamicArray->pAddres = malloc(sizeof(void*) * Capacity);
	if (!ptDynamicArray->pAddres)
	{
		perror("DynamicArry_Init: malloc DYNAMICARRAY fail_2!!!");
		return EXIT_FAILURE;
	}

	ptDynamicArray->Capacity = Capacity;
	ptDynamicArray->Size = 0;

	//保证结构体内函数的正确调用

	return ptDynamicArray;
}

INT32 DynamicArry_Insert(PDYNAMICARRAY tpDynamicArray, UINT32 Position, void* data)
{
	tpDynamicArray->Size++;

	if (tpDynamicArray->Size > tpDynamicArray->Capacity)
	{
		void** pTemp = malloc(sizeof(void*) * (tpDynamicArray->Capacity + 1));
		if (!pTemp)
		{
			perror("DynamicArry_Insert: malloc fail!!!");
			return EXIT_FAILURE;
		}

		memcpy(pTemp, tpDynamicArray->pAddres, tpDynamicArray->Capacity);

		if (pTemp != tpDynamicArray->pAddres)
			free(tpDynamicArray->pAddres);

		tpDynamicArray->pAddres = pTemp;
	}

	//尾插
	if (Position < 0 || Position > tpDynamicArray->Size)
	{
		tpDynamicArray->pAddres[tpDynamicArray->Size] = data;
		return EXIT_SUCCESS;
	}

	//移动元素，插入新元素
	for (int i = tpDynamicArray->Size - 1; i >= Position; i--)
	{
		tpDynamicArray->pAddres[i + 1] = tpDynamicArray->pAddres[i];
	}

	tpDynamicArray->pAddres[Position] = data;

	int nValue = *(int*)data;


	return EXIT_SUCCESS;
}


