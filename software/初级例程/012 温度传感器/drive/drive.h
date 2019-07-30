/*********************************************************************************************************
*���ƣ�display.h
*���ܣ���OLED��Ļ��ʾ�����õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/7/30
���ߣ�������
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

