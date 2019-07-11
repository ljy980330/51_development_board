/*********************************************************************************************************
*名称：data_read.h
*功能：读取数据所用到头文件以及函数声明
创建时间：2019/7/6
修改时间：2019/XX/XX
作者：XXX
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

