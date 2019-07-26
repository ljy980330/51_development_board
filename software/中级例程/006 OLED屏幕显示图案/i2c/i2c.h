/*********************************************************************************************************
*���ƣ�i2c.h
*���ܣ���i2c���������õ�ͷ�ļ�����������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _I2C_H
#define _I2C_H

#include "config.h"
#include "STC12C5A.H"
#include "delay/delay.h"

#define high 1	//�ߵ�ƽ
#define low  0	//�͵�λ

sbit SCL=P0^4; //����ʱ��
sbit SDA=P0^3; //��������

void IIC_Start();

void IIC_Stop();

void Write_IIC_Byte(U8 IIC_Byte);

#endif