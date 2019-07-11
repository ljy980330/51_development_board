/*********************************************************************************************************
*名称：interrupt.h
*功能：数据类型及通用变量的声明及定义
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
*********************************************************************************************************/
#ifndef _INTERRUPT_H
#define _INTERRUPT_H
#include <STC12C5A.H>
#include "delay/delay.h"
#include "config.h"

sbit LED1=P4^0;      //位定义，定义三个LED灯
sbit LED2=P4^1; 
sbit LED3=P4^4; 
sbit key1=P4^5;		 //定三个按键
sbit key2=P4^6;
sbit buzz=P2^7;
void Int0Init();
void time0();
void time1();

#endif