/*********************************************************************************************************
*���ƣ�rtc.c
*���ܣ�ds3231ʱ����������
����ʱ�䣺2019/7/9
�޸�ʱ�䣺2019/7/9
���ߣ�������
*********************************************************************************************************/
#include <STC12C5A.H> 
#include<intrins.h>
#include "rtc.h"	  
#include "delay/delay.h"	 
#include "i2c/i2c.h"


bit ack; //Ӧ���־λ

#define DS3231_WriteAddress 0xD0 //����д��ַ ************** 
#define DS3231_ReadAddress 0xD1 //��������ַ************** 
#define DS3231_SECOND 0x00 //�� 
#define DS3231_MINUTE 0x01 //�� 
#define DS3231_HOUR 0x02 //ʱ 
#define DS3231_WEEK 0x03 //���� 
#define DS3231_DAY 0x04 //�� 
#define DS3231_MONTH 0x05 //�� 
#define DS3231_YEAR 0x06 //�� 
//����1 
#define DS3231_SALARM1ECOND 0x07 //�� 
#define DS3231_ALARM1MINUTE 0x08 //�� 
#define DS3231_ALARM1HOUR 0x09 //ʱ 
#define DS3231_ALARM1WEEK 0x0A //����/�� //����2 
#define DS3231_ALARM2MINUTE 0x0b //�� 
#define DS3231_ALARM2HOUR 0x0c //ʱ
#define DS3231_ALARM2WEEK 0x0d //����/�� 
#define DS3231_CONTROL 0x0e //���ƼĴ��� 
#define DS3231_STATUS 0x0f //״̬�Ĵ��� 
#define BSY 2 //æ 
#define OSF 7 //����ֹͣ��־ 
#define DS3231_XTAL 0x10 //�����ϻ��Ĵ��� 
#define DS3231_TEMPERATUREH 0x11 //�¶ȼĴ������ֽ�(8λ) 
#define DS3231_TEMPERATUREL 0x12 //�¶ȼĴ������ֽ�(��2λ) //************** 
uchar code dis_code[11]={0xc0,0xf9,0xa4,0xb0, // 0,1,2,3 
	0x99,0x92,0x82,0xf8,0x80,0x90, 0xff}; // 4,5,6,7,8,9,off 
uchar data dis_buf[8]; 
uchar data dis_index; 
uchar data dis_digit; 	 
/*******************************************************************************
* �� �� ��         : BCD2HEX
* ��������		   : BCDת��ΪByte 
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
* �� �� ��         : HEX2BCD
* ��������		   : B��ת��ΪBCD��
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
* �� �� ��         : write_byte
* ��������		   : д��һλ����
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
* �� �� ��         : read_current
* ��������		   : ��ȡRcvByte�������ݲ�����
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
* �� �� ��         : read_random
* ��������		   : ����read_current�������ݲ�����
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
* �� �� ��         : ModifyTime
* ��������		   : �޸�ʱ��
*******************************************************************************/
void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec) 
{ 
	uchar temp=0; 
	temp=HEX2BCD(yea); 
	write_byte(DS3231_YEAR,temp); //�޸��� 
	temp=HEX2BCD(mon); 
	write_byte(DS3231_MONTH,temp); //�޸��� 
	temp=HEX2BCD(da); 
	write_byte(DS3231_DAY,temp); //�޸��� 
	temp=HEX2BCD(hou); 
	write_byte(DS3231_HOUR,temp); //�޸�ʱ
	temp=HEX2BCD(min); 
	write_byte(DS3231_MINUTE,temp); //�޸ķ� 
	temp=HEX2BCD(sec); 
	write_byte(DS3231_SECOND,temp); //�޸��� 
} 	 
/*******************************************************************************
* �� �� ��         : TimeDisplay
* ��������		   : ����ʱ��
*******************************************************************************/
void TimeDisplay(uchar Dhour,uchar Dmin,uchar Dsec)
{ 
	dis_buf[7]=dis_code[Dhour / 10]; // ʱʮλ 
	dis_buf[6]=dis_code[Dhour % 10]; // ʱ��λ 
	dis_buf[4]=dis_code[Dmin / 10]; // ��ʮλ 
	dis_buf[3]=dis_code[Dmin % 10]; // �ָ�λ 
	dis_buf[1]=dis_code[Dsec / 10]; // ��ʮλ 
	dis_buf[0]=dis_code[Dsec % 10]; // ���λ 
	dis_buf[2]=0xbf; // ��ʾ"-" 
	dis_buf[5]=0xbf; 
} 	  
/*******************************************************************************
* �� �� ��         : DateDisplay
* ��������		   : ��������
*******************************************************************************/
void DateDisplay(uchar Dyear,uchar Dmonth,uchar Dday)
{ 
	dis_buf[7]=dis_code[Dyear / 10]; // ��ʮλ 
	dis_buf[6]=dis_code[Dyear % 10]; // ���λ 
	dis_buf[4]=dis_code[Dmonth / 10]; // ��ʮλ 
	dis_buf[3]=dis_code[Dmonth % 10]; // �¸�λ 
	dis_buf[1]=dis_code[Dday / 10]; // ��ʮλ 
	dis_buf[0]=dis_code[Dday % 10]; // ���λ 
	dis_buf[2]=0xbf; // ��ʾ"-" 
	dis_buf[5]=0xbf; 
}  
/*******************************************************************************
* �� �� ��         : get_show_time
* ��������		   : ��ʾ24Сʱ��ʱ��
*******************************************************************************/
void get_show_time() 
{ 
	uchar Htemp1,Htemp2,Mtemp1,Mtemp2,Stemp1,Stemp2; 
	Htemp1=read_random(DS3231_HOUR); //ʱ 24Сʱ�� 
	Htemp1&=0x3f;
	Htemp2=BCD2HEX(Htemp1);
	Mtemp1=read_random(DS3231_MINUTE); //�� 
	Mtemp2=BCD2HEX(Mtemp1); 
	Stemp1=read_random(DS3231_SECOND); //�� 
	Stemp2=BCD2HEX(Stemp1); 
	TimeDisplay(Htemp2,Mtemp2,Stemp2); 
} 	  
/*******************************************************************************
* �� �� ��         : get_show_date
* ��������		   : ��ʾ����
*******************************************************************************/
void get_show_date() 
{ 
	uchar Ytemp1,Ytemp2,Mtemp1,Mtemp2,Dtemp1,Dtemp2; 
	Ytemp1=read_random(DS3231_YEAR); //�� 
	Ytemp2=BCD2HEX(Ytemp1); 
	Mtemp1=read_random(DS3231_MONTH); //�� 
	Mtemp2=BCD2HEX(Mtemp1); 
	Dtemp1=read_random(DS3231_DAY); //�� 
	Dtemp2=BCD2HEX(Dtemp1); 
	DateDisplay(Ytemp2,Mtemp2,Dtemp2); 
}	   
/*******************************************************************************
* �� �� ��         : get_show_Temperature
* ��������		   : ��ʾ�¶�
*******************************************************************************/
void get_show_Temperature() 
{ 
	uchar Ttemp1,Ttemp2,Ttemp3,Ttemp4; 
	Ttemp1=read_random(DS3231_TEMPERATUREH); //�¶� ���ֽ� 
	Ttemp2=BCD2HEX(Ttemp1); 
	Ttemp3=read_random(DS3231_TEMPERATUREL); //�¶ȵ��ֽ� 
	Ttemp4=BCD2HEX(Ttemp3); 
	DateDisplay(0,Ttemp2,Ttemp4); 
}
   