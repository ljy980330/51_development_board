/*********************************************************************************************************
*���ƣ�rtc.h
*���ܣ��ⲿ���õ���rtc������������
����ʱ�䣺2019/7/8
�޸�ʱ�䣺2019/7/8
���ߣ�������
*********************************************************************************************************/
#include <STC12C5A.H>	
#include "config.h"	 
#ifndef __IIC_H
#define __IIC_H

uchar write_byte(uchar addr, uchar write_data);
void ModifyTime(uchar yea,uchar mon,uchar da,uchar hou,uchar min,uchar sec); //��ʼ��ʱ��,ModifyTime(10,6,13,15,30,00)=2010/6/13,15/30/00
void get_show_date();	//��ʾ���� 
void get_show_Temperature(); //��ʾ�¶�
void get_show_time();	//��ʾʱ�� 
#endif  