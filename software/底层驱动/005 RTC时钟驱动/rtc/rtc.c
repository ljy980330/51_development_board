/*********************************************************************************************************
*名称：rtc.c
*功能：ds3231时钟驱动函数
创建时间：2019/7/9
修改时间：2019/7/9
作者：黄彦钊
*********************************************************************************************************/
#include <STC12C5A.H> 
#include<intrins.h>
#include "rtc.h"	  
#include "delay/delay.h"	 
#include "i2c/i2c.h"


bit ack; //应答标志位

#define DS3231_WriteAddress 0xD0 //器件写地址 ************** 
#define DS3231_ReadAddress 0xD1 //器件读地址************** 
#define DS3231_SECOND 0x00 //秒 
#define DS3231_MINUTE 0x01 //分 
#define DS3231_HOUR 0x02 //时 
#define DS3231_WEEK 0x03 //星期 
#define DS3231_DAY 0x04 //日 
#define DS3231_MONTH 0x05 //月 
#define DS3231_YEAR 0x06 //年 
//闹铃1 
#define DS3231_SALARM1ECOND 0x07 //秒 
#define DS3231_ALARM1MINUTE 0x08 //分 
#define DS3231_ALARM1HOUR 0x09 //时 
#define DS3231_ALARM1WEEK 0x0A //星期/日 //闹铃2 
#define DS3231_ALARM2MINUTE 0x0b //分 
#define DS3231_ALARM2HOUR 0x0c //时
#define DS3231_ALARM2WEEK 0x0d //星期/日 
#define DS3231_CONTROL 0x0e //控制寄存器 
#define DS3231_STATUS 0x0f //状态寄存器 
#define BSY 2 //忙 
#define OSF 7 //振荡器停止标志 
#define DS3231_XTAL 0x10 //晶体老化寄存器 
#define DS3231_TEMPERATUREH 0x11 //温度寄存器高字节(8位) 
#define DS3231_TEMPERATUREL 0x12 //温度寄存器低字节(高2位) //************** 
uchar code dis_code[11]={0xc0,0xf9,0xa4,0xb0, // 0,1,2,3 
	0x99,0x92,0x82,0xf8,0x80,0x90, 0xff}; // 4,5,6,7,8,9,off 
