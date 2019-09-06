/*********************************************************************************************************
*名称：display.h
*功能：对OLED屏幕显示设置用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/30
作者：黄彦钊
*********************************************************************************************************/

#ifndef _DRIVE_H
#define _DRIVE_H

#include "config.h"
#include "display/display.h"
#include "function/function.h"
#include "OLED_Init/OLED_Init.h"
#include "delay/delay.h"
#include "STC12C5A.H"

void OLED_Display();

void DHT_Collect();

void sys_init();



#endif

