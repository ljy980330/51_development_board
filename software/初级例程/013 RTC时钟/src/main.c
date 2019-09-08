/*********************************************************************************************************
*名称：RTC时钟
*功能：利用rtc在OLED屏幕上显示时间 
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/
#include "../src/includes.h"

/**********************************************主函数**********************************************/
void main()
{
	uchar send_buffer[100];
	
	UartPrintInit();
	DS3231_time_Init();					//初始化时间
	DS3231_Init();				//模块初始化

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