uchar data dis_buf[8]; 
uchar data dis_index; 
uchar data dis_digit; 	 
/*******************************************************************************
* 函 数 名         : BCD2HEX
* 函数功能		   : BCD转换为Byte 
*******************************************************************************/
uchar BCD2HEX(uchar val) 
{ 
	uchar temp; 
	temp=val&0x0f; 
	val>>=4; 
	val&=0x0f; 
	val*=10; 
	temp+=val; 
	return temp; 
} 	 
/*******************************************************************************
* 函 数 名         : HEX2BCD
* 函数功能		   : B码转换为BCD码
*******************************************************************************/
uchar HEX2BCD(uchar val)  
{ 
	uchar i,j,k; 
	i=val/10; 
	j=val-i*10;
	k=j+(i<<4); 
	return k; 
} 
/*******************************************************************************
* 函 数 名         : write_byte
* 函数功能		   : 写入一位数据
*******************************************************************************/
uchar write_byte(uchar addr, uchar write_data) 
{ 
	I2C_Start(); 
	Write_I2C_Byte(DS3231_WriteAddress); 
	if (ack == 0) 
		return 0; 
	Write_I2C_Byte(addr); 
	if (ack == 0) 
		return 0; 
	Write_I2C_Byte(write_data); 
	if (ack == 0) 
		return 0; 
	I2C_Stop(); 
	delay_us(10); 
	return 1; 
} 	
/*******************************************************************************
* 函 数 名         : read_current
* 函数功能		   : 读取RcvByte返回数据并返回
*******************************************************************************/
uchar read_current()
{ 
	uchar read_data; 
	I2C_Start(); 
	Write_I2C_Byte(DS3231_ReadAddress); 
	if(ack==0) 
		return(0); 
	read_data = Read_I2C_Byte(); 
	Ack_I2C(1); 
	I2C_Stop(); 
	return read_data; 
} 	
/*******************************************************************************
* 函 数 名         : read_random
* 函数功能		   : 处理read_current返回数据并返回
*******************************************************************************/
uchar read_random(uchar random_addr) 
{ 
	I2C_Start(); 
	Write_I2C_Byte(DS3231_WriteAddress); 
	if(ack==0) 
		return(0); 
	Write_I2C_Byte(random_addr); 
	if(ack==0) 
		return(0); 
	return(read_current()); 
} 	
/*******************************************************************************
* 函 数 名         : ModifyTime
* 函数功能		   : 修改时间
*******************************************************************************/
void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec) 
{ 
	uchar temp=0; 
	temp=HEX2BCD(yea); 
	write_byte(DS3231_YEAR,temp); //修改年 
	temp=HEX2BCD(mon); 
	write_byte(DS3231_MONTH,temp); //修改月 
	temp=HEX2BCD(da); 
	write_byte(DS3231_DAY,temp); //修改日 
	temp=HEX2BCD(hou); 
	write_byte(DS3231_HOUR,temp); //修改时
	temp=HEX2BCD(min); 
	write_byte(DS3231_MINUTE,temp); //修改分 
	temp=HEX2BCD(sec); 
	write_byte(DS3231_SECOND,temp); //修改秒 
} 	 
/*******************************************************************************
* 函 数 名         : TimeDisplay
* 函数功能		   : 处理时间
*******************************************************************************/
void TimeDisplay(uchar Dhour,uchar Dmin,uchar Dsec)
{ 
	dis_buf[7]=dis_code[Dhour / 10]; // 时十位 
	dis_buf[6]=dis_code[Dhour % 10]; // 时个位 
	dis_buf[4]=dis_code[Dmin / 10]; // 分十位 
	dis_buf[3]=dis_code[Dmin % 10]; // 分个位 
	dis_buf[1]=dis_code[Dsec / 10]; // 秒十位 
	dis_buf[0]=dis_code[Dsec % 10]; // 秒个位 
	dis_buf[2]=0xbf; // 显示"-" 
	dis_buf[5]=0xbf; 
} 	  
/*******************************************************************************
* 函 数 名         : DateDisplay
* 函数功能		   : 处理日期
*******************************************************************************/
void DateDisplay(uchar Dyear,uchar Dmonth,uchar Dday)
{ 
	dis_buf[7]=dis_code[Dyear / 10]; // 年十位 
	dis_buf[6]=dis_code[Dyear % 10]; // 年个位 
	dis_buf[4]=dis_code[Dmonth / 10]; // 月十位 
	dis_buf[3]=dis_code[Dmonth % 10]; // 月个位 
	dis_buf[1]=dis_code[Dday / 10]; // 天十位 
	dis_buf[0]=dis_code[Dday % 10]; // 天个位 
	dis_buf[2]=0xbf; // 显示"-" 
	dis_buf[5]=0xbf; 
}  
/*******************************************************************************
* 函 数 名         : get_show_time
* 函数功能		   : 显示24小时制时间
*******************************************************************************/
void get_show_time() 
{ 
	uchar Htemp1,Htemp2,Mtemp1,Mtemp2,Stemp1,Stemp2; 
	Htemp1=read_random(DS3231_HOUR); //时 24小时制 
	Htemp1&=0x3f;
	Htemp2=BCD2HEX(Htemp1);
	Mtemp1=read_random(DS3231_MINUTE); //分 
	Mtemp2=BCD2HEX(Mtemp1); 
	Stemp1=read_random(DS3231_SECOND); //秒 
	Stemp2=BCD2HEX(Stemp1); 
	TimeDisplay(Htemp2,Mtemp2,Stemp2); 
} 	  
/*******************************************************************************
* 函 数 名         : get_show_date
* 函数功能		   : 显示日期
*******************************************************************************/
void get_show_date() 
{ 
	uchar Ytemp1,Ytemp2,Mtemp1,Mtemp2,Dtemp1,Dtemp2; 
	Ytemp1=read_random(DS3231_YEAR); //年 
	Ytemp2=BCD2HEX(Ytemp1); 
	Mtemp1=read_random(DS3231_MONTH); //月 
	Mtemp2=BCD2HEX(Mtemp1); 
	Dtemp1=read_random(DS3231_DAY); //日 
	Dtemp2=BCD2HEX(Dtemp1); 
	DateDisplay(Ytemp2,Mtemp2,Dtemp2); 
}	   
/*******************************************************************************
* 函 数 名         : get_show_Temperature
* 函数功能		   : 显示温度
*******************************************************************************/
void get_show_Temperature() 
{ 
	uchar Ttemp1,Ttemp2,Ttemp3,Ttemp4; 
	Ttemp1=read_random(DS3231_TEMPERATUREH); //温度 高字节 
	Ttemp2=BCD2HEX(Ttemp1); 
	Ttemp3=read_random(DS3231_TEMPERATUREL); //温度低字节 
	Ttemp4=BCD2HEX(Ttemp3); 
	DateDisplay(0,Ttemp2,Ttemp4); 
}
   