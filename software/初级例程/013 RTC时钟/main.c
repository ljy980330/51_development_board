/*********************************************************************************************************
*���ƣ�RTCʱ��
*���ܣ�����rtc��OLED��Ļ����ʾʱ�� 
����ʱ�䣺2019/XX/XX
�޸�ʱ�䣺2019/6/5
���ߣ�XXX
*********************************************************************************************************/
#include "includes.h"
#include <string.h>
#include <stdio.h>
/**********************************************������**********************************************/
void main()
{			  
	uchar display[16];
	uint i;			
	UartPrintInit();

	DS3231_time_Init();			//��ʼ��ʱ��
	DS3231_Init();				//ģ���ʼ��   
	OLED_Init(); 
	while(1)
	{		 			 
		 
		DS3231_Read_time();
		Update_rtc_buffer();
		
		for(i=0;i<17;i++)
			display[i]=display_buff[i]+'0';
		display[i]='\0'; //�������Ҫ�����ַ��������� 

		printf(display);
		printf("\n");	

		OLED_P8x16Str(0,0,display);
			
			intToStr();
		displayAll();	
			
		Delay_ms(4000);
		OLED_CLS();//����
	}
}
