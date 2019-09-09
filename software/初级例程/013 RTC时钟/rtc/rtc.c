/*********************************************************************************************************
*名称：rtc.c
*功能：时钟模块包括的函数
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/

#include <STC12C5A.H>	   
#include <intrins.h>
#include "rtc.h"

uchar display_buff[16] = {0};
uchar RTC_Data[8];
uchar RTC_Data1[8];

code uchar rtc_address[8]={0x00,0x01,0x02,0x04,0x05,0x03,0x06,0x11};//秒分时日月周年 最低位读写位

void DS3231_IIC_delay()//IIC延时函数。延时4个机器周期。   
{
	_nop_();_nop_();_nop_();_nop_();
}

void DS3231_IIC_start()//起始信号
{   
     DS3231_IIC_SDA=1;
     DS3231_IIC_SCL=1;
     DS3231_IIC_delay();
     DS3231_IIC_SDA=0;
     DS3231_IIC_delay();
     DS3231_IIC_SCL=0;
}

void DS3231_IIC_stop()//停止信号
{
    DS3231_IIC_SDA=0;
    DS3231_IIC_delay();
    DS3231_IIC_SCL=1;
    DS3231_IIC_delay();
    DS3231_IIC_SDA=1;
    DS3231_IIC_delay();
}

bit DS3231_IIC_Tack()//接收应答
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

void DS3231_IIC_write_byte(uchar Data)//写入数据函数
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

uchar DS3231_IIC_read_byte()//读取数据函数
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

void DS3231_IIC_single_byte_write(uchar Waddr,uchar Data)//写入数据函数
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

uchar DS3231_IIC_single_byte_read(uchar Waddr)//读取数据函数
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

void DS3231_Read_time()//读取时间
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

void DS3231_write_time()//写入时间
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

void DS3231_Init()
{
    DS3231_IIC_SDA=1;
    DS3231_IIC_SCL=1;
    DS3231_IIC_single_byte_write(0x0e,0x0c);
}

/**************************************************************************
* 函数名称： Ram_init()
* 功能：     初始化时间
******************************************************************************/
void DS3231_time_Init(void)
{
	DS3231_Read_time();	                        //读取 秒分时日月周年
	if((!RTC_Data[6])&&(!RTC_Data[5])&&(!RTC_Data[4])&&(!RTC_Data[3])&&(!RTC_Data[2])&&(!RTC_Data[1])&&(!RTC_Data[0]))
	{
		RTC_Data[0]=0;       //秒      			//秒分时日月周年 最低位读写位
		RTC_Data[1]=0;		 //分
		RTC_Data[2]=12;		 //时
		RTC_Data[3]=3;		 //日
		RTC_Data[4]=11;		 //月
		RTC_Data[5]=2;		 //周
		RTC_Data[6]=15;		 //年
		DS3231_write_time();                    //写入 秒分时日月周年
	}
}

void Update_rtc_buffer(void)
{
	display_buff[0] = 2;
	display_buff[1] = 0;
	display_buff[2] = RTC_Data[6]/10;
	display_buff[3] = RTC_Data[6]%10;		//年
	                  
	display_buff[4] = RTC_Data[4]/10;
	display_buff[5] = RTC_Data[4]%10;		//月
	                  
	display_buff[6] = RTC_Data[3]/10;
	display_buff[7] = RTC_Data[3]%10;		//日
	                  
	display_buff[8] = RTC_Data[2]/10;
	display_buff[9] = RTC_Data[2]%10;		//时
	
	display_buff[10] = RTC_Data[1]/10;
	display_buff[11] = RTC_Data[1]%10;		//分
	                   
	display_buff[12] = RTC_Data[0]/10;
	display_buff[13] = RTC_Data[0]%10;		//秒
	                   
	display_buff[14] = RTC_Data[5]/10;
	display_buff[15] = RTC_Data[5]%10;		//星期
                       
	display_buff[16] = RTC_Data[7]/10;
	display_buff[17] = RTC_Data[7]%10;		//温度
}                      