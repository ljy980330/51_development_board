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

sbit BB=P0^7;//blue����
sbit RR=P0^6;//red���
sbit GG=P0^5;//green�̵�


void Display1();
void Display2();
void Display3();

#endif


