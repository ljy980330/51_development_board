#ifndef _RTC_H
#define _RTC_H

#include "../src/i2c/i2c.h"
#include "../src/delay/delay.h"

sbit DS3231_IIC_SDA=P4^1;
sbit DS3231_IIC_SCL=P4^0;

/*****************************************DS3231��������***********************************************/
extern uchar display_buff[];
extern	uchar RTC_Data[];
extern uchar RTC_Data1[];

extern void DS3231_Read_time(void);						 //��ȡʱ��
extern void DS3231_write_time(void);						 //д��ʱ��
extern void DS3231_Init(void);								 //ʱ��ģ���ʼ��
extern void DS3231_time_Init(void);
extern void Update_rtc_buffer(void);


#endif