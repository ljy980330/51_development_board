/*********************************************************************************************************
*名称：OLED_Init.h
*功能：延时所用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/30
作者：黄彦钊
**********************************************************************************************************/

#ifndef _OLED_INIT_H
#define _OLED_INIT_H

#include "config.h"
#include "delay/delay.h"
#include "function/function.h"

#define Brightness	0xCF	//11001111


void OLED_Init(void);

#endif