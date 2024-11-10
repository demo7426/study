/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	mainwindow.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.10
��  ��: ������������LED״̬,ʹ���������
��  ע:  
�޸ļ�¼: 

  1.  ����: 2024.11.10
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/
#include <REGX52.H>

void Delay(unsigned int _Ms)		//@12.000MHz
{
	unsigned char i, j;

	while(_Ms--)
	{
		i = 2;
		j = 239;
		do
		{
			while (--j);
		} while (--i);
	}
}

int main(void)
{
		while(1)
		{
			if(P3_1 == 0)
			{
				Delay(20);
				while(P3_1==0);
				Delay(20);
				P2_0 = ~P2_0;
			}
		}
}
