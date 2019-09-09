/*********************************************************************************************************
*名称：i2c.c
*功能：IO口模拟I2C通信
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/
						  
#include "rtc-oled.h"	
#include "../display/display.h"	
#include "../rtc/rtc.h"				 
#include <stdio.h>

uchar year[5],month[5],day[5],hour[5],branch[5],second[5],week[5],temp[5];	
uint i;

void intToStr()
{	
	year[0]=display_buff[0]+'0';  
	year[1]=display_buff[1]+'0';  
	year[2]=display_buff[2]+'0';  
	year[3]=display_buff[3]+'0';  	
	year[4]='\0'; //这个很重要，是字符串结束符 
	
	month[0]=display_buff[4]+'0';  
	month[1]=display_buff[5]+'0'; 
	month[2]='\0';

	day[0]=display_buff[6]+'0';
	day[1]=display_buff[7]+'0';	
	day[2]='\0';
								
	hour[0]=display_buff[8]+'0';
	hour[1]=display_buff[9]+'0';
	hour[2]='\0';	 
								
	branch[0]=display_buff[10]+'0';
	branch[1]=display_buff[11]+'0';
	branch[2]='\0';
								
	second[0]=display_buff[12]+'0';
	second[1]=display_buff[13]+'0';	
	second[2]='\0';

	week[0]=display_buff[14]+'0';
	week[1]=display_buff[15]+'0';  
	week[2]='\0'; 

	temp[0]=display_buff[16]+'0';
	temp[1]=display_buff[17]+'0';
	temp[2]='\0';
}	 

void displayAll()
{
//	OLED_P8x16Str(0,0,"AB");//第一行 -- 8x16的显示单元显示ASCII码
//	OLED_P8x16Str(10,0,month);									   
//	OLED_P8x16Str(0,1,day);
//	OLED_P8x16Str(10,1,hour);
//	OLED_P8x16Str(0,2,branch);


	OLED_P8x16Str(0,0,month);
		 
//	printf(year);
	printf(week);
	printf("\n");
}