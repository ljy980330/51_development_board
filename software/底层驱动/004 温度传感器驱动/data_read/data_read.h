/*********************************************************************************************************
*���ƣ�data_read.h
*���ܣ���ȡ�������õ�ͷ�ļ��Լ���������
����ʱ�䣺2019/7/6
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _DATA_READ_H
#define _DATA_READ_H

#include "config.h"
#include "STC12C5A.H"
#include "delay/delay.h"

#define high	1
#define low		0

sbit DATA = P2^0;

SendData(U8 *a);

void  COM(void);

void RH(void);

void Text(void);


#endif

