/*********************************************************************************************************
*名称：iic.c
*功能：iic包括的函数
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/
#include <STC12C5A.H>
#include <intrins.h>
#include "iic.h"	 
#include "config.h"	
#include "delay/delay.h"

uchar display_buff[16];
uchar RTC_Data[8];
uchar RTC_Data1[8];
uchar RTC_Set_ID;
code uchar rtc_address[8]={0x00,0x01,0x02,0x04,0x05,0x03,0x06,0x11};//秒分时日月周年 最低位读写位
		
/*******************************************************************************
* 函 数 名         : DS3231_IIC_delay
* 函数功能		   : IIC延时函数。延时4个机器周期。   
*******************************************************************************/			 
void DS3231_IIC_delay()
{
	nop(4);
}				

/*******************************************************************************
* 函 数 名         : DS3231_IIC_start
* 函数功能		   : 起始信号
*******************************************************************************/
void DS3231_IIC_start()
{   
     DS3231_IIC_SDA=1;
     DS3231_IIC_SCL=1;
     DS3231_IIC_delay();
     DS3231_IIC_SDA=0;
     DS3231_IIC_delay();
     DS3231_IIC_SCL=0;
}
	
/*******************************************************************************
* 函 数 名         : DS3231_IIC_stop
* 函数功能		   : 停止信号
*******************************************************************************/
void DS3231_IIC_stop()
{
    DS3231_IIC_SDA=0;
    DS3231_IIC_delay();
    DS3231_IIC_SCL=1;
    DS3231_IIC_delay();
    DS3231_IIC_SDA=1;
    DS3231_IIC_delay();
}
	 
/*******************************************************************************
* 函 数 名         : DS3231_IIC_Tack
* 函数功能		   : 接收应答
*******************************************************************************/
bit DS3231_IIC_Tack()
{
    bit ack;
    DS3231_IIC_SDA=1;
    DS3231_IIC_delay();
    DS3231_IIC_SCL=1;
    DS3231_IIC_delay();
    ack=DS3231_IIC_SDA;
    DS3231_IIC_delay();
    DS3231_IIC_SCL=0;
    DS3231_IIC_delay();
    return ack;
}
	
/*******************************************************************************
* 函 数 名         : DS3231_IIC_write_byte
* 函数功能		   : 写入数据函数
*******************************************************************************/
void DS3231_IIC_write_byte(uchar Data)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if(Data&0x80)
		DS3231_IIC_SDA=1;
		else
		DS3231_IIC_SDA = 0;
		DS3231_IIC_delay();
		DS3231_IIC_SCL=1; 
		DS3231_IIC_delay();
		DS3231_IIC_SCL=0;
		DS3231_IIC_delay();
		Data=Data<<1;
	}
}
   
/*******************************************************************************
* 函 数 名         : DS3231_IIC_read_byte
* 函数功能		   : 读取数据函数
*******************************************************************************/
uchar DS3231_IIC_read_byte()
{
    uchar i;
    uchar Data;       
    for(i=0;i<8;i++)
    {
        DS3231_IIC_SCL=1;
        DS3231_IIC_delay();
        Data=Data<<1;
        DS3231_IIC_delay();
       
        if(DS3231_IIC_SDA)
        Data=Data|0x01;
        DS3231_IIC_SCL=0;
        DS3231_IIC_delay();
    }
    return Data;
}
/*******************************************************************************
* 函 数 名         : DS3231_IIC_single_byte_write
* 函数功能		   : 写入数据函数
*******************************************************************************/
void DS3231_IIC_single_byte_write(uchar Waddr,uchar Data)
{
    DS3231_IIC_start();
    DS3231_IIC_write_byte(0xd0);
    DS3231_IIC_Tack();
    DS3231_IIC_write_byte(Waddr);
    DS3231_IIC_Tack();
    DS3231_IIC_write_byte(Data);
    DS3231_IIC_Tack();
    DS3231_IIC_stop();
}
/*******************************************************************************
* 函 数 名         : DS3231_IIC_single_byte_read
* 函数功能		   : 读取数据函数
*******************************************************************************/
uchar DS3231_IIC_single_byte_read(uchar Waddr)
{
    uchar Data;
    DS3231_IIC_start();
    DS3231_IIC_write_byte(0xd0);
    DS3231_IIC_Tack();
    DS3231_IIC_write_byte(Waddr);
    DS3231_IIC_Tack();
    DS3231_IIC_stop();
    DS3231_IIC_start();
    DS3231_IIC_write_byte(0xd1);
    DS3231_IIC_Tack();
    Data=DS3231_IIC_read_byte();
    DS3231_IIC_delay();
    DS3231_IIC_stop();
    return Data;
}
/*******************************************************************************
* 函 数 名         : DS3231_Read_time
* 函数功能		   : 读取时间
*******************************************************************************/
void DS3231_Read_time()
{
    uchar i,tmp,tmp1,tmp2;         
    for(i=0;i<8;i++)
    {
    	tmp = DS3231_IIC_single_byte_read(rtc_address[i]);
    	tmp1 = tmp/16;
    	tmp2 = tmp%16;
		RTC_Data[i]=tmp1*10+tmp2;
    }   
}
/*******************************************************************************
* 函 数 名         : DS3231_write_time
* 函数功能		   : 写入时间
*******************************************************************************/
void DS3231_write_time()
{
    uchar i,tmp;
    for(i=0;i<7;i++)
    {       
        tmp=RTC_Data[i]/10;//BCD处理
        RTC_Data1[i]=RTC_Data[i]%10;
        RTC_Data1[i]=RTC_Data1[i]+tmp*16;
    } 
    for(i=0;i<7;i++)
    {
        DS3231_IIC_single_byte_write(rtc_address[i],RTC_Data1[i]);
    }
    DS3231_IIC_single_byte_write(0x0e,0x0c);
}
/*******************************************************************************
* 函 数 名         : DS3231_Init
* 函数功能		   : DS3231初始化
*******************************************************************************/
void DS3231_Init()
{
    DS3231_IIC_SDA=1;
    DS3231_IIC_SCL=1;
    DS3231_IIC_single_byte_write(0x0e,0x0c);
}