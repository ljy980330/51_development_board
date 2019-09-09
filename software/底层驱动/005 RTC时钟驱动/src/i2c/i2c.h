/*********************************************************************************************************
*���ƣ�i2c.h
*���ܣ���i2c���������õ�ͷ�ļ�����������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _I2C_H
#define _I2C_H

#include <STC12C5A.H>
#include "../src/config.h"
#include "../src/delay/delay.h"

#define high 1	//�ߵ�ƽ
#define low  0	//�͵�λ

void IIC_Start(bit scl, bit sda, uint counter);

void IIC_Stop(bit scl, bit sda, uint counter);

#endif