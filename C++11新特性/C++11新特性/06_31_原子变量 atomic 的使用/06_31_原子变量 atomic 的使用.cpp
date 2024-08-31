/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
文件名:	06_31_原子变量 atomic 的使用.cpp
作  者:	钱锐      版本: V1.0.0     新建日期: 2024.07.07
描  述: 原子操作只能支持整型和指针，不能支持浮点型和复合类型（比如结构体、联合体等）
备  注:
修改记录:

  1.  日期: 2024.07.07
	  作者: 钱锐
	  内容:
		  1) 此为模板第一个版本；
	  版本:V1.0.0

*************************************************/

#include <iostream>
#include <atomic>

int Test01(void)
{
	std::atomic<char> cAtomicValue01('a');
	std::atomic<char> cAtomicValue02;

	std::atomic_init(&cAtomicValue02, 'b');

	cAtomicValue01 = 'c';
	cAtomicValue01.store('e');

	char chValue = cAtomicValue01.exchange('f');

	std::cout << chValue << " " << cAtomicValue01.load() << " " << cAtomicValue02 << std::endl;

	return EXIT_SUCCESS;
}

int main()
{
	Test01();

	return EXIT_SUCCESS;
}
