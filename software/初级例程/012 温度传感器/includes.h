/*********************************************************************************************************
*���ƣ�includes.h
*���ܣ����е�ͷ�ļ��������ͷ�ļ��н��а���
����ʱ�䣺2019/7/14
�޸�ʱ�䣺2019/7/30
���ߣ�������
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
void PrintUartInit(void)//ʹ�ö�ʱ��1��Ϊ���ڲ����ʷ�����
{
    TH1 = 0xFD;	 //����11.0592mhz ��������Ϊ9600
    TL1 = TH1;
    TMOD |= 0x20;	 //��ʱ��1��ʽ2
    SCON = 0x50;	 //���ڽ���ʹ��
    ES = 1;			 //�����ж�ʹ��
    TR1 = 1;		 //��ʱ��1ʹ��
    TI = 1;			 //�����жϱ��λ����������
	EA = 1;
}

#endif