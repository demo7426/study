#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

#include<sys/types.h>
#include<sys/stat.h>

//����ʹ�þ���·��
int main(void)
{
	struct  stat _Stat;

	rename("D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/02.txt.txt", "D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/01.txt.txt");

	printf("%d\n", stat("D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/01.txt.txt", &_Stat));
	printf("�ļ���С��%d\n", _Stat.st_size);

	rename("D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/01.txt.txt", "D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/02.txt.txt");

	//remove("D:/C++��ϰ/����ѵ��Ӫ/C���Ի���/��ȡ�ļ�����/��ȡ�ļ�����/02.txt.txt");//ɾ���ļ�
	return EXIT_SUCCESS;
}
