/*********************************************************************************************************
*���ƣ�ChaoShengBo.h
*���ܣ����������õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/7/5
���ߣ��ƽ���
*********************************************************************************************************/
#ifndef _ChaoShengBo_H
#define _ChaoShengBo_H
#include <STC12C5A.H>
#include "config.h"
#include "delay/delay.h"
#include "smgdisplay/smgdisplay.h"
#include <intrins.h>

sbit RX=P3^6;
sbit TX=P3^7;

extern unsigned int  time;
extern unsigned int  timer;
extern unsigned char posit;
extern unsigned long S;
extern bit      flag ;



void Conut();
void time0();
void time1();
void Initiali();
void CsbDisplay();


#endif