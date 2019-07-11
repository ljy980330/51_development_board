/*********************************************************************************************************
*名称：LEDshanshuo.h
*功能：闪烁函数对应的头文件
创建时间：2019/7/4
修改时间：2019/7/4
作者：黄剑桥
*********************************************************************************************************/
#ifndef _LEDSHANSHUO_H
#define _LEDSHANSHUO_H
#include <STC12C5A.H>
#include "config.h"
#include "includes.h"
sbit LED1=P4^0;      //位定义，将stc12中的定义为LED
sbit LED2=P4^1; 
sbit LED3=P4^4;
sbit E3  =P2^3;		 //使能端 当该IO电平拉低时，LED全灭
void LED_Shan_Shuo(); 
#endif
