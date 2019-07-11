/*********************************************************************************************************
*���ƣ�function.h
*���ܣ���OLED�����õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "config.h"
#include "i2c/i2c.h"

#define X_WIDTH	128
#define Y_WIDTH	64

void OLED_WrCmd(U8 IIC_Command);

void OLED_WrDat(U8 IIC_Data);

void OLED_Set_Pos(U8 x, U8 y);

void OLED_Fill(U8 bmp_dat);

void OLED_CLS(void);

#endif