#include <STC12C5A.H>
#ifndef __IIC_H
#define __IIC_H

sbit DS3231_IIC_SDA=P0^0;
sbit DS3231_IIC_SCL=P0^1;
void DS3231_Read_time();						 //��ȡʱ��
void DS3231_write_time();						 //д��ʱ��
void DS3231_Init();								 //ʱ��ģ���ʼ��
#endif  