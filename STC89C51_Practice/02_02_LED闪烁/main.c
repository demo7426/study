/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	mainwindow.h
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.07
��  ��: ����һ��LED��
��  ע:  
�޸ļ�¼: 

  1.  ����: 2024.11.07
      ����: Ǯ��
      ����:
          1) ��Ϊģ���һ���汾;
      �汾:V0.1.0

*************************************************/

#include <REGX52.H>
#include <INTRINS.H>

static void Delay500ms()		//@12.000MHz
{
	unsigned char i, j, k;

	_nop_();
	i = 4;
	j = 205;
	k = 187;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


int main()
{
	while(1)
	{
		P2 = 0xfe;
		Delay500ms();

		P2 = 0xff;
		Delay500ms();
	}
	
	return 0;
}
