/*********************************************************************************************************
*名称：FengMingQi.h
*功能：蜂鸣器所用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
*********************************************************************************************************/
#ifndef _FENGMINGQI_H
#define _FENGMINGQI_H

#include <STC12C5A.H>
#include <INTRINS.H> 
#include "config.h"
#include "delay/delay.h"
sbit  buzz=P2^7;
extern U16 n; //n为节拍数变量
extern U16 code music_tab[186]; 
void delay_pinglu (U16 m);   //控制频率延时 
void int0();
void Feng_Ming_Qi();

#endif