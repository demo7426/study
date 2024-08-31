#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#include<sys/types.h>
#include<sys/stat.h>

//必须使用绝对路径
int main(void)
{
	struct  stat _Stat;

	rename("D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/02.txt.txt", "D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/01.txt.txt");

	printf("%d\n", stat("D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/01.txt.txt", &_Stat));
	printf("文件大小：%d\n", _Stat.st_size);

	rename("D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/01.txt.txt", "D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/02.txt.txt");

	//remove("D:/C++练习/黑马训练营/C语言基础/获取文件属性/获取文件属性/02.txt.txt");//删除文件
	return EXIT_SUCCESS;
}
