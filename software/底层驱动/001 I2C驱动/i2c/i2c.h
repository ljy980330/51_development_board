/*********************************************************************************************************
*名称：i2c_set.h
*功能：	i2c设置所有用到的头文件以及函数的声明
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

void IIC_Init();

void IIC_Start();

void IIC_Stop();

void Write_IIC_Byte(uchar IIC_Byte);

uchar Read_IIC_Byte();

void Ack_I2C(bit a);


#endif

