/*********************************************************************************************************
*名称：includes.h
*功能：所有的头文件都在这个头文件中进行包含
创建时间：2019/7/14
修改时间：2019/7/30
作者：黄彦钊
**********************************************************************************************************/

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "STC12C5A.H"				 
#include "stdio.h"
#include "config.h"
#include "OLED_Init/OLED_Init.h"
#include "delay/delay.h"
#include "code_tab/code_tab.h"
#include "display/display.h"
#include "function/function.h"
#include "i2c/i2c.h"
#include "drive/drive.h"

extern void PrintUartInit(void);
void PrintUartInit(void)//使用定时器1作为串口波特率发生器
{
    TH1 = 0xFD;	 //晶振11.0592mhz 波特率设为9600
    TL1 = TH1;
    TMOD |= 0x20;	 //定时器1方式2
    SCON = 0x50;	 //串口接收使能
    ES = 1;			 //串口中断使能
    TR1 = 1;		 //定时器1使能
    TI = 1;			 //发送中断标记位，必须设置
	EA = 1;
}

#endif