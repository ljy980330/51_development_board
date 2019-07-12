/*********************************************************************************************************
*���ƣ�i2c_set.h
*���ܣ�	i2c���������õ���ͷ�ļ��Լ�����������
����ʱ�䣺2019/7/5
�޸�ʱ�䣺2019/XX/XX
���ߣ�XXX
**********************************************************************************************************/

#ifndef _I2C_SET_H
#define _I2C_SET_H

#include "config.h"
#include "STC12C5A.H"
#include "delay/delay.h"

#define high 1	//�ߵ�ƽ
#define low  0	//�͵�λ

sbit SCL = P2^0;	//����ʱ��
sbit SDA = P2^1;	//��������

void IIC_Init();

void IIC_Start();

void IIC_Stop();

void Write_IIC_Byte(U8 IIC_Byte);

U8 Read_IIC_Byte();


#endif

