/*************************************************
Copyright (C), 2009-2012    , Level Chip Co., Ltd.
�ļ���:	main.c
��  ��:	Ǯ��      �汾: V0.1.0     �½�����: 2024.11.10
��  ��: ��̬�������ʾ
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

//�������ʾ�Ӻ���
void SetNixieTube(unsigned char _NixieNo, unsigned char _Num)
{
	//����ܶ����
	unsigned char NixieTable[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
	
	switch(_NixieNo)
	{
		case 1: 	P2_4 = 1; P2_3 = 1; P2_2 = 1; break;
		case 2: 	P2_4 = 1; P2_3 = 1; P2_2 = 0; break;
		case 3: 	P2_4 = 1; P2_3 = 0; P2_2 = 1; break;
		case 4: 	P2_4 = 1; P2_3 = 0; P2_2 = 0; break;
		case 5: 	P2_4 = 0; P2_3 = 1; P2_2 = 1; break;
		case 6: 	P2_4 = 0; P2_3 = 1; P2_2 = 0; break;
		case 7: 	P2_4 = 0; P2_3 = 0; P2_2 = 1; break;
		case 8: 	P2_4 = 0; P2_3 = 0; P2_2 = 0; break;
		default:
			break;
	}
	
	P0 = NixieTable[_Num];
	
	Delay(5);		//�����������ʾ���쵼�µĲ�Ӱ
	P0 = 0xFF;
}

int main(void)
{
	SetNixieTube(1, 1);
	SetNixieTube(2, 2);
	SetNixieTube(3, 3);
	
	return 0;
}
