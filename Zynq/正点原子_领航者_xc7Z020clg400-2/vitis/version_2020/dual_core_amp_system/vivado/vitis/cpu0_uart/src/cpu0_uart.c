#include "xparameters.h"
#include "xscugic.h"
#include "xil_printf.h"
#include "xil_exception.h"
#include "xil_mmu.h"
#include "stdio.h"

//�궨��
#define INTC_DEVICE_ID	     XPAR_SCUGIC_SINGLE_DEVICE_ID //�ж�ID
#define SHARE_BASE           0xffff0000                   //����OCM�׵�ַ
#define CPU1_COPY_ADDR       0xfffffff0                   //���CPU1Ӧ����ʼ��ַ�ĵ�ַ
#define CPU1_START_ADDR      0x10000000                   //CPU1Ӧ����ʼ��ַ

#define CPU1_ID              XSCUGIC_SPI_CPU1_MASK        //CPU1 ID
#define SOFT_INTR_ID_TO_CPU0 0                            //����жϺ� 0 ,��Χ��0~15
#define SOFT_INTR_ID_TO_CPU1 1                            //����жϺ� 1 ,��Χ��0~15

//"SEV"ָ���CPU1����ת����Ӧ�ĳ���
#define sev()                __asm__("sev")               //C������Ƕ���д�� send eventָ��

//��������
void start_cpu1();
void cpu0_intr_init(XScuGic *intc_ptr);
void soft_intr_handler(void *CallbackRef);

//ȫ�ֱ���
XScuGic Intc;                    //�жϿ�������������ʵ��
int rec_freq_flag = 0;           //���յ�������Ƶ�����õı�־
int freq_gear;                   //Ƶ�ʵ�λ

//CPU0 main����
int main()
{
	//S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0
	Xil_SetTlbAttributes(SHARE_BASE,0x14de2);    //����OCM��Cache����

	//S=b1 TEX=b100 AP=b11, Domain=b1111, C=b0, B=b0
	Xil_SetTlbAttributes(CPU1_COPY_ADDR,0x14de2);//����0xfffffff0��Cache����

	//����CPU1
	start_cpu1();
	//CPU0�жϳ�ʼ��
	cpu0_intr_init(&Intc);
	while(1){
		if(rec_freq_flag == 0){
			xil_printf("This is CPU0,Please input the numbers 1~5 to change "
					"breath led frequency\r\n");
			scanf("%d",&freq_gear);
			if(freq_gear >= 1 && freq_gear <=5){
				xil_printf("You input number is %d\r\n",freq_gear);
				//����ĵ�ַ��д�����������
				Xil_Out8(SHARE_BASE,freq_gear);
				//��CPU1�����ж�
				XScuGic_SoftwareIntr(&Intc,SOFT_INTR_ID_TO_CPU1,CPU1_ID);
				rec_freq_flag = 1;
			}
			else{
				xil_printf("Error,The number range is 1~5\r\n");
				xil_printf("\r\n");
			}
		}
	}
	return 0 ;
}

//����CPU1�����ڹ̻�����
void start_cpu1()
{
	//�� CPU1_COPY_ADDR(0Xffffffff0)��ַд�� CPU1 �ķ����ڴ����ַ
	Xil_Out32(CPU1_COPY_ADDR, CPU1_START_ADDR);
	dmb();  //�ȴ��ڴ�д�����(ͬ��)
	sev();  //ͨ��"SEV"ָ���CPU1����ת����Ӧ�ĳ���
}

//CPU0�жϳ�ʼ��
void cpu0_intr_init(XScuGic *intc_ptr)
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

    XScuGic_Connect(intc_ptr, SOFT_INTR_ID_TO_CPU0,
          (Xil_ExceptionHandler)soft_intr_handler, (void *)intc_ptr);

    XScuGic_Enable(intc_ptr, SOFT_INTR_ID_TO_CPU0); //CPU0����ж�
}

//����жϺ���
void soft_intr_handler(void *CallbackRef)
{
	xil_printf("This is CPU0,Soft Interrupt from CPU1\r\n");
	xil_printf("\r\n");
	rec_freq_flag = 0;
}
