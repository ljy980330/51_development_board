/*********************************************************************************************************
*���ƣ�display.h
*���ܣ���ʾ���õ���ͷ�ļ��Լ���������
����ʱ�䣺2019/7/6
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "STC12C5A.H"
#include "config.h"
#include "intrins.h"
#include "delay/delay.h"

sbit BB=P1^0;//blue����
sbit RR=P1^1;//red���
sbit GG=P1^2;//green�̵�


void Display1();
void Display2();
void Display3();

#endif


