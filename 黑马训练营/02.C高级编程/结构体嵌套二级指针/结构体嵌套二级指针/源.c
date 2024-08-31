#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

int g_nTeacherNum = 0;//老师数量
int g_nStudentNum = 0;//学生数量

typedef struct _TEACHER
{
	char* Name;
	char** Student;
}TEACHER, *PTEACHER;

/// <summary>
/// 分配内存
/// </summary>
/// <param name="tpppTeacher">三级TEACHER指针</param>
/// <param name="TeacherNum">老师数量</param>
/// <param name="StudentNum">学生数量</param>
void AllocateSpace(TEACHER*** tpppTeacher, const int TeacherNum, const int StudentNum)
{
	if (*tpppTeacher != NULL)
	{
		perror("AllocateSpace tpppTeacher != NULL\n");
		return;
	}

	//分配所有老师的指针数组内存
	TEACHER** tppTemp_Teacher = malloc(sizeof(TEACHER*) * TeacherNum);
	if (!tppTemp_Teacher)
	{
		perror("AllocateSpace malloc fail_1!\n");
		return;
	}
	
	for (int i = 0; i < TeacherNum; i++)
	{
		//分配每个老师的内存
		*(tppTemp_Teacher + i) = malloc(sizeof(TEACHER));//等同于tppTemp_Teacher[i] = malloc(sizeof(TEACHER));
		if (!*(tppTemp_Teacher + i))
		{
			perror("AllocateSpace malloc fail_2!\n");
			return;
		}

		//分配每个老师名称的内存
		tppTemp_Teacher[i]->Name = malloc(sizeof(char) * 64);
		if (!tppTemp_Teacher[i]->Name)
		{
			perror("AllocateSpace malloc fail_3!\n");
			return;
		}

		//给老师取名字
		sprintf(tppTemp_Teacher[i]->Name, "techer_%d", i);

		//给学生名称数组分配内存
		tppTemp_Teacher[i]->Student = malloc(sizeof(char*) * StudentNum);
		if (!tppTemp_Teacher[i]->Student)
		{
			perror("AllocateSpace malloc fail_4!\n");
			return;
		}

		//给每个学生名称分配内存
		for (int j = 0; j < StudentNum; j++)
		{
			tppTemp_Teacher[i]->Student[j] = malloc(sizeof(char) * 64);
			if (!tppTemp_Teacher[i]->Student[j])
			{
				perror("AllocateSpace malloc fail_5!\n");
				return;
			}

			//给学生取名字
			sprintf(tppTemp_Teacher[i]->Student[j], "teacher_%d_student_%d", i, j);
		}
	}

	*tpppTeacher = tppTemp_Teacher;
	g_nTeacherNum = TeacherNum;
	g_nStudentNum = StudentNum;
}

/// <summary>
/// 打印数据
/// </summary>
/// <param name="tppTeacher"></param>
void MyPrintf(TEACHER** tppTeacher)
{
	for (int i = 0; i < g_nTeacherNum; i++)
	{
		printf("老师名称：%s\n", tppTeacher[i]->Name);
		for (size_t j = 0; j < g_nStudentNum; j++)
		{
			printf("	学生名称：%s\n", tppTeacher[i]->Student[j]);
		}
	}
}

/// <summary>
/// 释放内存
/// </summary>
/// <param name="tppTeacher"></param>
void FreeSpace(TEACHER** tppTeacher)
{
	for (int i = 0; i < g_nTeacherNum; i++)
	{
		
		for (size_t j = 0; j < g_nStudentNum; j++)
		{
			if (!tppTeacher[i]->Student[j])
			{
				free(tppTeacher[i]->Student[j]);
				tppTeacher[i]->Student[j] = NULL;
			}
		}

		if (!tppTeacher[i]->Student)
		{
			free(tppTeacher[i]->Student);
			tppTeacher[i]->Student = NULL;
		}

		if (!tppTeacher[i]->Name)
		{
			free(tppTeacher[i]->Name);
			tppTeacher[i]->Name = NULL;
		}

		if (!tppTeacher[i])
		{
			free(tppTeacher[i]);
			tppTeacher[i] = NULL;
		}
	}

	if (!tppTeacher)
	{
		free(tppTeacher);
		tppTeacher = NULL;
	}
}

void Test01()
{
	TEACHER** tppTeacher = NULL;

	AllocateSpace(&tppTeacher, 3, 4);
	MyPrintf(tppTeacher);
	FreeSpace(tppTeacher);
}

int main(void)
{
	Test01();
	return EXIT_SUCCESS;
}
