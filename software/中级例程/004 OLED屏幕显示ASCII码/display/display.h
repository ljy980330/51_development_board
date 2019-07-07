/*********************************************************************************************************
*���ƣ�display.h
*���ܣ���OLED��Ļ��ʾ�����õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _DISPLAY_H
#define _DISPLAY_H

#include "config.h"
#include "code_tab/code_tab.h"
#include "function/function.h"


void OLED_P6x8Str(U8 x, y,U8 ch[]);

void OLED_P8x16Str(U8 x, y,U8 ch[]);

void OLED_P16x16Ch(U8 x, y, N);

void Draw_BMP(U8 x0, y0,x1, y1,U8 BMP[]);


#endif