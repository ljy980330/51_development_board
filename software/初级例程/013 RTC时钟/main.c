/*********************************************************************************************************
*名称：RTC时钟
*功能：利用rtc在OLED屏幕上显示时间 
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/
#include "includes.h"
#include <string.h>
#include <stdio.h>
/**********************************************主函数**********************************************/
void main()
{			  
	uchar display[16];
	uint i;			
	UartPrintInit();

	DS3231_time_Init();			//初始化时间
	DS3231_Init();				//模块初始化   
	OLED_Init(); 
	while(1)
	{		 			 
		 
		DS3231_Read_time();
		Update_rtc_buffer();
		
		for(i=0;i<17;i++)
			display[i]=display_buff[i]+'0';
		display[i]='\0'; //这个很重要，是字符串结束符 

		printf(display);
		printf("\n");	

		OLED_P8x16Str(0,0,display);
			
			intToStr();
		displayAll();	
			
		Delay_ms(4000);
		OLED_CLS();//清屏
	}
}
