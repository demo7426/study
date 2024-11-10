/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	mainwindow.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.10
��  ��: LED��ˮ��
��  ע:  
�޸ļ�¼: 

  1.  ����: 2024.11.10
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/
#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(unsigned _Mes)		//@12.000MHz
{
	unsigned char i, j;

	while(_Mes--)
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
		P2 = 0xFE;
		Delay1ms(500);
		P2 = 0xFD;
		Delay1ms(500);
		P2 = 0xFB;
		Delay1ms(500);
		P2 = 0xF7;
		Delay1ms(500);
		P2 = 0xEF;
		Delay1ms(500);
		P2 = 0xDF;
		Delay1ms(500);
		P2 = 0xBF;
		Delay1ms(500);
		P2 = 0x7F;
		Delay1ms(500);

	}
	
}