/*********************************************************************************************************
*���ƣ�FengMingQi.h
*���ܣ����������õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/7/5
���ߣ��ƽ���
*********************************************************************************************************/
#ifndef _FENGMINGQI_H
#define _FENGMINGQI_H

#include <STC12C5A.H>
#include <INTRINS.H> 
#include "config.h"
#include "delay/delay.h"
sbit  buzz=P2^7;
extern U16 n; //nΪ����������
extern U16 code music_tab[186]; 
void delay_pinglu (U16 m);   //����Ƶ����ʱ 
void int0();
void Feng_Ming_Qi();

#endif