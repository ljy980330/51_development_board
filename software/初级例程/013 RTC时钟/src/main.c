/*********************************************************************************************************
*���ƣ�RTCʱ��
*���ܣ�����rtc��OLED��Ļ����ʾʱ�� 
����ʱ�䣺2019/XX/XX
�޸�ʱ�䣺2019/6/5
���ߣ�XXX
*********************************************************************************************************/
#include "../src/includes.h"

/**********************************************������**********************************************/
void main()
{
	uchar send_buffer[100];
	
	UartPrintInit();
	DS3231_time_Init();					//��ʼ��ʱ��
	DS3231_Init();				//ģ���ʼ��

	while(1)
	{		
		DS3231_Read_time();
		Update_rtc_buffer();
		
		sprintf(send_buffer, "%c%c%c%c-%c%c-%c%c %c%c:%c%c:%c%c  week:%c%c  temp:%c%c"    , display_buff[0]+'0', display_buff[1]+'0'\
																						  , display_buff[2]+'0', display_buff[3]+'0'\
																						  , display_buff[4]+'0', display_buff[5]+'0'\
																						  , display_buff[6]+'0', display_buff[7]+'0'\
																						  , display_buff[8]+'0', display_buff[9]+'0'\
																						  , display_buff[10]+'0', display_buff[11]+'0'\
																						  , display_buff[12]+'0', display_buff[13]+'0'\
																						  , display_buff[14]+'0', display_buff[15]+'0'\
																						  , display_buff[16]+'0', display_buff[17]+'0');
		
		printf("%s\n\r\n\r", send_buffer);
		
		Delay_1s();
	}
}
