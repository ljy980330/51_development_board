/*********************************************************************************************************
*名称：smgdisplay.h
*功能：数码管显示所用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/7/5
作者：黄剑桥
*********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include <STC12C5A.H>
#include "config.h"

sbit DIO   = P0^0;				//串行数据输入
sbit RCLK  = P0^1;				//时钟脉冲信号——上升沿有效
sbit SCLK  = P0^2;				//打入信号————上升沿有效

extern uchar code DuanMa[18];
extern uchar code WeiMa[8];
extern uchar code shuju[10];

void Display (uchar JNdata); //向hc595传送一个字节
void DisplayAddr(uint j); //显示的数据

#endif