/*********************************************************************************************************
*���ƣ�OLED��ʾ��ʪ��
*���ܣ�����Ļ����ʾDHT11�������ʪ��
����ʱ�䣺2019/7/14
�޸�ʱ�䣺2019/7/30
���ߣ���ʫ��
*********************************************************************************************************/

#include "includes.h"

uint Temperature[3]={1,1,1};//ǰ��λΪ�������֣���һλΪС������
uint Humidity[2]={1,1};//���ص�ʪ������ֻ����������
uchar Data_Receive[5];

//#define PRINT_LOG

int main()
{
	P3M0=0X00; //0000,0000 �˿�3ģʽ�Ĵ���0
	P3M1=0X00;
	//sys_init();
#ifdef PRINT_LOG
	PrintUartInit();
#endif
	while(1)
	{
#ifdef PRINT_LOG
		printf("-------DHT_Collect start.....-----------\n\r");
#endif
		DHT_Collect();//DHT11���ݲɼ�
#ifdef PRINT_LOG
		printf("-------DHT_Collect end.....-----------\n\r");
#endif
		//YLED=1;RLED=0;//��״̬ת��
		//OLED_Display();//OLED��ʾ����
	//	RLED=1;YLED=0;//��״̬ת��
		delay_ms(1000);
		delay_ms(1000);//ע�⣺��ʱ�����ʱ����Ҫ�У���Ȼ�����0
	}
}

