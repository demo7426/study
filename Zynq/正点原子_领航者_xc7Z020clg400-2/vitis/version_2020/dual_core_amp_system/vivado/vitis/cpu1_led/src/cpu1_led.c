#include "xparameters.h"
#include "xscugic.h"
#include "xil_printf.h"
#include "xil_exception.h"
#include "xil_mmu.h"
#include "stdio.h"
#include "breath_led_ip.h"

//�궨��
#define INTC_DEVICE_ID	     XPAR_SCUGIC_SINGLE_DEVICE_ID //�ж�ID
#define SHARE_BASE  	     0xffff0000                   //����OCM�׵�ַ

#define CPU0_ID              XSCUGIC_SPI_CPU0_MASK        //CPU0 ID
#define SOFT_INTR_ID_TO_CPU0 0                            //����жϺ� 0 ,��Χ��0~15
#define SOFT_INTR_ID_TO_CPU1 1                            //����жϺ� 1 ,��Χ��0~15

#define  LED_IP_BASEADDR     XPAR_BREATH_LED_IP_0_S0_AXI_BASEADDR //LED IP����ַ
#define  LED_IP_REG0         BREATH_LED_IP_S0_AXI_SLV_REG0_OFFSET //LED IP�Ĵ�����ַ0
#define  LED_IP_REG1         BREATH_LED_IP_S0_AXI_SLV_REG1_OFFSET //LED IP�Ĵ�����ַ1

//��������
void cpu1_intr_init(XScuGic *intc_ptr);
void soft_intr_handler(void *CallbackRef);

//ȫ�ֱ���
XScuGic Intc;               //�жϿ�������������ʵ��
int soft_intr_flag = 0;     //����жϵı�־
int freq_gear;              //Ƶ�ʵ�λ

//CPU1 main����
int main()
{
	int freq_step = 0;
	//S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0
	Xil_SetTlbAttributes(SHARE_BASE,0x14de2);    //����OCM��Cache����

	//CPU1�жϳ�ʼ��
	cpu1_intr_init(&Intc);
	//�򿪺�����
	BREATH_LED_IP_mWriteReg(LED_IP_BASEADDR, LED_IP_REG0, 1);//1
	while(1){
		if(soft_intr_flag){
			freq_gear = Xil_In8(SHARE_BASE);     //�ӹ���OCM�ж�������
			xil_printf("CUP1 Received data is %d\r\n",freq_gear) ;
			switch(freq_gear){
				case 1 : freq_step = 1;break;
				case 2 : freq_step = 3;break;
				case 3 : freq_step = 5;break;
				case 4 : freq_step = 7;break;
				case 5 : freq_step = 9;break;
				default : freq_step = 1;break;
			}
			//���ú�����Ƶ��,���λΪ1��������Ч
			BREATH_LED_IP_mWriteReg(LED_IP_BASEADDR,LED_IP_REG1,(0x80000000|freq_step));
			//����CPU0�����ж�
			XScuGic_SoftwareIntr(&Intc,SOFT_INTR_ID_TO_CPU0,CPU0_ID);
			soft_intr_flag = 0;
		}
	}
	return 0 ;
}

//CPU1�жϳ�ʼ��
void cpu1_intr_init(XScuGic *intc_ptr)
{
	//��ʼ���жϿ�����
	XScuGic_Config *intc_cfg_ptr;
	intc_cfg_ptr = XScuGic_LookupConfig(INTC_DEVICE_ID);
    XScuGic_CfgInitialize(intc_ptr, intc_cfg_ptr,
    		intc_cfg_ptr->CpuBaseAddress);
    //���ò����ж��쳣������
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
    		(Xil_ExceptionHandler)XScuGic_InterruptHandler, intc_ptr);
    Xil_ExceptionEnable();

    XScuGic_Connect(intc_ptr, SOFT_INTR_ID_TO_CPU1,
          (Xil_ExceptionHandler)soft_intr_handler, (void *)intc_ptr);

    XScuGic_Enable(intc_ptr, SOFT_INTR_ID_TO_CPU1); //CPU1����ж�
}

//����жϺ���
void soft_intr_handler(void *CallbackRef)
{
	xil_printf("This is CUP1,Soft Interrupt from CPU0\r\n") ;
	soft_intr_flag = 1;
}
