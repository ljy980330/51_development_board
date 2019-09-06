/*********************************************************************************************************
*名称：function.h
*功能：对OLED设置用到的头文件，包括函数的声明
创建时间：2019/7/14
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "config.h"
#include "i2c/i2c.h"

#define X_WIDTH	128
#define Y_WIDTH	64

void OLED_WrCmd(uchar IIC_Command);

void OLED_WrDat(uchar IIC_Data);

void OLED_Set_Pos(uchar x, uchar y);

void OLED_Fill(uchar bmp_dat);

void OLED_CLS(void);

#endif