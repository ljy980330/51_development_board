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

void OLED_P6x8Str(uchar x, y,uchar ch[]);

void OLED_P8x16Str(uchar x, y,uchar ch[]);

void OLED_P16x16Ch(uchar x, y, N);

void Draw_BMP(uchar x0, y0,x1, y1,uchar BMP[]);


#endif