/*********************************************************************************************************
*名称：display.h
*功能：对OLED屏幕显示设置用到的头文件，包括函数的声明
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H
#include "config.h"	

void OLED_P6x8Str(uchar x, y,uchar ch[]);

void OLED_P8x16Str(uchar x, y,uchar ch[]);

void OLED_P16x16Ch(uchar x, y, N);

void Draw_BMP(uchar x0, y0,x1, y1,uchar BMP[]);


#endif