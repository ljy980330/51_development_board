/*********************************************************************************************************
*名称：i2c.h
*功能：对i2c总线设置用到头文件，函数声明
创建时间：2019/7/5
修改时间：2019/XX/XX
作者：XXX
**********************************************************************************************************/

#ifndef _I2C_H
#define _I2C_H

#include <STC12C5A.H>
#include "../src/config.h"
#include "../src/delay/delay.h"

#define high 1	//高电平
#define low  0	//低电位

void IIC_Start(bit scl, bit sda, uint counter);

void IIC_Stop(bit scl, bit sda, uint counter);

#endif