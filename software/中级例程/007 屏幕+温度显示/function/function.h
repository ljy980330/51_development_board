/*********************************************************************************************************
*���ƣ�function.h
*���ܣ���OLED�����õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/14
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
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