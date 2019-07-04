/*********************************************************************************************************
*名称：ir.h
*功能：红外模块头文件，包括函数及变量的声明
创建时间：2019/XX/XX
修改时间：2019/6/5
作者：XXX
*********************************************************************************************************/

#ifndef _IR_H
#define _IR_H

#include <STC12C5A.H>
#include "config.h"
#include "delay/delay.h"
#include "smgdisplay/smgdisplay.h"

sbit IRIN  = P1^7;

extern U8 IRCOM[7];
extern U8 shuju[8];   //储存数码管显示的值

void IrInit(); //红外初始化
void IR_IN(); //红外值数据读取

#endif