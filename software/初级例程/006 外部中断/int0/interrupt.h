/*********************************************************************************************************
*���ƣ�interrupt.h
*���ܣ��������ͼ�ͨ�ñ���������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/7/5
���ߣ��ƽ���
*********************************************************************************************************/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H
#include <STC12C5A.H>
#include "delay/delay.h"
#include "config.h"

sbit LED1=P4^0;      //λ���壬��������LED��
sbit LED2=P4^1; 
sbit LED3=P4^4; 
sbit key1=P4^5;		 //����������
sbit key2=P4^6;
sbit buzz=P2^7;
void Int0Init();
void time0();
void time1();

#endif