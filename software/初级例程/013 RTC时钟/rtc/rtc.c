/*********************************************************************************************************
*���ƣ�rtc.c
*���ܣ�ʱ��ģ������ĺ���
����ʱ�䣺2019/XX/XX
�޸�ʱ�䣺2019/6/5
���ߣ�XXX
*********************************************************************************************************/

#include <STC12C5A.H>	   
#include <intrins.h>
#include "rtc.h"

uchar display_buff[16] = {0};
uchar RTC_Data[8];
uchar RTC_Data1[8];

code uchar rtc_address[8]={0x00,0x01,0x02,0x04,0x05,0x03,0x06,0x11};//���ʱ�������� ���λ��дλ

void DS3231_IIC_delay()//IIC��ʱ��������ʱ4���������ڡ�   
{
	_nop_();_nop_();_nop_();_nop_();
}

void DS3231_IIC_start()//��ʼ�ź�
{   
     DS3231_IIC_SDA=1;
     DS3231_IIC_SCL=1;
     DS3231_IIC_delay();
     DS3231_IIC_SDA=0;
     DS3231_IIC_delay();
     DS3231_IIC_SCL=0;
}

void DS3231_IIC_stop()//ֹͣ�ź�
{
    DS3231_IIC_SDA=0;
    DS3231_IIC_delay();
    DS3231_IIC_SCL=1;
    DS3231_IIC_delay();
    DS3231_IIC_SDA=1;
    DS3231_IIC_delay();
}

bit DS3231_IIC_Tack()//����Ӧ��
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

void DS3231_IIC_write_byte(uchar Data)//д�����ݺ���
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

uchar DS3231_IIC_read_byte()//��ȡ���ݺ���
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

void DS3231_IIC_single_byte_write(uchar Waddr,uchar Data)//д�����ݺ���
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

uchar DS3231_IIC_single_byte_read(uchar Waddr)//��ȡ���ݺ���
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

void DS3231_Read_time()//��ȡʱ��
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

void DS3231_write_time()//д��ʱ��
{
    uchar i,tmp;
    for(i=0;i<7;i++)
    {       
        tmp=RTC_Data[i]/10;//BCD����
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
* �������ƣ� Ram_init()
* ���ܣ�     ��ʼ��ʱ��
******************************************************************************/
void DS3231_time_Init(void)
{
	DS3231_Read_time();	                        //��ȡ ���ʱ��������
	if((!RTC_Data[6])&&(!RTC_Data[5])&&(!RTC_Data[4])&&(!RTC_Data[3])&&(!RTC_Data[2])&&(!RTC_Data[1])&&(!RTC_Data[0]))
	{
		RTC_Data[0]=0;       //��      			//���ʱ�������� ���λ��дλ
		RTC_Data[1]=0;		 //��
		RTC_Data[2]=12;		 //ʱ
		RTC_Data[3]=3;		 //��
		RTC_Data[4]=11;		 //��
		RTC_Data[5]=2;		 //��
		RTC_Data[6]=15;		 //��
		DS3231_write_time();                    //д�� ���ʱ��������
	}
}

void Update_rtc_buffer(void)
{
	display_buff[0] = 2;
	display_buff[1] = 0;
	display_buff[2] = RTC_Data[6]/10;
	display_buff[3] = RTC_Data[6]%10;		//��
	                  
	display_buff[4] = RTC_Data[4]/10;
	display_buff[5] = RTC_Data[4]%10;		//��
	                  
	display_buff[6] = RTC_Data[3]/10;
	display_buff[7] = RTC_Data[3]%10;		//��
	                  
	display_buff[8] = RTC_Data[2]/10;
	display_buff[9] = RTC_Data[2]%10;		//ʱ
	
	display_buff[10] = RTC_Data[1]/10;
	display_buff[11] = RTC_Data[1]%10;		//��
	                   
	display_buff[12] = RTC_Data[0]/10;
	display_buff[13] = RTC_Data[0]%10;		//��
	                   
	display_buff[14] = RTC_Data[5]/10;
	display_buff[15] = RTC_Data[5]%10;		//����
                       
	display_buff[16] = RTC_Data[7]/10;
	display_buff[17] = RTC_Data[7]%10;		//�¶�
}                      