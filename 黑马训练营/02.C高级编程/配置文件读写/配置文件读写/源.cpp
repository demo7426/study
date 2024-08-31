#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

/// <summary>
/// ������Ϣ�ṹ��
/// </summary>
typedef struct _CONFIGMESSAGE
{
	char key[64];//����
	char Value[64];//ֵ
}CONFIGMESSAGE, *PCONFIGMESSAGE;

/// <summary>
/// ��ȡ�����ļ���Ч�к���
/// </summary>
/// <param name="FileName"></param>
/// <param name="lineNum"></param>
/// <returns></returns>
static int ReadConfigFile_NumberOfValidRows(const char* FileName, int* lineNum)
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		perror("ReadConfigFile_NumberOfValidRows fopen error!");
		return -1;
	}

	char cbuf[1024] = { NULL };
	int nLineNum = 0;
	while (fgets(cbuf, 1024, fp) != NULL)
	{
		if (strchr(cbuf, ':'))
			nLineNum++;
		
		memset(cbuf, 0, 1024);
	}

	fclose(fp);
	fp = NULL;

	*lineNum = nLineNum;
	return 0;
}

/// <summary>
/// ��ȡ�����ļ���Ϣ�����������ṹ����
/// </summary>
/// <param name="FileName"></param>
/// <param name="ConfigMessage"></param>
/// <param name="lineNum">��Ч����</param>
/// <returns></returns>
static int ReadConfigFile(const char* FileName, PCONFIGMESSAGE* ConfigMessage, const int lineNum)
{
	FILE* fp = fopen(FileName, "r");
	if (fp == NULL)
	{
		perror("ReadConfigFile fopen error!");
		return -1;
	}

	PCONFIGMESSAGE pStrConfigMessage = (PCONFIGMESSAGE)malloc(sizeof(CONFIGMESSAGE) * lineNum);

	char cbufArray[1024] = { NULL };
	int nLineNum = 0;
	char *pcPos = 0;
	while (fgets(cbufArray, 1024, fp) != NULL)
	{
		pcPos = strchr(cbufArray, ':');
		if (pcPos != NULL)
		{
			memset(pStrConfigMessage[nLineNum].key, 0, 64);
			memset(pStrConfigMessage[nLineNum].Value, 0, 64);

			strncpy(pStrConfigMessage[nLineNum].key, cbufArray, pcPos - cbufArray);
			strncpy(pStrConfigMessage[nLineNum].Value, pcPos + 1, strlen(pcPos + 1) - 1);//���з�����Ҫ����
			nLineNum++;
		}
		
		memset(cbufArray, 0, 1024);
	}

	fclose(fp);
	fp = NULL;
	*ConfigMessage = pStrConfigMessage;
	return 0;
}

/// <summary>
/// ������������ֵ
/// </summary>
/// <param name="ConfigMessage"></param>
/// <param name="key"></param>
/// <param name="Value"></param>
/// <param name="lineNum"></param>
/// <returns></returns>
static int GetValueByKey(PCONFIGMESSAGE ConfigMessage, const char* key, char** Value, const int lineNum)
{
	int nLineNum = 0;
	while (true)
	{
		if (!strcmp(ConfigMessage[nLineNum].key, key))
		{
			*Value = ConfigMessage[nLineNum].Value;
			break;
		}			
		else if (nLineNum >= lineNum - 1)
			return -1;

		nLineNum++;	
	}
	return 0;
}

int main(int argc, char argv[])
{
	int nlineNum = 0;
	PCONFIGMESSAGE pStrConfigMessage;
	const char* pcFileName = "config.txt";
	const char* pcKey = "heroInfo";//���ҵ�����

	if (ReadConfigFile_NumberOfValidRows(pcFileName, &nlineNum))
		throw "ReadConfigFile_NumberOfValidRows return error";

	if (ReadConfigFile(pcFileName, &pStrConfigMessage, nlineNum))
		throw "ReadConfigFile return error";
	
	char* pcValue = NULL;
	if (GetValueByKey(pStrConfigMessage, pcKey, &pcValue, nlineNum))
		throw "GetValueByKey return error";

	printf_s("%s:%s", pcKey, pcValue);

	free(pStrConfigMessage);
	pStrConfigMessage = NULL;
	return EXIT_SUCCESS;
}