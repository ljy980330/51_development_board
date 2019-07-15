/*********************************************************************************************************
*名称：display.h
*功能：显示所用到的头文件以及函数声明
创建时间：2019/7/6
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "STC12C5A.H"
#include "config.h"
#include "intrins.h"
#include "delay/delay.h"

sbit BB=P0^7;//blue蓝灯
sbit RR=P0^6;//red红灯
sbit GG=P0^5;//green绿灯


void Display1();
void Display2();
void Display3();

#endif


