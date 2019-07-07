/*********************************************************************************************************
*名称：ChaoShengBo.h
*功能：超声波所用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
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