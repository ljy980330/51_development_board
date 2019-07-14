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
#include "function/function.h"
#include "i2c/i2c.h"
#include "code_tab/code_tab.h"

void OLED_FormName(uchar x, y);

void OLED_FormLine(uchar x, y);

void OLED_FormTitle(uchar x,y);

void OLED_FormTemp(uchar x,y);

void OLED_FormHumi(uchar x,y);

void OLED_AnyChar_16X16(uchar x, y,uchar anystr_temp[]);

void OLED_AnyChar_8X16(uchar x, y,uchar anystr_temp[]);

void OLED_DataDisplay_H(uchar x, y,uint display_temp[]);

void OLED_DataDisplay_T(uchar x, y,uint display_temp[]);

void OLED_P16x16Ch(uchar x, y, N);

#endif
