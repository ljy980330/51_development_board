/*********************************************************************************************************
*名称：delay.h
*功能：延时所用到的头文件，包括函数的声明
创建时间：2019/7/14
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _DELAY_H
#define _DELAY_H
					  
#include <intrins.h>
#include "../config.h"

extern void Delay_30us();

extern void Delay_20ms();

extern void Delay_1s();

extern void Delay_ms(uint z);

extern void Delay_nop(uint counter);
extern void nop();

#endif


