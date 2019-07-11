#ifndef _RTC_H
#define _RTC_H

void Time_Fun();								 //时基、走时函数
void DS3231_Read_time();						 //读取时间
void DS3231_write_time();						 //写入时间
void KeyDataProcess();							 //键值处理函数
void DS3231_Init();								 //时间模块初始化
void Ram_init();
void main_init();
void delayms(uint x);							 //延时函数
void display1();								 //显示函数
void display2();
#endif