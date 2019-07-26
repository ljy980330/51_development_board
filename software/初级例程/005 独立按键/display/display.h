/*********************************************************************************************************
*���ƣ�smgdisplay.h
*���ܣ��������ʾ���õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/7/5
���ߣ��ƽ���
*********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <STC12C5A.H>
#include "config.h"

sbit DIO   = P0^0;				//������������
sbit RCLK  = P0^1;				//ʱ�������źš�����������Ч
sbit SCLK  = P0^2;				//�����źš���������������Ч

extern uchar code DuanMa[18];
extern uchar code WeiMa[8];
extern uchar code shuju[10];

void Display (uchar JNdata); //��hc595����һ���ֽ�
void DisplayAddr(uint j); //��ʾ������

#endif