/*********************************************************************************************************
*���ƣ�delay.h
*���ܣ���ʱ���õ���ͷ�ļ�����������������
����ʱ�䣺2019/7/14
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _DELAY_H
#define _DELAY_H
					  
#include <intrins.h>
#include "../config.h"

extern void Delay_30us();

extern void Delay_20ms();

extern void Delay_1s();

extern void Delay_ms(uint z);

extern void Delay_nop(uint counter);
extern void nop();

#endif


