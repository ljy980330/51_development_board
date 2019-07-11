/*********************************************************************************************************
*名称：DuLiKey.h
*功能：独立按键所用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
*********************************************************************************************************/
#ifndef _DULIKEY_H
#define _DULIKEY_H
#include <STC12C5A.H>
#include "config.h"
#include "delay/delay.h"
#include "smg/smgdisplay.h"

sbit KEY1=P4^5;				  //分别定义三个按键
sbit KEY2=P4^6;					 
sbit KEY3=P4^7;

void Key1();
extern U8 j;

#endif