#ifndef _RTC_H
#define _RTC_H

void Time_Fun();								 //ʱ������ʱ����
void DS3231_Read_time();						 //��ȡʱ��
void DS3231_write_time();						 //д��ʱ��
void KeyDataProcess();							 //��ֵ������
void DS3231_Init();								 //ʱ��ģ���ʼ��
void Ram_init();
void main_init();
void delayms(uint x);							 //��ʱ����
void display1();								 //��ʾ����
void display2();
#endif