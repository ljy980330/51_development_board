/*********************************************************************************************************
*名称：interrupt.h
*功能：数据类型及通用变量的声明及定义
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
*********************************************************************************************************/
#ifndef _OUTINTERRUPT_H
#define _OUTINTERRUPT_H
#include <STC12C5A.H>
#include "delay/delay.h"
#include "config.h"
#include "key/key.h"
void Int0Init();
void time0();
void time1();

#endif