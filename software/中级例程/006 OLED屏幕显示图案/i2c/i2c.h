/*********************************************************************************************************
*名称：i2c.h
*功能：对i2c总线设置用到头文件，函数声明
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _I2C_H
#define _I2C_H

#include "config.h"
#include "STC12C5A.H"
#include "delay/delay.h"

#define high 1	//高电平
#define low  0	//低电位

sbit SCL=P0^4; //串行时钟
sbit SDA=P0^3; //串行数据

void IIC_Start();

void IIC_Stop();

void Write_IIC_Byte(U8 IIC_Byte);

#endif